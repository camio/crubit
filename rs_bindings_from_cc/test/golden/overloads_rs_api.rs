// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Automatically @generated Rust bindings for the following C++ target:
// //rs_bindings_from_cc/test/golden:overloads_cc

#![feature(negative_impls)]
#![allow(stable_features)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![deny(warnings)]

// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// rs_bindings_from_cc/test/golden/overloads.h;l=10
// Error while generating bindings for item 'Overload':
// Cannot generate bindings for overloaded function

// rs_bindings_from_cc/test/golden/overloads.h;l=11
// Error while generating bindings for item 'Overload':
// Cannot generate bindings for overloaded function

// rs_bindings_from_cc/test/golden/overloads.h;l=16
// Error while generating bindings for item 'UncallableOverload':
// Cannot generate bindings for overloaded function

// rs_bindings_from_cc/test/golden/overloads.h;l=19
// Error while generating bindings for item 'UncallableOverload':
// Cannot generate bindings for overloaded function

// rs_bindings_from_cc/test/golden/overloads.h;l=22
// Error while generating bindings for item 'UncallableOverload':
// Function templates are not supported yet

#[inline(always)]
pub fn AlsoTemplateOverload() {
    unsafe { crate::detail::__rust_thunk___Z20AlsoTemplateOverloadv() }
}

// rs_bindings_from_cc/test/golden/overloads.h;l=26
// Error while generating bindings for item 'AlsoTemplateOverload':
// Function templates are not supported yet

// THIRD_PARTY_CRUBIT_RS_BINDINGS_FROM_CC_TEST_GOLDEN_OVERLOADS_H_

#[::ctor::recursively_pinned]
#[repr(C)]
pub struct __CcTemplateInstNSt3__u17integral_constantIbLb0EEE {
    __non_field_data: [::std::mem::MaybeUninit<u8>; 1],
}
forward_declare::unsafe_define!(
    forward_declare::symbol!("std::integral_constant<bool, false>"),
    crate::__CcTemplateInstNSt3__u17integral_constantIbLb0EEE
);

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, false>::std::integral_constant<bool, false>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, false>::std::integral_constant<bool, false>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, false>::integral_constant':
// Parameter #0 is not supported: Unsupported type 'struct std::integral_constant<_Bool, false> &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, false>::operator=':
// `self` has no lifetime. Use lifetime annotations or `#pragma clang lifetime_elision` to create bindings for this function.

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, false>::operator=':
// Parameter #0 is not supported: Unsupported type 'struct std::integral_constant<_Bool, false> &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=24
// Error while generating bindings for item 'value_type':
// Typedefs nested in classes are not supported yet

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=25
// Error while generating bindings for item 'type':
// Typedefs nested in classes are not supported yet

// <unknown location>
// Error while generating bindings for item 'std::integral_constant<bool, false>::operator bool':
// TODO(b/248542210,b/248577708): as a temporary workaround for un-instantiable function templates, template functions from the STL cannot be instantiated in user crates

// <unknown location>
// Error while generating bindings for item 'std::integral_constant<bool, false>::operator()':
// TODO(b/248542210,b/248577708): as a temporary workaround for un-instantiable function templates, template functions from the STL cannot be instantiated in user crates

#[::ctor::recursively_pinned]
#[repr(C)]
pub struct __CcTemplateInstNSt3__u17integral_constantIbLb1EEE {
    __non_field_data: [::std::mem::MaybeUninit<u8>; 1],
}
forward_declare::unsafe_define!(
    forward_declare::symbol!("std::integral_constant<bool, true>"),
    crate::__CcTemplateInstNSt3__u17integral_constantIbLb1EEE
);

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, true>::std::integral_constant<bool, true>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, true>::std::integral_constant<bool, true>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, true>::integral_constant':
// Parameter #0 is not supported: Unsupported type 'struct std::integral_constant<_Bool, true> &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, true>::operator=':
// `self` has no lifetime. Use lifetime annotations or `#pragma clang lifetime_elision` to create bindings for this function.

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=21
// Error while generating bindings for item 'std::integral_constant<bool, true>::operator=':
// Parameter #0 is not supported: Unsupported type 'struct std::integral_constant<_Bool, true> &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=24
// Error while generating bindings for item 'value_type':
// Typedefs nested in classes are not supported yet

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/integral_constant.h;l=25
// Error while generating bindings for item 'type':
// Typedefs nested in classes are not supported yet

// <unknown location>
// Error while generating bindings for item 'std::integral_constant<bool, true>::operator bool':
// TODO(b/248542210,b/248577708): as a temporary workaround for un-instantiable function templates, template functions from the STL cannot be instantiated in user crates

// <unknown location>
// Error while generating bindings for item 'std::integral_constant<bool, true>::operator()':
// TODO(b/248542210,b/248577708): as a temporary workaround for un-instantiable function templates, template functions from the STL cannot be instantiated in user crates

