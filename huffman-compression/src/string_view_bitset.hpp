#pragma once
#include <string_view>
#include <cmath>
#include <unordered_set>
#include <set>

#include "./base_bitset.hpp"
#include "./dynamic_bitset.hpp"
#include "./bit_util.hpp"

// A class where you can pass in a string and view it like a bitset.
//
// The class guarantees that the string you pass in will not be modified.
// Its main purpose is read only. While write operations from
// BaseBitset interface are provided, they are likely slow.
class StringViewBitset : public BaseBitset {
 public:
  StringViewBitset();
  StringViewBitset(const std::string& str, const int _bitSize);
  StringViewBitset(const std::string_view _view, const int _bitSize);
  
  void push_back(const bool val) override;

  unsigned char getByte(const int index) const override;
  bool operator[](const int index) const override;
  reference operator[](const int index);
  BaseBitset& operator++() override;
  
  std::string toString() const override;
  int size() const override;

  void clear() override;
  BaseBitset* clone() const;
	
	virtual ~StringViewBitset() = default;
 protected:
  void set(const int index) override;
  void unset(const int index) override;
  bool get(const int index) const override;

 private:
  bool alreadySet(const int index) const { return get(index) == 1; }
  bool alreadyUnset(const int index) const { return get(index) == 0; }

  bool mapsToAdditions(const int index) const { return index < additions.size(); }

  void setOnAdditions(const int index) { additions[index] = 1; }
  void unsetOnAdditions(const int index) { additions[index] = 0; }

  void setOnString(const int index);
  void unsetOnString(const int index);
  bool getFromString(const int index) const;

  bool isOverridden(const int index) const;
  void override(const int index) { overrides.insert(index - additions.size()); }
  void removeOverride(const int index) { overrides.erase(index - additions.size()); }

  std::string_view view;
  int bitSize;
  // since StringViewBitset doesn't change the underlying
  // string, extra objects are used to keep track of changes.
  // Size incrementing changes are kept in additions object
  // whereas changes to the string data are kept in overrides object.
  DynamicBitset<> additions;
  std::unordered_set<int> overrides;
};

inline bool StringViewBitset::isOverridden(const int index) const {
  if (overrides.empty()) return false;
  return overrides.find(index - additions.size()) != overrides.end();
}

inline bool StringViewBitset::getFromString(const int index) const {
  int byteIndex = BitUtil::toByteIndex(index);
  int bitOffset = BitUtil::bitOffset(index);
  unsigned char byte = view[view.size() - byteIndex - 1];
  return BitUtil::nthBit(byte, bitOffset);
}

inline bool StringViewBitset::get(const int index) const {
	//TODO: Make a constant version of StringViewBitset 
	// so that we don't have to bother with all these checks
  return getFromString(index);
  //if (mapsToAdditions(index)) {
  //  return additions[index];
  //} else if (isOverridden(index)) {
  //  return !getFromString(index - additions.size());
  //} else {
  //  return getFromString(index - additions.size());
  //}
}
