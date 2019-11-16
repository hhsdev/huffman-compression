#pragma once

#include <deque>
#include <climits>
#include "./base_bitset.hpp"

class DynamicBitset : public BaseBitset {
 public:
  DynamicBitset();

  void push_back(bool val) override;
  
  bool operator[](int index) const;
  reference operator[](int index);
  BaseBitset& operator++() override;

  void clear() override;
  unsigned char getByte(int index) const override;

  int size() const override;

  std::string toString() const override;

  BaseBitset* clone() const override;

 protected:
  bool get(int index) const override;
  void set(int index) override;
  void unset(int index) override;

 private:
  std::deque<unsigned char> container;
  int bitSize;
};
