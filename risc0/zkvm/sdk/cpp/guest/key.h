// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/// @file key.h
/// @brief Cryptographic key

#pragma once

#include <cstddef>
#include <cstdint>

namespace risc0 {

class Env;
struct Digest;
class SHA256;

/// A pointer to a Digest.
using DigestPtr = const Digest*;

/// @brief KeyMode
enum class KeyMode : uint32_t {
  NEW,      ///< New
  EXISTING, ///< Existing
  ANY,      ///< Any
};

/// @brief A cryptographic key
/// @headerfile "risc0/zkvm/sdk/cpp/guest/key.h"
class Key {
  friend class Env;
  friend class SHA256;

public:
  /// Combine keys via XOR.
  Key(const Key& a, const Key& b);

  /// Commit to the key, i.e. Get the 'public' version of this key.
  DigestPtr commit() const;

  /// Support for (de)serialization.
  template <typename Archive> void transfer(Archive& ar) {
    for (uint32_t& word : data) {
      ar.transfer(word);
    }
  }

private:
  /// @private keys can only be generated by the Env.
  Key() = default;

private:
  uint32_t data[4];
};

/// A pointer to a Key.
using KeyPtr = const Key*;

} // namespace risc0