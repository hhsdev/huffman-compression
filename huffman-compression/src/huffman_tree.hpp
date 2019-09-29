#pragma once
#include <functional>
#include <queue>
#include "compressor.hpp"
#include "huffman_node.hpp"

class HuffmanTree {
  using ArrayFittingAllChars = Compressor::ArrayFittingAllChars;
  using PriorityQueue =
      std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>,
                          std::function<bool(const HuffmanNode* const,
                                             const HuffmanNode* const)>>;

 public:
  HuffmanTree(const ArrayFittingAllChars& frequencyCounts);
  const HuffmanNode* getRoot() const {
	return root;
  }
  ~HuffmanTree() {
    HuffmanNode* iterNode = root;
    recursiveDelete(root);
  }

 private:
  void recursiveDelete(const HuffmanNode* node) {
    if (node == nullptr) return;
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
      delete node;
      node == nullptr;
      return;
    }
    recursiveDelete(node->getLeft());
    recursiveDelete(node->getRight());
  }
  HuffmanTree::PriorityQueue makeNodesFromChars(
      const ArrayFittingAllChars& frequencyCounts);
  HuffmanNode* buildTree(PriorityQueue& nodes);
  HuffmanNode* root;
};
