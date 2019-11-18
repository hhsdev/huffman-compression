#include "./string_view_bitset.hpp"

StringViewBitset::StringViewBitset(const std::string& str, int _bitSize)
    : view(str), bitSize(_bitSize) {}

StringViewBitset::StringViewBitset(std::string_view _view, int _bitSize)
    : view(_view), bitSize(_bitSize) {}

StringViewBitset::StringViewBitset() : view(""), bitSize(0) {}

void StringViewBitset::clear() {
  additions.clear();
  bitSize = 0;
}

unsigned char StringViewBitset::getByte(int index) const {
  int byteSizeInAdditions = BitUtil::toByteSize(additions.size());
  if (index < byteSizeInAdditions) {
    return additions.getByte(index);
  }
  return view[index - additions.size()];
}

void StringViewBitset::push_back(bool val) { additions.push_back(val); }

bool StringViewBitset::operator[](int index) const { return get(index); }

BaseBitset::reference StringViewBitset::operator[](int index) {
  return reference(this, index);
}

std::string StringViewBitset::toString() const {
  std::string ret;
  for (int i = size() - 1; i >= 0; --i) {
	ret.push_back(get(i) ? '1' : '0');
  }
  return ret;
}

int StringViewBitset::size() const { return bitSize + additions.size(); }

BaseBitset& StringViewBitset::operator++() { return *this; }

BaseBitset* StringViewBitset::clone() const {
  return new StringViewBitset(*this);
}

// TODO: these three functions are abominations; clean them
void StringViewBitset::set(int index) {
  if (mapsToAdditions(index)) {
    setOnAdditions(index);
  } else {
    setOnString(index);
  }
}

void StringViewBitset::unset(int index) {
  if (mapsToAdditions(index)) {
    unsetOnAdditions(index);
  } else {
    unsetOnString(index);
  }
}

bool StringViewBitset::get(int index) const {
  if (mapsToAdditions(index)) {
    return additions[index];
  } else if (isOverridden(index)) {
    return !getFromString(index - additions.size());
  } else {
    return getFromString(index - additions.size());
  }
}

bool StringViewBitset::getFromString(int index) const {
  int byteIndex = BitUtil::toByteIndex(index);
  int bitOffset = BitUtil::bitOffset(index);
  unsigned char byte = view[view.size() - byteIndex - 1];
  return BitUtil::nthBit(byte, bitOffset);
}

void StringViewBitset::setOnString(int index) {
  if (alreadySet(index)) return;
  if (isOverridden(index)) removeOverride(index);
  else override(index);
}

void StringViewBitset::unsetOnString(int index) {
  if (alreadyUnset(index)) return;
  if (isOverridden(index)) removeOverride(index);
  else override(index);
}

bool StringViewBitset::isOverridden(int index) const {
  return overrides.find(index - additions.size()) != overrides.end();
}
