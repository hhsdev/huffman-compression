#include "./huffman_node.hpp"

HuffmanNode::HuffmanNode()
	: left(nullptr),
	  right(nullptr),
	  count(-1),
	  ch(-1)
{}

HuffmanNode::HuffmanNode(char ch, int count)
	: left(nullptr),
	  right(nullptr),
	  count(count),
	  ch(ch)
{}
HuffmanNode::HuffmanNode(const HuffmanNode& left,
		                 const HuffmanNode& right)
	: left(&left),
	  right(&right),
	  count(left.getCount() + right.getCount()),
	  ch(-1)
{}

short HuffmanNode::getChar() const {
	return ch;
}

int HuffmanNode::getCount() const {
	return count;
}

const HuffmanNode& HuffmanNode::getLeft() {
	return *left;
}
const HuffmanNode& HuffmanNode::getRight() {
	return *right;
}

bool HuffmanNode::operator<(const HuffmanNode& other) const {
	return this->getCount() < other.getCount();
}
bool HuffmanNode::operator<=(const HuffmanNode& other) const {
	return this->getCount() <= other.getCount();
}
bool HuffmanNode::operator>(const HuffmanNode& other) const {
	return this->getCount() > other.getCount();
}
bool HuffmanNode::operator>=(const HuffmanNode& other) const {
	return this->getCount() >= other.getCount();
}
bool HuffmanNode::operator==(const HuffmanNode& other) const {
	return this->getCount() == other.getCount();
}
bool HuffmanNode::operator!=(const HuffmanNode& other) const {
	return this->getCount() != other.getCount();
}
