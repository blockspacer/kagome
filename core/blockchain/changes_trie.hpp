/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_BLOCKCHAIN_CHANGES_TRIE_HPP
#define KAGOME_BLOCKCHAIN_CHANGES_TRIE_HPP

#include "common/buffer.hpp"
#include "outcome/outcome.hpp"
#include "primitives/extrinsic.hpp"

namespace kagome::blockchain {

  class ChangesTrie {
   public:
    /**
     * @param key - key which value was changed
     * @param changers - indices of extrinsics that changed the entry
     */
    virtual outcome::result<void> insertExtrinsicsChange(
        const common::Buffer &key,
        const std::vector<primitives::ExtrinsicIndex> &changers) = 0;
    // virtual outcome::result<void> insertBlocksChange() = 0;

    virtual common::Buffer getRootHash() const = 0;
  };

}  // namespace kagome::blockchain

#endif  // KAGOME_BLOCKCHAIN_CHANGES_TRIE_HPP