#include <cmath>

#include "./huffman_node.hpp"

HuffmanNode::HuffmanNode()
    : left(nullptr), right(nullptr), frequency(-1), ch(-1), height(0) {}

HuffmanNode::HuffmanNode(char ch, int frequency)
    : left(nullptr), right(nullptr), frequency(frequency), ch(ch), height(0) {}

HuffmanNode::HuffmanNode(const HuffmanNode& left, const HuffmanNode& right)
    : left(&left),
      right(&right),
      frequency(left.getFrequency() + right.getFrequency()),
      ch(-1) {
  height = calculateHeight();
}

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

int HuffmanNode::calculateHeight() const {
  int leftBranchHeight = left ? left->height : -1;
  int rightBranchHeight = right ? right->height : -1;

  return std::max(leftBranchHeight, rightBranchHeight) + 1;
}
