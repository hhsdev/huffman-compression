#pragma once
#include <memory>

class HuffmanNode {
 public:
  HuffmanNode();
  HuffmanNode(char ch, int frequency);
  HuffmanNode(const HuffmanNode& left, const HuffmanNode& right);
  HuffmanNode(const HuffmanNode& other)
	: left(other.left),
	  right(other.right),
	  frequency(other.frequency),
	  ch(other.ch)
  {}

  bool hasChar() const;
  short getChar() const;
  int getFrequency() const;
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
  int frequency;
  short ch;
};

