#pragma once
#include <memory>

class HuffmanNode {
 public:
  HuffmanNode();
  HuffmanNode(char ch, int frequency);
  HuffmanNode(HuffmanNode& left, HuffmanNode& right);
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
  short setChar(unsigned char newCh) { ch = newCh; }
  int getFrequency() const { return frequency; }
  int getHeight() const { return height; }

  const HuffmanNode* getLeft() const { return left; }
  const HuffmanNode* getRight() const { return right; }
  
  HuffmanNode* getLeft() { return left; }
  HuffmanNode* getRight() { return right; }

  void setLeft(HuffmanNode *newLeft) { left = newLeft; }
  void setRight(HuffmanNode *newRight) { right = newRight; }

  bool operator<(const HuffmanNode& other) const;
  bool operator<=(const HuffmanNode& other) const;
  bool operator>(const HuffmanNode& other) const;
  bool operator>=(const HuffmanNode& other) const;
  bool operator==(const HuffmanNode& other) const;
  bool operator!=(const HuffmanNode& other) const;

 private:
  int calculateHeight() const;

  HuffmanNode* left;
  HuffmanNode* right;
  int frequency;
  short ch;
  int height;
};

