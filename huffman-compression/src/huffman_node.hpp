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
  {
	height = calculateHeight();
  }

  bool hasChar() const { return ch >= 0; }
  short getChar() const { return ch; }
  int getFrequency() const { return frequency; }
  int getHeight() const { return height; }
  const HuffmanNode* getLeft() const { return left; }
  const HuffmanNode* getRight() const { return right; }
  
  bool operator<(const HuffmanNode& other) const;
  bool operator<=(const HuffmanNode& other) const;
  bool operator>(const HuffmanNode& other) const;
  bool operator>=(const HuffmanNode& other) const;
  bool operator==(const HuffmanNode& other) const;
  bool operator!=(const HuffmanNode& other) const;

 private:
  int calculateHeight() const;

  const HuffmanNode* left;
  const HuffmanNode* right;
  int frequency;
  short ch;
  int height;
};

