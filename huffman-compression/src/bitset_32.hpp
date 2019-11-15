#pragma once
#include <climits>
#include <cstdint>
#include "./base_bitset.hpp"
class Bitset32 : public BaseBitset {
 public:
  Bitset32();
  Bitset32(uint32_t _bits, int size);

  bool operator[](int index) const override;
  reference operator[](int index) override;
  BaseBitset& operator++() override;
  unsigned char getByte(int index) const override;

  void push_back(bool val) override;
  void clear() override;
  std::string toString() const override;

  int size() const override;

  Bitset32* clone() const override;

 protected:
  bool get(int index) const override;
  void set(int index) override;
  void unset(int index) override;

 private:
  uint32_t bits;
  int bitSize = 0;
};
