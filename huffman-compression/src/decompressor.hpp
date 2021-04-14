#pragma once
#include <exception>
#include "./base_bitset.hpp"
#include "./huffman_tree.hpp"
#include "./bitset.hpp"
#include "./huffman_tree.hpp"

class HuffmanTree;

class Decompressor {
 public:
  std::string decompress(const HuffmanTree& tree,
                         const BaseBitset& bits) const {
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

  std::string decompress(const HuffmanTree& tree,
                         const Bitset& bits) const {
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
