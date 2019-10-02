#ifndef H_COMPRESSOR_HUFFMAN_TREE_H_
#define H_COMPRESSOR_HUFFMAN_TREE_H_
#include <functional>
#include <queue>

#include "./compressor.hpp"
#include "./huffman_node.hpp"  // TODO: just use forward declaration
#include "./prefix.hpp"
#include "./util.hpp"

class HuffmanTree {
  using PriorityQueueCompareFunction =
      std::function<bool(const HuffmanNode*, const HuffmanNode*)>;
  using PriorityQueue =
      std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>,
                          PriorityQueueCompareFunction>;

 public:
  const HuffmanNode* getRoot() const { return root; }
  HuffmanTree(const Huffman::CharSizedArray<int>& frequencyCounts);
  Huffman::CharSizedArray<Prefix> buildPrefixArray();
  void accumulatePrefixes(const HuffmanNode* node,
                          Huffman::CharSizedArray<Prefix>& arr,
                          const Prefix& parentPrefix, bool isLeft);
  ~HuffmanTree();

 private:
  void recursiveDelete(const HuffmanNode* node);
  HuffmanTree::PriorityQueue makeNodesFromChars(
      const Huffman::CharSizedArray<int>& frequencyCounts);
  HuffmanNode* buildTree(PriorityQueue& nodes);
  HuffmanNode* root;

};
#endif  //! H_COMPRESSOR_HUFFMAN_TREE_H_
