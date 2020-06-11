#pragma once
#include <string>
#include "./base_bitset.hpp"

template <typename Block = unsigned long>
class StaticBitset : public BaseBitset {
 public:
  using block_type = Block;

  StaticBitset();
  StaticBitset(block_type _bits, int _bitSize);

  void clear() override;

  unsigned char getByte(int index) const override;

  void push_back(bool val) override;
  bool operator[](int index) const override;
  reference operator[](int index) override;

  virtual BaseBitset& operator++();

  std::string toString() const override;

  int size() const override { return bitSize; }
  BaseBitset* clone() const { return new StaticBitset(*this); }
  virtual ~StaticBitset() = default;

 protected:
  void set(int index) override;
  void unset(int index) override;
  bool get(int index) const override { return (bits >> index) & block_type(1); }

 private:
  block_type bits;
  int bitSize;
};

template <typename Block>
StaticBitset<Block>::StaticBitset() : StaticBitset(0, 0) {}

template <typename Block>
StaticBitset<Block>::StaticBitset(block_type _bits, int _bitSize)
    : BaseBitset(), bits(_bits), bitSize(_bitSize) {}

template <typename Block>
void StaticBitset<Block>::clear() {
  bits = 0;
  bitSize = 0;
}

template <typename Block>
unsigned char StaticBitset<Block>::getByte(int index) const {
  return (bits >> (index * CHAR_BIT)) & 0b1111'1111;
}

template <typename Block>
void StaticBitset<Block>::push_back(bool val) {
  bits <<= 1;
  bits |= val;
  ++bitSize;
}

template <typename Block>
bool StaticBitset<Block>::operator[](int index) const {
  return get(index);
}

template <typename Block>
BaseBitset::reference StaticBitset<Block>::operator[](int index) {
  return reference(this, index);
}

template <typename Block>
BaseBitset& StaticBitset<Block>::operator++() {
  ++bits;
  return *this;
}

template <typename Block>
std::string StaticBitset<Block>::toString() const {
  const int sz = this->size();
  std::string ret;
  for (int i = sz - 1; i >= 0; --i) {
    ret.push_back((*this)[i] ? '1' : '0');
  }
  return ret;
}

template <typename Block>
void StaticBitset<Block>::set(int index) {
  block_type mask = block_type(1) << index;
  bits |= mask;
}

template <typename Block>
void StaticBitset<Block>::unset(int index) {
  block_type mask = ~(block_type(1) << index);
  bits &= mask;
}
