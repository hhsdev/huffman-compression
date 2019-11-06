#include <algorithm>
#include <iostream>
#include <iterator>

#include "./code_word.hpp"
#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"

HuffmanTree::HuffmanTree(const Huffman::CharSizedArray<int> &frequencyCounts) {
  PriorityQueue lowToHighFrequencyNodes = makeNodesFromChars(frequencyCounts);
  this->root = buildTree(lowToHighFrequencyNodes);
}

HuffmanTree::PriorityQueue HuffmanTree::makeNodesFromChars(
    const Huffman::CharSizedArray<int> &frequencyCounts) {
  HuffmanTree::PriorityQueue nodes(
      [](const node_t *a, const node_t *b) { return *a > *b; });

  for (int ch = 0; ch < frequencyCounts.size(); ++ch) {
    if (frequencyCounts[ch] > 0) {
      nodes.push(new node_t(ch, frequencyCounts[ch]));
    }
  }
  return nodes;
}

HuffmanTree::node_t *HuffmanTree::buildTree(PriorityQueue &nodes) {
  while (nodes.size() > 1) {
    node_t *leftChild = new node_t(*nodes.top());
    nodes.pop();
    node_t *rightChild = new node_t(*nodes.top());
    nodes.pop();
    nodes.push(new node_t(*leftChild, *rightChild));
  }
  return nodes.top();
}

void HuffmanTree::recursiveDelete(const node_t *node) {
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
  node_t *iterNode = root;
  recursiveDelete(root);
}

