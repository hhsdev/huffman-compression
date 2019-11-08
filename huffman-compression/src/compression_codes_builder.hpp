#ifndef H_CODE_WORD_ARRAY_BUILDER_H_
#define H_CODE_WORD_ARRAY_BUILDER_H_
#include <memory>

#include "./base_bitset.hpp"
#include "./bitset_32.hpp"
#include "./dynamic_bitset.hpp"
#include "./util.hpp"

template <typename FrequencyTree>
class CompressionCodesBuilder {
 public:
  using CompressionCodes = Huffman::CharSizedArray<std::unique_ptr<BaseBitset>>;
  using node_t = typename FrequencyTree::node_t;

  const CompressionCodes& buildFrom(const FrequencyTree& tree);
  const CompressionCodes& getArray() const { return compressionCodes; }

 private:
  CompressionCodes compressionCodes;
  BaseBitset* chooseAppropriateBitset(const FrequencyTree& tree) const;
  void accumulateCodeWords(const node_t* node, BaseBitset* parent, bool isLeft);
};

template <typename FrequencyTree>
const typename CompressionCodesBuilder<FrequencyTree>::CompressionCodes&
CompressionCodesBuilder<FrequencyTree>::buildFrom(const FrequencyTree& tree) {
  std::unique_ptr<BaseBitset> baseBitset(chooseAppropriateBitset(tree));
  if (tree.getRoot()->getLeft() != nullptr)
    accumulateCodeWords(tree.getRoot()->getLeft(), baseBitset->clone(), true);

  if (tree.getRoot()->getRight() != nullptr)
    accumulateCodeWords(tree.getRoot()->getRight(), baseBitset->clone(), false);
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

template <typename FrequencyTree>
BaseBitset* CompressionCodesBuilder<FrequencyTree>::chooseAppropriateBitset(
    const FrequencyTree& tree) const {
  if (tree.getHeight() <= 32)
	return new Bitset32();
  else
	return new DynamicBitset();
}
#endif
