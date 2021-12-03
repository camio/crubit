#![rustfmt::skip]
// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#![feature(const_maybe_uninit_as_ptr, const_ptr_offset_from, custom_inner_attributes)]

use memoffset_unstable_const::offset_of;
use static_assertions::const_assert_eq;

// CRUBIT_RS_BINDINGS_FROM_CC_TEST_GOLDEN_TRIVIAL_TYPE_H_

#[inline(always)]
pub fn UsesImportedType(t: trivial_type_cc::Trivial) -> trivial_type_cc::Trivial {
    unsafe { crate::detail::__rust_thunk__UsesImportedType(t) }
}

#[derive(Clone, Copy)]
#[repr(C)]
pub struct UserOfImportedType {
    pub trivial: *mut trivial_type_cc::Trivial,
}

// rs_bindings_from_cc/test/golden/user_of_imported_type.h;l=8
// Error while generating bindings for item 'UserOfImportedType::UserOfImportedType':
// Nested classes are not supported yet

// rs_bindings_from_cc/test/golden/user_of_imported_type.h;l=8
// Error while generating bindings for item 'UserOfImportedType::UserOfImportedType':
// Empty parameter names are not supported

// rs_bindings_from_cc/test/golden/user_of_imported_type.h;l=8
// Error while generating bindings for item 'UserOfImportedType::operator=':
// Empty parameter names are not supported

// rs_bindings_from_cc/test/golden/user_of_imported_type.h;l=8
// Error while generating bindings for item 'UserOfImportedType::UserOfImportedType':
// Parameter type 'struct UserOfImportedType &&' is not supported

// rs_bindings_from_cc/test/golden/user_of_imported_type.h;l=8
// Error while generating bindings for item 'UserOfImportedType::operator=':
// Parameter type 'struct UserOfImportedType &&' is not supported

// CRUBIT_RS_BINDINGS_FROM_CC_TEST_GOLDEN_USER_OF_IMPORTED_TYPE_H_

mod detail {
    use super::*;
    extern "C" {
        #[link_name = "_Z16UsesImportedType7Trivial"]
        pub(crate) fn __rust_thunk__UsesImportedType(
            t: trivial_type_cc::Trivial,
        ) -> trivial_type_cc::Trivial;
        pub(crate) fn __rust_constructor_thunk__UserOfImportedType(
            __this: *mut UserOfImportedType,
        ) -> ();
    }
}

const_assert_eq!(std::mem::size_of::<UserOfImportedType>(), 8usize);
const_assert_eq!(std::mem::align_of::<UserOfImportedType>(), 8usize);
const_assert_eq!(offset_of!(UserOfImportedType, trivial) * 8, 0usize);