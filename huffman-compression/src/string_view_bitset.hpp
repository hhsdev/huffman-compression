#pragma once
#include <string_view>
#include <cmath>
#include <set>

#include "./base_bitset.hpp"
#include "./dynamic_bitset.hpp"
#include "./bit_util.hpp"

// A class where you can pass in a string and view it like a bitset.
//
// The class guarantees that the string you pass in will not be modified.
// Indeed, its main purpose is read only. While all operations from
// BaseBitset interface are provided, they are likely slow.
class StringViewBitset : public BaseBitset {
 public:
  StringViewBitset();
  StringViewBitset(const std::string& str, int _bitSize);
  StringViewBitset(std::string_view _view, int _bitSize);
  
  void push_back(bool val) override;

  unsigned char getByte(int index) const override;
  bool operator[](int index) const override;
  reference operator[](int index);
  BaseBitset& operator++() override;
  
  std::string toString() const override;
  int size() const override;

  void clear() override;
  BaseBitset* clone() const;

 protected:
  void set(int index) override;
  void unset(int index) override;
  bool get(int index) const override;

 private:
  bool alreadySet(int index) const { return get(index) == 1; }
  bool alreadyUnset(int index) const { return get(index) == 0; }

  bool mapsToAdditions(int index) const { return index < additions.size(); }

  void setOnAdditions(int index) { additions[index] = 1; }
  void unsetOnAdditions(int index) { additions[index] = 0; }

  void setOnString(int index);
  void unsetOnString(int index);
  bool getFromString(int index) const;

  bool isOverridden(int index) const;
  void override(int index) { overrides.insert(index - additions.size()); }
  void removeOverride(int index) { overrides.erase(index - additions.size()); }

  std::string_view view;
  int bitSize;
  // since StringViewBitset doesn't change the underlying
  // string, extra objects are used to keep track of changes.
  // Size incrementing changes are kept in additions object
  // whereas changes to the string data are kept in overrides object.
  DynamicBitset<> additions;
  std::set<int> overrides;
};
