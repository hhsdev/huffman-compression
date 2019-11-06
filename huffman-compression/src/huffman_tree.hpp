#ifndef H_COMPRESSOR_HUFFMAN_TREE_H_
#define H_COMPRESSOR_HUFFMAN_TREE_H_
#include <functional>
#include <queue>

#include "./compressor.hpp"
#include "./util.hpp"

class HuffmanNode;

class HuffmanTree {
 public:
  using node_t = HuffmanNode;
  using compare_func_t =
      std::function<bool(const node_t*, const node_t*)>;
  using PriorityQueue = std::priority_queue<node_t*, std::vector<node_t*>,
                                            compare_func_t>;

  const node_t* getRoot() const { return root; }
  int getHeight() const { return root->getHeight(); 
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
