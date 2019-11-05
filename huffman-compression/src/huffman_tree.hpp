#ifndef H_COMPRESSOR_HUFFMAN_TREE_H_
#define H_COMPRESSOR_HUFFMAN_TREE_H_
#include <functional>
#include <queue>

#include "./compressor.hpp"
#include "./util.hpp"

class HuffmanNode;

class HuffmanTree {
 public:
  using PriorityQueueCompareFunction =
      std::function<bool(const HuffmanNode*, const HuffmanNode*)>;
  using PriorityQueue =
      std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>,
                          PriorityQueueCompareFunction>;
  using node_t = HuffmanNode;
 public:
  const node_t* getRoot() const { return root; }
  HuffmanTree(const Huffman::CharSizedArray<int>& frequencyCounts);
  ~HuffmanTree();

 private:
  void recursiveDelete(const node_t* node);
  PriorityQueue makeNodesFromChars(
      const Huffman::CharSizedArray<int>& frequencyCounts);
 node_t* buildTree(PriorityQueue& nodes);
  node_t* root;
};
#endif  //! H_COMPRESSOR_HUFFMAN_TREE_H_
