#pragma once
#include <cstdint>
#include "./base_bitset.hpp"
class Bitset32 : public BaseBitset {
 public:
  Bitset32(uint32_t _bits) : BaseBitset(), bits(_bits) {}

  void push_back(bool val) override {
	bits <<= 1;
	bits |= val;
	++bitSize;
  }
  bool operator[](int index) const override {
	return get(index);
  }
  reference operator[](int index) override {
	return reference(this, index);
  }
  std::string toString() const override {
	const int sz = this->size();
	std::string ret;
	for (int i = sz - 1; i >= 0; --i) {
	  ret.push_back((*this)[i] ? '1' : '0');
	}
	return ret;
  }
  int size() const override { return bitSize; }
  Bitset32* clone() const override { return new Bitset32(*this); }
 protected:
  bool get(int index) const override {
	return (bits >> index) & 1U;
  }
  void set(int index) override {
	uint32_t mask = uint32_t(1) << index;
	bits |= mask;
  }
  void unset(int index) override {
	uint32_t mask = ~(uint32_t(1) << index);
	bits &= mask;
  }
 private:
  uint32_t bits;
  int bitSize = 0;
};
