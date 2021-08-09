// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// This file defines an intermediate representation (IR) used between Clang AST
// and code generators that generate Rust bindings and C++ bindings
// implementation.
//
// All types in this file own their data. This IR is expected to outlive the
// Clang's AST context, therefore it cannot reference data owned by it.
#ifndef CRUBIT_RS_BINDINGS_FROM_CC_IR_H_
#define CRUBIT_RS_BINDINGS_FROM_CC_IR_H_

#include <utility>
#include <vector>

#include "base/logging.h"
#include "third_party/absl/strings/cord.h"
#include "third_party/json/src/json.hpp"

namespace rs_bindings_from_cc {

// A type involved in the bindings. It has the knowledge about how the type is
// spelled in Rust and in C++ code.
//
// Examples:
//     Type of C++'s `int32_t` will be `Type("i32")`.
//     Type of C++'s `struct foo` will be `Type("Foo")`.
//
// Conventions:
//     `rs_name` cannot be empty.
// TODO(hlopko): Add knowledge about the spelling of the C++ type.
class Type {
 public:
  explicit Type(absl::Cord rs_name) : rs_name_(std::move(rs_name)) {}

  const absl::Cord &RsName() const { return rs_name_; }

  nlohmann::json ToJson() const;

 private:
  absl::Cord rs_name_;
};

// An identifier involved in bindings.
//
// Examples:
//     Identifier of C++'s `int32_t Add(int32_t a, int32_t b)` will be
//     `Identifier("add")`.
//
// Invariants:
//     `identifier` cannot be empty.
class Identifier {
 public:
  explicit Identifier(absl::Cord identifier)
      : identifier_(std::move(identifier)) {
    CHECK(!identifier_.empty()) << "Identifier name cannot be empty.";
  }

  const absl::Cord &Ident() const { return identifier_; }

  nlohmann::json ToJson() const;

 private:
  absl::Cord identifier_;
};

// A function parameter.
//
// Examples:
//    FuncParam of a C++ function `void Foo(int32_t a);` will be
//    `FuncParam(Type("i32"), Identifier("foo"))`.
class FuncParam {
 public:
  explicit FuncParam(Type type, Identifier identifier)
      : type_(std::move(type)), identifier_(std::move(identifier)) {}

  const Type &ParamType() const { return type_; }
  const Identifier &Ident() const { return identifier_; }

  nlohmann::json ToJson() const;

 private:
  Type type_;
  Identifier identifier_;
};

// A function involved in the bindings.
class Func {
 public:
  explicit Func(Identifier identifier, absl::Cord mangled_name,
                Type return_type, std::vector<FuncParam> params)
      : identifier_(std::move(identifier)),
        mangled_name_(std::move(mangled_name)),
        return_type_(std::move(return_type)),
        params_(std::move(params)) {}

  const absl::Cord &MangledName() const { return mangled_name_; }
  const Type &ReturnType() const { return return_type_; }
  const Identifier &Ident() const { return identifier_; }

  const std::vector<FuncParam> &Params() const { return params_; }

  nlohmann::json ToJson() const;

 private:
  Identifier identifier_;
  absl::Cord mangled_name_;
  Type return_type_;
  std::vector<FuncParam> params_;
};

// A complete intermediate representation of bindings for publicly accessible
// declarations of a single C++ library.
class IR {
 public:
  explicit IR(std::vector<Func> functions) : functions_(std::move(functions)) {}

  nlohmann::json ToJson() const;

 private:
  std::vector<Func> functions_;
};

}  // namespace rs_bindings_from_cc

#endif  // CRUBIT_RS_BINDINGS_FROM_CC_IR_H_
