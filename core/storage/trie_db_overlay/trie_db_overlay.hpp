/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_STORAGE_TRIE_DB_OVERLAY_HPP
#define KAGOME_STORAGE_TRIE_DB_OVERLAY_HPP

#include "storage/trie/trie_db.hpp"
#include "blockchain/changes_trie.hpp"

namespace kagome::storage::trie_db_overlay {

  class TrieDbOverlay : public trie::TrieDb {
   public:

    // commit all operations pending in memory to the main storage
    // insert all accumulated changes to the provided changes trie
    // clear the accumulated changes set
    virtual outcome::result<void> commitAndInsertChanges(
        blockchain::ChangesTrie &changes_trie) = 0;
  };

}  // namespace kagome::storage::trie_db_overlay

#endif  // KAGOME_STORAGE_TRIE_DB_OVERLAY_HPP