#pragma once
#include <memory>
#include <climits>

#include "./base_bitset.hpp"
#include "./static_bitset.hpp"
#include "./dynamic_bitset.hpp"

std::unique_ptr<BaseBitset> getLargeEnoughBitset(int capacity);
