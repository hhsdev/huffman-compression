#include "./huffman_tree.hpp"
#include <algorithm>
#include <iterator>

inline bool dereferenced_greater(const HuffmanNode* const a,
                          const HuffmanNode* const b) {
  return *a > *b;
}
HuffmanTree::HuffmanTree(const ArrayFittingAllChars &frequencyCounts) {
  PriorityQueue lowToHighFrequency = makeNodesFromChars(frequencyCounts);
  this->root = buildTree(lowToHighFrequency);
}

HuffmanTree::PriorityQueue HuffmanTree::makeNodesFromChars(
    const ArrayFittingAllChars &frequencyCounts) {
  HuffmanTree::PriorityQueue nodes(dereferenced_greater);
  for (int ch = 0; ch < frequencyCounts.size(); ++ch) {
	if (frequencyCounts[ch] > 0) {
	  nodes.push(new HuffmanNode(ch, frequencyCounts[ch]));
	}
  }
  return nodes;
}

HuffmanNode* HuffmanTree::buildTree(PriorityQueue &nodes) {
  while (nodes.size() != 1) {
    HuffmanNode *leftChildNode = new HuffmanNode(*nodes.top());
    nodes.pop();
    HuffmanNode *rightChildNode = new HuffmanNode(*nodes.top());
    nodes.pop();
	nodes.push(new HuffmanNode(*leftChildNode, *rightChildNode));
  }
  return nodes.top();
}
