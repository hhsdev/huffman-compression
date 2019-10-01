#ifndef H_COMPRESSOR_HUFFMAN_TREE_H_
#define H_COMPRESSOR_HUFFMAN_TREE_H_
#include <functional>
#include <queue>
#include "./huffman_node.hpp"
#include "./prefix.hpp"
#include "./compressor.hpp"

class HuffmanTree {
  using ArrayFittingAllChars = Compressor::ArrayFittingAllChars;
  using PriorityQueueCompareFunction =
      std::function<bool(const HuffmanNode*, const HuffmanNode*)>;
  using PriorityQueue =
      std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>,
                          PriorityQueueCompareFunction>;

 public:
  const HuffmanNode* getRoot() const { return root; }
  HuffmanTree(const ArrayFittingAllChars& frequencyCounts);
  std::array<Prefix, Compressor::NUM_ALL_CHARS> buildPrefixArray();
  void traverseAndAddPrefixes(
      const HuffmanNode* node,
      std::array<Prefix, Compressor::NUM_ALL_CHARS>& arr,
      const Prefix& parentPrefix, bool isLeft);
  ~HuffmanTree();

 private:
  void recursiveDelete(const HuffmanNode* node);
  HuffmanTree::PriorityQueue makeNodesFromChars(
      const ArrayFittingAllChars& frequencyCounts);
  HuffmanNode* buildTree(PriorityQueue& nodes);
  HuffmanNode* root;
};
#endif  //! H_COMPRESSOR_HUFFMAN_TREE_H_
