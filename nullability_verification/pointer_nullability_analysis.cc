// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "nullability_verification/pointer_nullability_analysis.h"

#include <string>

#include "absl/log/check.h"
#include "nullability_verification/pointer_nullability.h"
#include "nullability_verification/pointer_nullability_matchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Analysis/FlowSensitive/CFGMatchSwitch.h"
#include "clang/Analysis/FlowSensitive/DataflowEnvironment.h"
#include "clang/Analysis/FlowSensitive/NoopLattice.h"
#include "clang/Analysis/FlowSensitive/Value.h"
#include "clang/Basic/LLVM.h"
#include "clang/Basic/Specifiers.h"

namespace clang {
namespace tidy {
namespace nullability {

using ast_matchers::MatchFinder;
using dataflow::BoolValue;
using dataflow::CFGMatchSwitchBuilder;
using dataflow::Environment;
using dataflow::NoopLattice;
using dataflow::PointerValue;
using dataflow::SkipPast;
using dataflow::TransferState;
using dataflow::Value;

namespace {

NullabilityKind getNullabilityFromTemplatedExpression(const Expr* E) {
  // Stores the nullability of each template argument.
  std::vector<NullabilityKind> NullabilityVector = {};
  const TemplateTypeParmDecl* ReplacedParameter = nullptr;

  // If the expression is a member function call on an object whose type
  // is a class template instantiation, propagate the sugar from template
  // arguments to the member function return type.
  //
  // TODO: Handle more expression shapes.
  if (auto MemberCall = dyn_cast<CXXMemberCallExpr>(E)) {
    Expr* Object = MemberCall->getImplicitObjectArgument();
    if (auto Member = dyn_cast<MemberExpr>(MemberCall->getCallee())) {
      if (auto Method = dyn_cast<CXXMethodDecl>(Member->getMemberDecl())) {
        if (auto TST = Object->getType()->getAs<TemplateSpecializationType>()) {
          for (TemplateArgument TA : TST->template_arguments()) {
            NullabilityKind ArgumentNullability = NullabilityKind::Unspecified;
            if (TA.getKind() == TemplateArgument::Type) {
              if (auto AT = TA.getAsType()->getAs<AttributedType>()) {
                ArgumentNullability = AT->getImmediateNullability().value_or(
                    NullabilityKind::Unspecified);
              }
            }
            NullabilityVector.push_back(ArgumentNullability);
          }
        }

        // Save the replaced template parameter.
        // TODO: Handle cases where the template argument is nested inside the
        // return type (e.g. vector<map<T**, T>>).
        if (auto SubstTemplate =
                Method->getReturnType()->getAs<SubstTemplateTypeParmType>()) {
          ReplacedParameter = SubstTemplate->getReplacedParameter();
        }
      }
    }
  }

  NullabilityKind Nullability = NullabilityKind::Unspecified;
  if (ReplacedParameter && ReplacedParameter->getDepth() == 0) {
    Nullability = NullabilityVector[ReplacedParameter->getIndex()];
  }
  return Nullability;
}

NullabilityKind getPointerNullability(const Expr* E, ASTContext& Ctx) {
  QualType ExprType = E->getType();
  NullabilityKind Nullability =
      ExprType->getNullability(Ctx).value_or(NullabilityKind::Unspecified);
  if (Nullability == NullabilityKind::Unspecified) {
    // Try to get nullability from the expression itself.
    Nullability = getNullabilityFromTemplatedExpression(E);
  }
  return Nullability;
}

void initPointerFromAnnotations(PointerValue& PointerVal, const Expr* E,
                                Environment& Env, ASTContext& Ctx) {
  NullabilityKind Nullability = getPointerNullability(E, Ctx);
  switch (Nullability) {
    case NullabilityKind::NonNull:
      initNotNullPointer(PointerVal, Env);
      break;
    case NullabilityKind::Nullable:
      initNullablePointer(PointerVal, Env);
      break;
    default:
      initUnknownPointer(PointerVal, Env);
  }
}

void transferNullPointer(const Expr* NullPointer,
                         const MatchFinder::MatchResult&,
                         TransferState<NoopLattice>& State) {
  if (auto* PointerVal = getPointerValueFromExpr(NullPointer, State.Env)) {
    initNullPointer(*PointerVal, State.Env);
  }
}

void transferNotNullPointer(const Expr* NotNullPointer,
                            const MatchFinder::MatchResult&,
                            TransferState<NoopLattice>& State) {
  if (auto* PointerVal = getPointerValueFromExpr(NotNullPointer, State.Env)) {
    initNotNullPointer(*PointerVal, State.Env);
  }
}

void transferPointer(const Expr* PointerExpr,
                     const MatchFinder::MatchResult& Result,
                     TransferState<NoopLattice>& State) {
  if (auto* PointerVal = getPointerValueFromExpr(PointerExpr, State.Env)) {
    initPointerFromAnnotations(*PointerVal, PointerExpr, State.Env,
                               *Result.Context);
  }
}

// TODO(b/233582219): Implement promotion of nullability knownness for initially
// unknown pointers when there is evidence that it is nullable, for example
// when the pointer is compared to nullptr, or casted to boolean.
void transferNullCheckComparison(const BinaryOperator* BinaryOp,
                                 const MatchFinder::MatchResult& result,
                                 TransferState<NoopLattice>& State) {
  // Boolean representing the comparison between the two pointer values,
  // automatically created by the dataflow framework.
  auto& PointerComparison =
      *cast<BoolValue>(State.Env.getValue(*BinaryOp, SkipPast::None));

  CHECK(BinaryOp->getOpcode() == BO_EQ || BinaryOp->getOpcode() == BO_NE);
  auto& PointerEQ = BinaryOp->getOpcode() == BO_EQ
                        ? PointerComparison
                        : State.Env.makeNot(PointerComparison);
  auto& PointerNE = BinaryOp->getOpcode() == BO_EQ
                        ? State.Env.makeNot(PointerComparison)
                        : PointerComparison;

  auto* LHS = getPointerValueFromExpr(BinaryOp->getLHS(), State.Env);
  auto* RHS = getPointerValueFromExpr(BinaryOp->getRHS(), State.Env);

  if (!LHS || !RHS) return;

  auto [LHSKnown, LHSNull] = getPointerNullState(*LHS, State.Env);
  auto [RHSKnown, RHSNull] = getPointerNullState(*RHS, State.Env);
  auto& LHSKnownNotNull =
      State.Env.makeAnd(LHSKnown, State.Env.makeNot(LHSNull));
  auto& RHSKnownNotNull =
      State.Env.makeAnd(RHSKnown, State.Env.makeNot(RHSNull));
  auto& LHSKnownNull = State.Env.makeAnd(LHSKnown, LHSNull);
  auto& RHSKnownNull = State.Env.makeAnd(RHSKnown, RHSNull);

  // nullptr == nullptr
  State.Env.addToFlowCondition(State.Env.makeImplication(
      State.Env.makeAnd(LHSKnownNull, RHSKnownNull), PointerEQ));
  // nullptr != notnull
  State.Env.addToFlowCondition(State.Env.makeImplication(
      State.Env.makeAnd(LHSKnownNull, RHSKnownNotNull), PointerNE));
  // notnull != nullptr
  State.Env.addToFlowCondition(State.Env.makeImplication(
      State.Env.makeAnd(LHSKnownNotNull, RHSKnownNull), PointerNE));
}

void transferNullCheckImplicitCastPtrToBool(const Expr* CastExpr,
                                            const MatchFinder::MatchResult&,
                                            TransferState<NoopLattice>& State) {
  auto* PointerVal =
      getPointerValueFromExpr(CastExpr->IgnoreImplicit(), State.Env);
  if (!PointerVal) return;

  auto [PointerKnown, PointerNull] =
      getPointerNullState(*PointerVal, State.Env);
  auto& CastExprLoc = State.Env.createStorageLocation(*CastExpr);
  State.Env.setValue(CastExprLoc, State.Env.makeNot(PointerNull));
  State.Env.setStorageLocation(*CastExpr, CastExprLoc);
}

void transferCallExpr(const CallExpr* CallExpr,
                      const MatchFinder::MatchResult& Result,
                      TransferState<NoopLattice>& State) {
  auto ReturnType = CallExpr->getType();
  if (!ReturnType->isAnyPointerType()) return;

  auto* PointerVal = getPointerValueFromExpr(CallExpr, State.Env);
  if (!PointerVal) {
    PointerVal = cast<PointerValue>(State.Env.createValue(ReturnType));
    auto& CallExprLoc = State.Env.createStorageLocation(*CallExpr);
    State.Env.setValue(CallExprLoc, *PointerVal);
    State.Env.setStorageLocation(*CallExpr, CallExprLoc);
  }
  initPointerFromAnnotations(*PointerVal, CallExpr, State.Env, *Result.Context);
}

auto buildTransferer() {
  return CFGMatchSwitchBuilder<TransferState<NoopLattice>>()
      // Handles initialization of the null states of pointers.
      .CaseOfCFGStmt<Expr>(isPointerVariableReference(), transferPointer)
      .CaseOfCFGStmt<Expr>(isCXXThisExpr(), transferNotNullPointer)
      .CaseOfCFGStmt<Expr>(isAddrOf(), transferNotNullPointer)
      .CaseOfCFGStmt<Expr>(isNullPointerLiteral(), transferNullPointer)
      .CaseOfCFGStmt<MemberExpr>(isMemberOfPointerType(), transferPointer)
      .CaseOfCFGStmt<CallExpr>(isCallExpr(), transferCallExpr)
      // Handles comparison between 2 pointers.
      .CaseOfCFGStmt<BinaryOperator>(isPointerCheckBinOp(),
                                     transferNullCheckComparison)
      // Handles checking of pointer as boolean.
      .CaseOfCFGStmt<Expr>(isImplicitCastPointerToBool(),
                           transferNullCheckImplicitCastPtrToBool)
      .Build();
}
}  // namespace

PointerNullabilityAnalysis::PointerNullabilityAnalysis(ASTContext& Context)
    : DataflowAnalysis<PointerNullabilityAnalysis, NoopLattice>(Context),
      Transferer(buildTransferer()) {}

void PointerNullabilityAnalysis::transfer(const CFGElement* Elt,
                                          NoopLattice& Lattice,
                                          Environment& Env) {
  TransferState<NoopLattice> State(Lattice, Env);
  Transferer(*Elt, getASTContext(), State);
}

BoolValue& mergeBoolValues(BoolValue& Bool1, const Environment& Env1,
                           BoolValue& Bool2, const Environment& Env2,
                           Environment& MergedEnv) {
  if (&Bool1 == &Bool2) {
    return Bool1;
  }

  auto& MergedBool = MergedEnv.makeAtomicBoolValue();

  // If `Bool1` and `Bool2` is constrained to the same true / false value,
  // `MergedBool` can be constrained similarly without needing to consider the
  // path taken - this simplifies the flow condition tracked in `MergedEnv`.
  // Otherwise, information about which path was taken is used to associate
  // `MergedBool` with `Bool1` and `Bool2`.
  if (Env1.flowConditionImplies(Bool1) && Env2.flowConditionImplies(Bool2)) {
    MergedEnv.addToFlowCondition(MergedBool);
  } else if (Env1.flowConditionImplies(Env1.makeNot(Bool1)) &&
             Env2.flowConditionImplies(Env2.makeNot(Bool2))) {
    MergedEnv.addToFlowCondition(MergedEnv.makeNot(MergedBool));
  } else {
    // TODO(b/233582219): Flow conditions are not necessarily mutually
    // exclusive, a fix is in order: https://reviews.llvm.org/D130270. Update
    // this section when the patch is commited.
    auto& FC1 = Env1.getFlowConditionToken();
    auto& FC2 = Env2.getFlowConditionToken();
    MergedEnv.addToFlowCondition(MergedEnv.makeOr(
        MergedEnv.makeAnd(FC1, MergedEnv.makeIff(MergedBool, Bool1)),
        MergedEnv.makeAnd(FC2, MergedEnv.makeIff(MergedBool, Bool2))));
  }
  return MergedBool;
}

bool PointerNullabilityAnalysis::merge(QualType Type, const Value& Val1,
                                       const Environment& Env1,
                                       const Value& Val2,
                                       const Environment& Env2,
                                       Value& MergedVal,
                                       Environment& MergedEnv) {
  if (!Type->isAnyPointerType()) {
    return false;
  }

  auto [Known1, Null1] = getPointerNullState(cast<PointerValue>(Val1), Env1);
  auto [Known2, Null2] = getPointerNullState(cast<PointerValue>(Val2), Env2);

  auto& Known = mergeBoolValues(Known1, Env1, Known2, Env2, MergedEnv);
  auto& Null = mergeBoolValues(Null1, Env1, Null2, Env2, MergedEnv);

  initPointerNullState(cast<PointerValue>(MergedVal), MergedEnv, &Known, &Null);

  return true;
}
}  // namespace nullability
}  // namespace tidy
}  // namespace clang