#[::ctor::recursively_pinned]
#[repr(C)]
pub struct __CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE
{
    __non_field_data: [::std::mem::MaybeUninit<u8>; 1],
}
forward_declare::unsafe_define!(forward_declare::symbol!("std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>"),crate::__CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE);

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=22
// Error while generating bindings for item 'std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>::std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=22
// Error while generating bindings for item 'std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>::std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>':
// Unsafe constructors (e.g. with no elided or explicit lifetimes) are intentionally not supported

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=22
// Error while generating bindings for item 'std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>::__type_list':
// Parameter #0 is not supported: Unsupported type 'struct std::__type_list<struct std::__align_type<unsigned char>, struct std::__type_list<struct std::__align_type<unsigned short>, struct std::__type_list<struct std::__align_type<unsigned int>, struct std::__type_list<struct std::__align_type<unsigned long>, struct std::__type_list<struct std::__align_type<unsigned long long>, struct std::__type_list<struct std::__align_type<double>, struct std::__type_list<struct std::__align_type<long double>, struct std::__type_list<struct std::__align_type<struct std::__struct_double>, struct std::__type_list<struct std::__align_type<struct std::__struct_double4>, struct std::__type_list<struct std::__align_type<int *>, struct std::__nat> > > > > > > > > > &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=22
// Error while generating bindings for item 'std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>::operator=':
// `self` has no lifetime. Use lifetime annotations or `#pragma clang lifetime_elision` to create bindings for this function.

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=22
// Error while generating bindings for item 'std::__type_list<std::__align_type<unsigned char>, std::__type_list<std::__align_type<unsigned short>, std::__type_list<std::__align_type<unsigned int>, std::__type_list<std::__align_type<unsigned long>, std::__type_list<std::__align_type<unsigned long long>, std::__type_list<std::__align_type<double>, std::__type_list<std::__align_type<long double>, std::__type_list<std::__align_type<std::__struct_double>, std::__type_list<std::__align_type<std::__struct_double4>, std::__type_list<std::__align_type<int *>, std::__nat>>>>>>>>>>::operator=':
// Parameter #0 is not supported: Unsupported type 'struct std::__type_list<struct std::__align_type<unsigned char>, struct std::__type_list<struct std::__align_type<unsigned short>, struct std::__type_list<struct std::__align_type<unsigned int>, struct std::__type_list<struct std::__align_type<unsigned long>, struct std::__type_list<struct std::__align_type<unsigned long long>, struct std::__type_list<struct std::__align_type<double>, struct std::__type_list<struct std::__align_type<long double>, struct std::__type_list<struct std::__align_type<struct std::__struct_double>, struct std::__type_list<struct std::__align_type<struct std::__struct_double4>, struct std::__type_list<struct std::__align_type<int *>, struct std::__nat> > > > > > > > > > &&': Unsupported type: && without lifetime

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=24
// Error while generating bindings for item '_Head':
// Typedefs nested in classes are not supported yet

// google3/nowhere/llvm/toolchain/include/c++/v1/__type_traits/type_list.h;l=25
// Error while generating bindings for item '_Tail':
// Typedefs nested in classes are not supported yet

forward_declare::forward_declare!(pub __CcTemplateInstNSt3__u11__type_listINS_12__align_typeItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEE = forward_declare::symbol!("__CcTemplateInstNSt3__u11__type_listINS_12__align_typeItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEE"));

forward_declare::forward_declare!(pub __CcTemplateInstNSt3__u12__align_typeIhEE = forward_declare::symbol!("__CcTemplateInstNSt3__u12__align_typeIhEE"));

mod detail {
    #[allow(unused_imports)]
    use super::*;
    extern "C" {
        pub(crate) fn __rust_thunk___Z20AlsoTemplateOverloadv();
    }
}

const _: () = assert!(::std::mem::size_of::<Option<&i32>>() == ::std::mem::size_of::<&i32>());

const _: () = assert!(
    ::std::mem::size_of::<crate::__CcTemplateInstNSt3__u17integral_constantIbLb0EEE>() == 1
);
const _: () = assert!(
    ::std::mem::align_of::<crate::__CcTemplateInstNSt3__u17integral_constantIbLb0EEE>() == 1
);
const _: () = {
    static_assertions::assert_not_impl_any!(
        crate::__CcTemplateInstNSt3__u17integral_constantIbLb0EEE: Copy
    );
};
const _: () = {
    static_assertions::assert_not_impl_any!(
        crate::__CcTemplateInstNSt3__u17integral_constantIbLb0EEE: Drop
    );
};

const _: () = assert!(
    ::std::mem::size_of::<crate::__CcTemplateInstNSt3__u17integral_constantIbLb1EEE>() == 1
);
const _: () = assert!(
    ::std::mem::align_of::<crate::__CcTemplateInstNSt3__u17integral_constantIbLb1EEE>() == 1
);
const _: () = {
    static_assertions::assert_not_impl_any!(
        crate::__CcTemplateInstNSt3__u17integral_constantIbLb1EEE: Copy
    );
};
const _: () = {
    static_assertions::assert_not_impl_any!(
        crate::__CcTemplateInstNSt3__u17integral_constantIbLb1EEE: Drop
    );
};

const _:()=assert!(::std::mem::size_of::<crate::__CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE>()==1);
const _:()=assert!(::std::mem::align_of::<crate::__CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE>()==1);
const _: () = {
    static_assertions::assert_not_impl_any!(crate::__CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE:Copy);
};
const _: () = {
    static_assertions::assert_not_impl_any!(crate::__CcTemplateInstNSt3__u11__type_listINS_12__align_typeIhEENS0_INS1_ItEENS0_INS1_IjEENS0_INS1_ImEENS0_INS1_IyEENS0_INS1_IdEENS0_INS1_IeEENS0_INS1_INS_15__struct_doubleEEENS0_INS1_INS_16__struct_double4EEENS0_INS1_IPiEENS_5__natEEEEEEEEEEEEEEEEEEEEE:Drop);
};
