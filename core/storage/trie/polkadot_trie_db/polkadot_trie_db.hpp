/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_CORE_STORAGE_TRIE_POLKADOT_TRIE_DB_POLKADOT_TRIE_DB_HPP
#define KAGOME_CORE_STORAGE_TRIE_POLKADOT_TRIE_DB_POLKADOT_TRIE_DB_HPP

#include <memory>
#include <optional>

#include "crypto/hasher.hpp"
#include "storage/trie/polkadot_trie_db/polkadot_codec.hpp"
#include "storage/trie/polkadot_trie_db/polkadot_node.hpp"
#include "storage/trie/polkadot_trie_db/polkadot_trie.hpp"
#include "storage/trie/trie_db.hpp"

namespace kagome::storage::trie {

  /**
   * A wrapper for PolkadotTrie that allows storing the trie in an external
   * storage that supports PersistentBufferMap interface
   */
  class PolkadotTrieDb : public TrieDb {
    using MapCursor = face::MapCursor<common::Buffer, common::Buffer>;
    using WriteBatch = face::WriteBatch<common::Buffer, common::Buffer>;
    using NodePtr = std::shared_ptr<PolkadotNode>;
    using BranchPtr = std::shared_ptr<BranchNode>;

    friend class PolkadotTrieBatch;

    // to output the trie into a stream
    template <typename Stream>
    friend Stream &operator<<(Stream &s, const PolkadotTrieDb &trie);
    template <typename Stream>
    friend Stream &printNode(Stream &s, const NodePtr &node,
                             const PolkadotTrieDb &trie, size_t nest_level);

   public:
    explicit PolkadotTrieDb(std::unique_ptr<PersistentBufferMap> db);

    ~PolkadotTrieDb() override = default;

    common::Buffer getRootHash() const override;

    outcome::result<void> clearPrefix(const common::Buffer &prefix) override;

    std::unique_ptr<WriteBatch> batch() override;

    // value will be copied
    outcome::result<void> put(const common::Buffer &key,
                              const common::Buffer &value) override;

    outcome::result<void> put(const common::Buffer &key,
                              common::Buffer &&value) override;

    outcome::result<void> remove(const common::Buffer &key) override;

    outcome::result<common::Buffer> get(
        const common::Buffer &key) const override;

    bool contains(const common::Buffer &key) const override;

    std::unique_ptr<MapCursor> cursor() override;

   private:
    /**
     * Creates an in-memory trie, which will fetch from the storage only the
     * nodes that are required to complete operations applied to the trie.
     * Usually it's the path from the root to the place of insertion/deletion
     */
    outcome::result<PolkadotTrie> initTrie() const;

    /**
     * Writes a node to a persistent storage, recursively storing its
     * descendants as well. Then replaces the node children to dummy nodes to
     * avoid memory waste
     */
    outcome::result<common::Buffer> storeNode(PolkadotNode &node);
    outcome::result<common::Buffer> storeNode(PolkadotNode &node,
                                              WriteBatch &batch);
    /**
     * Fetches a node from the storage. A nullptr is returned in case that there
     * is no entry for provided key. Mind that a branch node will have dummy
     * nodes as its children
     */
    outcome::result<NodePtr> retrieveNode(const common::Buffer &db_key) const;
    /**
     * Retrieves a node child, replacing a dummy node to an actual node if
     * needed
     */
    outcome::result<NodePtr> retrieveChild(const BranchPtr &parent,
                                           uint8_t idx) const;

    std::unique_ptr<PersistentBufferMap> db_;
    std::optional<common::Buffer> root_;
    PolkadotCodec codec_;
  };

}  // namespace kagome::storage::trie

#endif  // KAGOME_CORE_STORAGE_TRIE_POLKADOT_TRIE_DB_POLKADOT_TRIE_DB_HPP