#include "./all_bitsets.hpp"

std::unique_ptr<BaseBitset> getLargeEnoughBitset(int capacity) {
  if (capacity <= sizeof(unsigned long) * CHAR_BIT)
	return std::unique_ptr<BaseBitset>(new StaticBitset<>());
  
  return std::unique_ptr<BaseBitset>(new DynamicBitset<>());
}
