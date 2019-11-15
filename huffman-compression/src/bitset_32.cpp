#include "./bitset_32.hpp"

Bitset32::Bitset32(uint32_t _bits, int size)
    : BaseBitset(), bits(_bits), bitSize(size) {}

Bitset32::Bitset32() : Bitset32(0, 0) {}

void Bitset32::push_back(bool val) {
  bits <<= 1;
  bits |= val;
  ++bitSize;
}

bool Bitset32::operator[](int index) const { return get(index); }

Bitset32::reference Bitset32::operator[](int index) {
  return reference(this, index);
}

BaseBitset& Bitset32::operator++() {
  ++bits;
  return *this;
}

void Bitset32::clear() {
  bits = 0;
  bitSize = 0;
}

std::string Bitset32::toString() const {
  const int sz = this->size();
  std::string ret;
  for (int i = sz - 1; i >= 0; --i) {
    ret.push_back((*this)[i] ? '1' : '0');
  }
  return ret;
}

int Bitset32::size() const { return bitSize; }

Bitset32* Bitset32::clone() const { return new Bitset32(*this); }

unsigned char Bitset32::getByte(int index) const {
  return (bits >> (index * CHAR_BIT)) & 0b1111'1111;
}

bool Bitset32::get(int index) const { return (bits >> index) & 1U; }

void Bitset32::set(int index) {
  uint32_t mask = uint32_t(1) << index;
  bits |= mask;
}

void Bitset32::unset(int index) {
  uint32_t mask = ~(uint32_t(1) << index);
  bits &= mask;
}
