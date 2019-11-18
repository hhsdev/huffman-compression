#pragma once
#include <memory>

#include "./base_bitset.hpp"
#include "./bitset_32.hpp"
#include "./static_bitset.hpp"
#include "./dynamic_bitset.hpp"

std::unique_ptr<BaseBitset> getLargeEnoughBitset(int capacity);
