#ifndef H_CODE_WORD_ARRAY_BUILDER_H_
#define H_CODE_WORD_ARRAY_BUILDER_H_
#include <memory>

#include "./base_bitset.hpp"
#include "./bitset_32.hpp"
#include "./util.hpp"

// TODO: Currently, CodeWord only supports trees of height < 32-ish
// Although unlikely, trees can grow pass that limit. We should add
// support for such cases. Current idea is to have a CodeWordBase
// interface and depending on the height of the tree, switch between
// Classes inheriting from said interface.
// For short trees:
//	CodeWord(more performant, but fixed size)
// For tall trees:
//	some type of dynamic variant of CodeWord that can accomodate
//	longer codes but might be less performant.

// BaseCodeWord& code = chooseAppropriateCodeWord(tree);
template <typename FrequencyTree>
class CompressionCodesBuilder {
 public:
  using CompressionCodes = Huffman::CharSizedArray<std::unique_ptr<BaseBitset>>;
  using node_t = typename FrequencyTree::node_t;

  const CompressionCodes& buildFrom(const FrequencyTree& tree);
  const CompressionCodes& getArray() const { return compressionCodes; }

 private:
  CompressionCodes compressionCodes;
  void accumulateCodeWords(const node_t* node, BaseBitset* parent,
                           bool isLeft);
};

template <typename FrequencyTree>
const typename CompressionCodesBuilder<FrequencyTree>::CompressionCodes&
CompressionCodesBuilder<FrequencyTree>::buildFrom(const FrequencyTree& tree) {
  if (tree.getRoot()->getLeft() != nullptr)
    accumulateCodeWords(tree.getRoot()->getLeft(), new Bitset32(0), true);

  if (tree.getRoot()->getRight() != nullptr)
    accumulateCodeWords(tree.getRoot()->getRight(), new Bitset32(0), false);
  return compressionCodes;
}

template <typename FrequencyTree>
void CompressionCodesBuilder<FrequencyTree>::accumulateCodeWords(
    const node_t* node, BaseBitset* parent, bool isLeft) {
  BaseBitset* current = parent->clone();
  current->push_back(isLeft ? 0 : 1);

  if (node->hasChar()) {
    compressionCodes[node->getChar()].reset(current);
    // every node holding a character is a leaf node
    // so no need to go further
    return;
  }

  if (node->getLeft()) accumulateCodeWords(node->getLeft(), current, true);
  if (node->getRight()) accumulateCodeWords(node->getRight(), current, false);
  delete current;
}
#endif
