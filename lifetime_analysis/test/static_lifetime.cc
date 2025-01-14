// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Tests involving static lifetimes.

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lifetime_analysis/test/lifetime_analysis_test.h"

namespace clang {
namespace tidy {
namespace lifetimes {
namespace {

TEST_F(LifetimeAnalysisTest, MaybeReturnStatic) {
  // Check that we don't infer 'static for the parameter or the return value,
  // which would be overly restrictive.

  EXPECT_THAT(GetLifetimes(R"(
    int* target(int* i_non_static) {
      if (*i_non_static > 0) {
        return i_non_static;
      } else {
        static int i_static;
        return &i_static;
      }
    }
  )"),
              LifetimesAre({{"target", "a -> a"}}));
}

TEST_F(LifetimeAnalysisTest, MaybeReturnStaticConst) {
  // Same as above, but return a pointer-to-const. This should have no
  // influence on the outcome.

  EXPECT_THAT(GetLifetimes(R"(
    const int* target(int* i_non_static) {
      if (*i_non_static > 0) {
        return i_non_static;
      } else {
        static int i_static;
        return &i_static;
      }
    }
  )"),
              LifetimesAre({{"target", "a -> a"}}));
}

TEST_F(LifetimeAnalysisTest, StaticPointerOutParam) {
  EXPECT_THAT(GetLifetimes(R"(
    void f(int** p) {
      static int i = 42;
      *p = &i;
    }
  )"),
              LifetimesAre({{"f", "(a, b)"}}));
}

TEST_F(LifetimeAnalysisTest, MaybeReturnStaticStruct) {
  // We infer a `static` lifetime parameter for `s_static` because any pointers
  // contained in it need to outlive the struct itself. This implies that the
  // lifetime parameter for the return value also needs to be `static`, and
  // hence the lifetime parameter on `*s_input` needs to be `static` too.

  EXPECT_THAT(GetLifetimes(R"(
    struct [[clang::annotate("lifetime_params", "a")]] S {
      [[clang::annotate("member_lifetimes", "a", "a")]]
      int** pp;
    };
    S* target(S* s_input) {
      if (**s_input->pp > 0) {
        return s_input;
      } else {
        static S s_static;
        return &s_static;
      }
    }
  )"),
              LifetimesAre({{"target", "(static, a) -> (static, a)"}}));
}

TEST_F(LifetimeAnalysisTest, MaybeReturnStaticStructConst) {
  // Same as above, but return a pointer-to-const. This shouldn't affect the
  // result, as it's still possible to modify `*s.pp` even if for a `const S s`.

  EXPECT_THAT(GetLifetimes(R"(
    struct [[clang::annotate("lifetime_params", "a")]] S {
      [[clang::annotate("member_lifetimes", "a", "a")]]
      int** pp;
    };
    const S* target(S* s_input) {
      if (**s_input->pp > 0) {
        return s_input;
      } else {
        static S s_static;
        return &s_static;
      }
    }
  )"),
              LifetimesAre({{"target", "(static, a) -> (static, a)"}}));
}

TEST_F(LifetimeAnalysisTest, MaybeReturnStaticStructConstWithoutPointer) {
  // Same as above, but with a struct that doesn't actually contain any
  // pointers. This changes the result, as a 'static struct without any pointer
  // can be used in place of a struct of the same type of any lifetime.

  EXPECT_THAT(GetLifetimes(R"(
    struct S {
      int i;
    };
    const S* target(S* s_input) {
      if (s_input->i > 0) {
        return s_input;
      } else {
        static S s_static;
        return &s_static;
      }
    }
  )"),
              LifetimesAre({{"target", "a -> a"}}));
}

TEST_F(LifetimeAnalysisTest, ReturnStaticDoublePointerWithConditional) {
  EXPECT_THAT(
      GetLifetimes(R"(
    struct [[clang::annotate("lifetime_params", "a")]] S {
      [[clang::annotate("member_lifetimes", "a")]]
      int* p;
    };
    int** target(int** pp1, int** pp2) {
      // Force *pp1 to have static lifetime.
      static S s;
      s.p = *pp1;

      if (**pp1 > 0) {
        return pp1;
      } else {
        return pp2;
      }
    }
  )"),
      LifetimesAre({{"target", "(static, a), (static, a) -> (static, a)"}}));
}

TEST_F(LifetimeAnalysisTest, ReturnStaticConstDoublePointerWithConditional) {
  EXPECT_THAT(GetLifetimes(R"(
    struct [[clang::annotate("lifetime_params", "a")]] S {
      [[clang::annotate("member_lifetimes", "a")]]
      int* p;
    };
    int* const * target(int** pp1, int** pp2) {
      // Force *pp1 to have static lifetime.
      static S s;
      s.p = *pp1;

      if (**pp1 > 0) {
        return pp1;
      } else {
        return pp2;
      }
    }
  )"),
              LifetimesAre({{"target", "(static, a), (b, a) -> (b, a)"}}));
}

TEST_F(LifetimeAnalysisTest, StaticParameterChainedCall) {
  EXPECT_THAT(GetLifetimes(R"(
    class S {};
    void f1(S* s) {
      static S* s_static = s;
    }
    void f2(S* s) {
      f1(s);
    }
  )"),
              LifetimesAre({{"f1", "static"}, {"f2", "static"}}));
}

TEST_F(LifetimeAnalysisTest, ConstructorStoresThisPointerInStatic) {
  EXPECT_THAT(
      GetLifetimes(R"(
    struct S {
      S() {
        static S* last_constructed = this;
      }
    };
    void construct_static_variable() {
      static S s;
    }
    void construct_local_variable() {
      S s;
    }
  )"),
      // Because S() stores the `this` pointer in a static variable, the
      // lifetime of the `this` pointer needs to be static. This means
      // that any instances of `S` that are constructed need to have
      // static lifetime.
      LifetimesAre({{"S::S", "static:"},
                    {"construct_static_variable", ""},
                    {"construct_local_variable",
                     "ERROR: attempted to make a pointer of static lifetime "
                     "point at an object of local lifetime"}}));
}

TEST_F(LifetimeAnalysisTest, ConstructorStoresThisPointerInStatic_WithField) {
  EXPECT_THAT(GetLifetimes(R"(
    struct S {
      S() {
        static S* last_constructed = this;
      }
    };
    struct T {
      // Ensure that T() isn't defaulted because we don't want to trigger the
      // special logic for defaulted functions.
      T() {}
      S s;
    };
  )"),
              LifetimesAre({{"S::S", "static:"}, {"T::T", "static:"}}));
}

TEST_F(LifetimeAnalysisTest,
       ConstructorStoresThisPointerInStatic_WithDerivedClass) {
  EXPECT_THAT(GetLifetimes(R"(
    struct S {
      S() {
        static S* last_constructed = this;
      }
    };
    struct T : public S {
      // Ensure that T() isn't defaulted because we don't want to trigger the
      // special logic for defaulted functions.
      T() {}
    };
  )"),
              LifetimesAre({{"S::S", "static:"}, {"T::T", "static:"}}));
}

}  // namespace
}  // namespace lifetimes
}  // namespace tidy
}  // namespace clang
