#include "catch.hpp"
#include "tree_reconstruction.hpp"

using LengthInfo = std::vector<std::pair<unsigned char, int>>;
using BranchInfo = std::vector<std::pair<unsigned char, std::string>>;

TreeReconstruction::CodeLengths setUpCodeLengths(const LengthInfo& input) {
  TreeReconstruction::CodeLengths codeLengths{0};
  for (const auto& [ch, length] : input) {
    codeLengths[ch] = length;
  }
  return codeLengths;
}

void verifyCharIsAtEndOfPathWay(const HuffmanTree& tree, unsigned char ch,
                                const std::string& pathway) {
  auto curr = tree.getRoot();
  for (char c : pathway) {
    if (c == 'l') curr = curr->getLeft();
    if (c == 'r') curr = curr->getRight();
  }
  REQUIRE(curr->getChar() == ch);
}

void verifyTreeHasCorrectBranches(const HuffmanTree& tree,
                                  const BranchInfo& input) {
  for (const auto& [ch, pathway] : input) {
    verifyCharIsAtEndOfPathWay(tree, ch, pathway);
  }
}

