// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

use string_view_apis::crubit_string_view::{GetHelloWorld, GetInvalidUtf8};

#[test]
fn test_valid_utf8_str() {
    let hello_str: &'static str = GetHelloWorld().try_into().unwrap();
    assert_eq!(hello_str, "Hello, world!");
}

#[test]
fn test_invalid_utf8_str() {
    let not_a_str: Result<&'static str, _> = GetInvalidUtf8().try_into();
    let _ = not_a_str.unwrap_err();
}
