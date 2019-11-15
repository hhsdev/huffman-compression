#pragma once
#include <functional>
#include <queue>

#include "./compressor.hpp"
#include "./huffman_node.hpp"
#include "./util.hpp"

class HuffmanTree {
 public:
  using node_t = HuffmanNode;
  using compare_func_t = std::function<bool(const node_t*, const node_t*)>;
  using PriorityQueue =
      std::priority_queue<node_t*, std::vector<node_t*>, compare_func_t>;

  HuffmanTree(const Huffman::CharSizedArray<uint32_t>& frequencyCounts);
  HuffmanTree(HuffmanNode* _root) : root(_root) {}
  HuffmanTree() : HuffmanTree(nullptr) {}

  const node_t* getRoot() const { return root; }
  int getHeight() const;
  ~HuffmanTree();

 private:
  void recursiveDelete(const node_t* node);
  PriorityQueue makeNodesFromChars(
      const Huffman::CharSizedArray<uint32_t>& frequencyCounts);
  node_t* buildTree(PriorityQueue& nodes);

  node_t* root;
};
