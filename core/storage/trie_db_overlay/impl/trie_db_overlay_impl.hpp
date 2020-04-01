/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_STORAGE_TRIE_DB_OVERLAY_IMPL_HPP
#define KAGOME_STORAGE_TRIE_DB_OVERLAY_IMPL_HPP

#include <boost/optional.hpp>

#include "primitives/extrinsic.hpp"
#include "storage/trie_db_overlay/trie_db_overlay.hpp"

namespace kagome::storage::trie_db_overlay {

  class TrieDbOverlayImpl : public TrieDbOverlay {
   public:
    explicit TrieDbOverlayImpl(std::shared_ptr<trie::TrieDb> main_db);
    ~TrieDbOverlayImpl() override = default;

    outcome::result<void> commitAndInsertChanges(
        blockchain::ChangesTrie &changes_trie) override;

    std::unique_ptr<face::WriteBatch<Buffer, Buffer>> batch() override;
    std::unique_ptr<face::MapCursor<Buffer, Buffer>> cursor() override;
    outcome::result<Buffer> get(const Buffer &key) const override;
    bool contains(const Buffer &key) const override;
    outcome::result<void> put(const Buffer &key, const Buffer &value) override;
    outcome::result<void> put(const Buffer &key, Buffer &&value) override;
    outcome::result<void> remove(const Buffer &key) override;
    outcome::result<void> clearPrefix(const common::Buffer &buf) override;
    Buffer getRootHash() override;
    bool empty() const override;

   private:
    static const common::Buffer EXTRINSIC_INDEX_KEY;

    static constexpr uint32_t NO_EXTRINSIC_INDEX = 0xffffffff;

    primitives::ExtrinsicIndex getExtrinsicIndex() const;

    struct ChangedValue {
      boost::optional<common::Buffer> value;
      std::vector<primitives::ExtrinsicIndex> changers;
    };
    std::map<common::Buffer, ChangedValue> changes_;
    std::shared_ptr<trie::TrieDb> storage_;
  };

}  // namespace kagome::storage::trie_db_overlay

#endif  // KAGOME_STORAGE_TRIE_DB_OVERLAY_IMPL_HPP