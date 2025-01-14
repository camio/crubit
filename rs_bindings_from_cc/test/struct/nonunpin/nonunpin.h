// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef CRUBIT_RS_BINDINGS_FROM_CC_TEST_STRUCT_NONUNPIN_NONUNPIN_H_
#define CRUBIT_RS_BINDINGS_FROM_CC_TEST_STRUCT_NONUNPIN_NONUNPIN_H_

#include <cstddef>
#include <utility>
#pragma clang lifetime_elision

// A deliberately !Unpin class.
class Nonunpin {
 public:
  Nonunpin() {}
  explicit Nonunpin(int value) : value_(value) {}
  Nonunpin(const Nonunpin& other) : Nonunpin(other.value_) {}
  // We have a nonconventional assignment operator which returns a
  // non-trivially-relocatable value, by value.
  //
  // NOLINTNEXTLINE(misc-unconventional-assign-operator)
  Nonunpin operator=(const Nonunpin& other) {
    value_ = other.value_;
    return *this;
  }
  Nonunpin(Nonunpin&& other) : Nonunpin(other.value_) { other.value_ = 0; }
  Nonunpin& operator=(Nonunpin&& other) {
    value_ = other.value_;
    other.value_ = 0;
    return *this;
  }
  ~Nonunpin() {}

  size_t addr() const { return addr_; }
  int value() const { return value_; }
  void set_value(int new_value) { value_ = new_value; }

  Nonunpin& AsMutRef() { return *this; }
  Nonunpin&& AsRvalueRef() { return std::move(*this); }

  const Nonunpin& AsConstRef() const { return *this; }
  const Nonunpin&& AsConstRvalueRef() const { return std::move(*this); }

  Nonunpin AsValue() const { return *this; }

 private:
  int value_ = 0;
  size_t addr_ = reinterpret_cast<size_t>(this);
};

inline int GetValueFromMutRef(Nonunpin& nonunpin) { return nonunpin.value(); }
inline int GetValueFromConstRef(const Nonunpin& nonunpin) {
  return nonunpin.value();
}
inline int GetValueFromRvalueRef(Nonunpin&& nonunpin) {
  return nonunpin.value();
}
inline int GetValueFromConstRvalueRef(const Nonunpin&& nonunpin) {
  return nonunpin.value();
}
inline int GetValueFromValue(Nonunpin nonunpin) { return nonunpin.value(); }

// A deliberately !Unpin (aggregate) struct.
struct NonunpinStruct {
  int value;
};

// A deliberately non-movable, non-copyable struct. (And, therefore, !Unpin).
struct Nonmovable final {
  Nonmovable() : addr(reinterpret_cast<uintptr_t>(this)) {}
  Nonmovable(const Nonmovable&) = delete;
  Nonmovable(Nonmovable&&) = delete;
  // The address at the time of construction.
  uintptr_t addr;
};

inline Nonmovable ReturnsNonmovable() { return Nonmovable(); }

#endif  // CRUBIT_RS_BINDINGS_FROM_CC_TEST_STRUCT_NONUNPIN_NONUNPIN_H_
