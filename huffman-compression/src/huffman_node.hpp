#pragma once
#include <memory>

class HuffmanNode {
 public:
  HuffmanNode();
  HuffmanNode(char ch, int count);
  HuffmanNode(const HuffmanNode& left, const HuffmanNode& right);
  HuffmanNode(const HuffmanNode& other)
	: left(other.left),
	  right(other.right),
	  count(other.count),
	  ch(other.ch)
  {}

  short getChar() const;
  int getCount() const;
  const HuffmanNode* getLeft() const;
  const HuffmanNode* getRight() const;

  bool operator<(const HuffmanNode& other) const;
  bool operator<=(const HuffmanNode& other) const;
  bool operator>(const HuffmanNode& other) const;
  bool operator>=(const HuffmanNode& other) const;
  bool operator==(const HuffmanNode& other) const;
  bool operator!=(const HuffmanNode& other) const;

 private:
  const HuffmanNode* left;
  const HuffmanNode* right;
  int count;
  short ch;
};

