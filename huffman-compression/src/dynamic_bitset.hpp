#pragma once

#include <deque>
#include <climits>
#include "./base_bitset.hpp"

class DynamicBitset : public BaseBitset {
 public:
  DynamicBitset() : container(), bitSize(0) {}

  void push_back(bool val) override {
	if (size() % CHAR_BIT == 0)
	  container.push_front(0);
	container[0] <<= 1;
    for (int i = 1; i < container.size(); ++i) {
	  // pass the most significant bit to the byte at the front
      container[i - 1] |= (container[i] >> (CHAR_BIT - 1));
	  container[i] <<= 1;
    }
	container.back() |= val;
	++bitSize;
  }
  
  std::string toString() const override {
	std::string ret;
	for (int i = bitSize - 1; i >= 0; --i) {
	  ret.push_back(this->get(i) ? '1' : '0');
	}
	return ret;
  }
  bool operator[](int index) const {
	return get(index);
  }
  reference operator[](int index) {
	return reference(this, index);
  }
  int size() const override { return bitSize; }

  BaseBitset* clone() const override {
	return new DynamicBitset(*this);
  }
 protected:
  bool get(int index) const override {
	int byteIndex = toByte(index);
	int bitIndexWrtByte = bitInByte(index);
	unsigned char byte = container[container.size() - byteIndex - 1];
	return (byte >> bitIndexWrtByte) & 1U;
  }
  void set(int index) override {
	int byteIndex = toByte(index);
	unsigned char mask = (unsigned char)1 << bitInByte(index);
	container[byteIndex] |= mask;
  }
  void unset(int index) override {
	int byteIndex = toByte(index);
	unsigned char mask = ~((unsigned char)1 << bitInByte(index));
	container[byteIndex] &= mask;
  }
 private:
  int toByte(int index) const { return index / CHAR_BIT; }
  int bitInByte(int index) const { return index % CHAR_BIT; }
  std::deque<unsigned char> container;
  int bitSize;
};
