#include <algorithm>
#include <iostream>
#include <iterator>

#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"
#include "./code_word.hpp"

HuffmanTree::HuffmanTree(const Huffman::CharSizedArray<int> &frequencyCounts) {
  PriorityQueue lowToHighFrequencyNodes = makeNodesFromChars(frequencyCounts);
  this->root = buildTree(lowToHighFrequencyNodes);
}

HuffmanTree::PriorityQueue HuffmanTree::makeNodesFromChars(
    const Huffman::CharSizedArray<int> &frequencyCounts) {
  HuffmanTree::PriorityQueue nodes(
      [](const HuffmanNode *a, const HuffmanNode *b) { return *a > *b; });

  for (int ch = 0; ch < frequencyCounts.size(); ++ch) {
    if (frequencyCounts[ch] > 0) {
      nodes.push(new HuffmanNode(ch, frequencyCounts[ch]));
    }
  }
  return nodes;
}

HuffmanNode *HuffmanTree::buildTree(PriorityQueue &nodes) {
  while (nodes.size() > 1) {
    HuffmanNode *leftChildNode = new HuffmanNode(*nodes.top());
    nodes.pop();
    HuffmanNode *rightChildNode = new HuffmanNode(*nodes.top());
    nodes.pop();
    nodes.push(new HuffmanNode(*leftChildNode, *rightChildNode));
  }
  return nodes.top();
}

void HuffmanTree::recursiveDelete(const HuffmanNode *node) {
  if (node == nullptr) return;
  if (node->getLeft() == nullptr && node->getRight() == nullptr) {
    delete node;
    node == nullptr;
    return;
  }
  recursiveDelete(node->getLeft());
  recursiveDelete(node->getRight());
}

HuffmanTree::~HuffmanTree() {
  HuffmanNode *iterNode = root;
  recursiveDelete(root);
}

