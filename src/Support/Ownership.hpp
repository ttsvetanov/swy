
/**
  Copyright(c) 2016 - 2017 Denis Blank <denis.blank at outlook dot com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
**/

#ifndef OWNERSHIP_HPP_INCLUDED__
#define OWNERSHIP_HPP_INCLUDED__

/// This class is responsible for holding an abstract copy- and
/// move-able ownership that is invalidated when the object
/// is moved to another instance.
class Ownership {
public:
  Ownership() = default;
  explicit Ownership(bool isOwning_) : isOwning(isOwning_) {}
  Ownership(Ownership const&) = default;
  Ownership(Ownership&& right) noexcept
      : isOwning(std::exchange(right.isOwning, false)){};
  Ownership& operator=(Ownership const&) = default;
  Ownership& operator=(Ownership&& right) noexcept {
    isOwning = std::exchange(right.isOwning, false);
    return *this;
  }

  Ownership operator&&(Ownership right) const noexcept {
    return Ownership(hasOwnership() && right.hasOwnership());
  }

  bool hasOwnership() const noexcept { return isOwning; }
  void invalidate() noexcept { isOwning = false; }

private:
  bool isOwning = true;
};

#endif // #ifndef OWNERSHIP_HPP_INCLUDED__
