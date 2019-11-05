#include "./huffman_node.hpp"

HuffmanNode::HuffmanNode()
    : left(nullptr), right(nullptr), frequency(-1), ch(-1) {}

HuffmanNode::HuffmanNode(char ch, int frequency)
    : left(nullptr), right(nullptr), frequency(frequency), ch(ch) {}

HuffmanNode::HuffmanNode(const HuffmanNode& left, const HuffmanNode& right)
    : left(&left),
      right(&right),
      frequency(left.getFrequency() + right.getFrequency()),
      ch(-1) {}

bool HuffmanNode::hasChar() const { return ch >= 0; }

short HuffmanNode::getChar() const { return ch; }

int HuffmanNode::getFrequency() const { return frequency; }

const HuffmanNode* HuffmanNode::getLeft() const { return left; }

const HuffmanNode* HuffmanNode::getRight() const { return right; }

bool HuffmanNode::operator<(const HuffmanNode& other) const {
  return getFrequency() < other.getFrequency();
}

bool HuffmanNode::operator<=(const HuffmanNode& other) const {
  return getFrequency() <= other.getFrequency();
}

bool HuffmanNode::operator>(const HuffmanNode& other) const {
  return getFrequency() > other.getFrequency();
}

bool HuffmanNode::operator>=(const HuffmanNode& other) const {
  return getFrequency() >= other.getFrequency();
}

bool HuffmanNode::operator==(const HuffmanNode& other) const {
  return getFrequency() == other.getFrequency();
}

bool HuffmanNode::operator!=(const HuffmanNode& other) const {
  return getFrequency() != other.getFrequency();
}

