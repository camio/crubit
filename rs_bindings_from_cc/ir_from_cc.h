// Part of the Crubit project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef CRUBIT_RS_BINDINGS_FROM_CC_IR_FROM_CC_H_
#define CRUBIT_RS_BINDINGS_FROM_CC_IR_FROM_CC_H_

#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "rs_bindings_from_cc/bazel_types.h"
#include "rs_bindings_from_cc/ir.h"

namespace crubit {

// Name of the namespace in which we generate code that triggers class template
// instantiations.
static constexpr absl::string_view kInstantiationsNamespaceName =
    "__cc_template_instantiations";

// Parses C++ source code into IR.
//
// Parameters:
// * `extra_source_code_for_testing`: C++ source code to be written into a
//   virtual header and included in binding generation. Intended for testing
//   only.
// * `current_target`: full label of the target for which we generate bindings.
//   If not specified `//test:testing_target` is used.
// * `public_headers`: names of headers from which we build the Clang AST. If
//   `extra_source_code_for_testing` is specified its header will be added
//   automatically.
// * `virtual_headers_contents_for_testing`: names and contents of virtual
//   headers that will be created in the virtual filesystem. These headers have
//   to be manually added to `public_headers` if needed.
// * `headers_to_targets`: mapping of headers to the label of the owning target.
//   If `extra_source_code` is specified it's added automatically under
//   `//test:testing_target`. Headers from
//   `virtual_headers_contents_for_testing` are not added automatically.
// * `clang_args`: additional command line arguments for Clang
// * `extra_rs_srcs`: A list of paths for additional rust files to include into
//   the crate. This is done via `#[path="..."] mod <...>; pub use <...>::*;`.
// * `extra_instantiations`: names of full C++ class template specializations
// to instantiate and generate bindings from.
//
absl::StatusOr<IR> IrFromCc(
    absl::string_view extra_source_code_for_testing,
    BazelLabel current_target = BazelLabel{"//test:testing_target"},
    absl::Span<const HeaderName> public_headers = {},
    absl::flat_hash_map<const HeaderName, const std::string>
        virtual_headers_contents_for_testing = {},
    absl::flat_hash_map<const HeaderName, const BazelLabel> headers_to_targets =
        {},
    absl::Span<const std::string> extra_rs_srcs = {},
    absl::Span<const absl::string_view> clang_args = {},
    absl::Span<const std::string> extra_instantiations = {});

}  // namespace crubit

#endif  // CRUBIT_RS_BINDINGS_FROM_CC_IR_FROM_CC_H_
