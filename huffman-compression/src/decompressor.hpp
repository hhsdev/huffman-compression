#pragma once
#include <exception>
#include "./huffman_tree.hpp"

class HuffmanTree;

class Decompressor {
 public:
  std::string decompress(const HuffmanTree& tree, const DynamicBitset& bits) const {
	std::string ret;
	const HuffmanNode* curr = tree.getRoot();
	if (!curr) {
	  throw std::runtime_error("Tree is empty");
	}
	for (int i = bits.size() - 1; i >= 0; --i) {
	  bool currentBit = bits[i];
	  if (currentBit) {
		curr = curr->getRight();
	  } else {
		curr = curr->getLeft();
	  }
	  if (!curr->getLeft() && !curr->getRight()) {
		ret.push_back(curr->getChar());
		curr = tree.getRoot();
	  }
	}
	return ret;
  }
};
