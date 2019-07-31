/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "crypto/hasher/hasher_impl.hpp"

#include <gsl/span>

#include "crypto/blake2/blake2b.h"
#include "crypto/sha/sha256.hpp"
#include "crypto/twox/twox.hpp"

namespace kagome::crypto {

  HasherImpl::Hash128 HasherImpl::twox_128(
      gsl::span<const uint8_t> buffer) const {
    Hash128 out;
    crypto::make_twox128(buffer.data(), buffer.size(), out.data());
    return out;
  }

  HasherImpl::Hash256 HasherImpl::twox_256(
      gsl::span<const uint8_t> buffer) const {
    Hash256 out;
    crypto::make_twox256(buffer.data(), buffer.size(), out.data());
    return out;
  }

  HasherImpl::Hash256 HasherImpl::blake2_256(
      gsl::span<const uint8_t> buffer) const {
    Hash256 out;
    blake2b(out.data(), 32, nullptr, 0, buffer.data(), buffer.size());
    return out;
  }

  HasherImpl::Hash256 HasherImpl::sha2_256(
      gsl::span<const uint8_t> buffer) const {
    return crypto::sha256(buffer);
  }
}  // namespace kagome::hash
