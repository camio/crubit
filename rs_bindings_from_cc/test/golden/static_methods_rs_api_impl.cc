// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <cstddef>
#include <memory>
#include "rs_bindings_from_cc/test/golden/static_methods.h"

extern "C" void __rust_thunk___ZN9SomeClassD1Ev(SomeClass* __this) {
  return std ::destroy_at(__this);
}

static_assert(sizeof(SomeClass) == 4);
static_assert(alignof(SomeClass) == 4);
static_assert(offsetof(SomeClass, field_) * 8 == 0);