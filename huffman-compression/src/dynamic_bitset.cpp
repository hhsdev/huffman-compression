#include "./dynamic_bitset.hpp"

DynamicBitset::DynamicBitset() : container(), bitSize(0) {}

void DynamicBitset::push_back(bool val) {
  if (size() % CHAR_BIT == 0) container.push_front(0);
  container[0] <<= 1;
  for (int i = 1; i < container.size(); ++i) {
    // pass the most significant bit to the byte at the front
    container[i - 1] |= (container[i] >> (CHAR_BIT - 1));
    container[i] <<= 1;
  }
  container.back() |= val;
  ++bitSize;
}

BaseBitset& DynamicBitset::operator++() {
  for (int i = container.size() - 1; i >= 0; --i) {
	++container[i];
	if (container[i] != 0) { 
	  break;
	}
  }
}

void DynamicBitset::clear() {
  container.clear();
  bitSize = 0;
}

std::string DynamicBitset::toString() const {
  std::string ret;
  for (int i = bitSize - 1; i >= 0; --i) {
    ret.push_back(this->get(i) ? '1' : '0');
  }
  return ret;
}

bool DynamicBitset::operator[](int index) const { return get(index); }

DynamicBitset::reference DynamicBitset::operator[](int index) {
  return reference(this, index);
}

int DynamicBitset::size() const { return bitSize; }

BaseBitset* DynamicBitset::clone() const {
  return new DynamicBitset(*this);
}

unsigned char DynamicBitset::getByte(int index) const {
  return container[container.size() - index - 1];
}

bool DynamicBitset::get(int index) const {
  int byteIndex = toByte(index);
  int bitIndexWrtByte = bitInByte(index);
  unsigned char byte = container[container.size() - byteIndex - 1];
  return (byte >> bitIndexWrtByte) & 1U;
}

void DynamicBitset::set(int index) {
  int byteIndex = toByte(index);
  unsigned char mask = (unsigned char)1 << bitInByte(index);
  container[byteIndex] |= mask;
}

void DynamicBitset::unset(int index) {
  int byteIndex = toByte(index);
  unsigned char mask = ~((unsigned char)1 << bitInByte(index));
  container[byteIndex] &= mask;
}

int DynamicBitset::toByte(int index) const { return index / CHAR_BIT; }

int DynamicBitset::bitInByte(int index) const { return index % CHAR_BIT; }
