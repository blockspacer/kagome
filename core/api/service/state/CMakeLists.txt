#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

add_library(state_api_service
    state_jrpc_processor.cpp
    impl/state_api_impl.cpp
    )
target_link_libraries(state_api_service
    api_state_requests
    buffer
    api_service
    polkadot_trie_db
    )

add_library(readonly_trie_builder
    impl/readonly_trie_builder_impl.cpp
    )
target_link_libraries(readonly_trie_builder
    buffer
    )

add_subdirectory(requests)
