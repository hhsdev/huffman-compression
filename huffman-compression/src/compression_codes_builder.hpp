#ifndef H_CODE_WORD_ARRAY_BUILDER_H_
#define H_CODE_WORD_ARRAY_BUILDER_H_

#include "./code_word.hpp"
#include "./util.hpp"

template <typename FrequencyTree>
class CompressionCodesBuilder {
 public:
  using CompressionCodes = Huffman::CharSizedArray<CodeWord>;
  using node_t = typename FrequencyTree::node_t;

  const CompressionCodes& buildFrom(const FrequencyTree& tree);
  const CompressionCodes& getArray() const { return compressionCodes; }

 private:
  CompressionCodes compressionCodes;
  void accumulateCodeWords(const node_t* node, const CodeWord& parent,
                           bool isLeft);
};


const CompressionCodes& CompressionCodesBuilder::buildFrom(
    const FrequencyTree& tree) {
  if (tree.getRoot()->getLeft() != nullptr)
    accumulateCodeWords(tree.getRoot()->getLeft(), CodeWord(), true);

  if (tree.getRoot()->getRight() != nullptr)
    accumulateCodeWords(tree.getRoot()->getRight(), CodeWord(), false);

  return compressionCodes;
}

void CompressionCodesBuilder::accumulateCodeWords(const node_t* node,
                                                  const CodeWord& parent,
                                                  bool isLeft) {
  CodeWord current = parent;
  current.add(isLeft ? 0 : 1, 1);

  if (node->hasChar()) {
    compressionCodes[node->getChar()] = current;
    // every node holding a character is a leaf node
    // so no need to go further
    return;
  }

  if (node->getLeft()) accumulateCodeWords(node->getLeft(), current, true);
  if (node->getRight()) accumulateCodeWords(node->getRight(), current, false);
}
#endif
