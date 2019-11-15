#include "./all_bitsets.hpp"

std::unique_ptr<BaseBitset> getLargeEnoughBitset(int capacity) {
  if (capacity <= 32)
	return std::unique_ptr<BaseBitset>(new Bitset32());
  return std::unique_ptr<BaseBitset>(new DynamicBitset());
}
