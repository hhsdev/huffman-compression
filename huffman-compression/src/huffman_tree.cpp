#include "huffman_tree.hpp"
#include <algorithm>
#include <iterator>
#include "./huffman_node.hpp"

#include <iostream>
HuffmanTree::HuffmanTree(const ArrayFittingAllChars &frequencyCounts) {
  PriorityQueue lowToHighFrequency = makeNodesFromChars(frequencyCounts);
  this->root = buildTree(lowToHighFrequency);
}

std::array<Prefix, Compressor::NUM_ALL_CHARS> HuffmanTree::buildPrefixArray() {
  std::array<Prefix, Compressor::NUM_ALL_CHARS> ret;
  traverseAndAddPrefixes(getRoot()->getLeft(), ret, Prefix(), true);
  traverseAndAddPrefixes(getRoot()->getRight(), ret, Prefix(), false);

  return ret;
}

void HuffmanTree::traverseAndAddPrefixes(
    const HuffmanNode *node, std::array<Prefix, Compressor::NUM_ALL_CHARS> &arr,
    const Prefix &parentPrefix, bool isLeftChild) {

  if (node == nullptr) return;
  Prefix currentPrefix = parentPrefix;
  currentPrefix.add(isLeftChild ? 0 : 1);

  if (node->getChar() >= 0) arr[node->getChar()] = currentPrefix;

  if (node->getLeft())
    traverseAndAddPrefixes(node->getLeft(), arr, currentPrefix, true);

  if (node->getRight())
    traverseAndAddPrefixes(node->getRight(), arr, currentPrefix, false);
}

HuffmanTree::PriorityQueue HuffmanTree::makeNodesFromChars(
    const ArrayFittingAllChars &frequencyCounts) {
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
  while (nodes.size() != 1) {
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
  HuffmanNode* iterNode = root;
  recursiveDelete(root);
}

