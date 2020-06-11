#pragma once
#include <iomanip>
#include <iostream>
#include <string>

class BaseBitset {
 public:
  class reference {
   public:
    reference(BaseBitset* _bitset, int _index)
        : bitset(_bitset), index(_index) {}

    reference& operator=(bool val) {
      if (val)
        bitset->set(index);
      else
        bitset->unset(index);
      return *this;
    }
    operator bool() const { return bitset->get(index); }

    bool operator~() const { return !bitset->get(index); }
    reference& flip() {
      bool val = bool(*this);
      if (val)
        bitset->unset(index);
      else
        bitset->set(index);
      return *this;
    }

   private:
    BaseBitset* bitset;
    int index;
  };

  BaseBitset() = default;
  virtual void assign(const BaseBitset& other) {
    this->clear();
    for (int i = other.size() - 1; i >= 0; --i) {
      this->push_back(other[i]);
    }
  }
  virtual void clear() = 0;
  virtual unsigned char getByte(int index) const = 0;
  virtual void push_back(bool val) = 0;
  virtual bool operator[](int index) const = 0;
  virtual reference operator[](int index) = 0;

  virtual BaseBitset& operator++() = 0;
  virtual std::string toString() const = 0;

  virtual int size() const = 0;
  virtual BaseBitset* clone() const = 0;
  virtual ~BaseBitset() = default;

 protected:
  virtual void set(int index) = 0;
  virtual void unset(int index) = 0;
  virtual bool get(int index) const = 0;
};
