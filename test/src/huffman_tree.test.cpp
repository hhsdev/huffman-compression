#include <iostream>
#include "catch.hpp"
#include "compressor.hpp"
#include "huffman_node.hpp"
#include "huffman_tree.hpp"

TEST_CASE("HuffmanTree", "[HuffmanTree]") {
  Huffman::CharSizedArray<uint32_t> charFrequencies = {};
  int aFrequency = 1, bFrequency = 2, cFrequency = 3;
  charFrequencies['a'] = aFrequency;
  charFrequencies['b'] = bFrequency;
  charFrequencies['c'] = cFrequency;

  HuffmanTree t(charFrequencies);
  SECTION("Construction") {
    auto root = t.getRoot();
    auto leftChild = root->getLeft();
    auto rightChild = root->getRight();
    // check for correct frequency counts
    REQUIRE(root->getFrequency() == aFrequency + bFrequency + cFrequency);
    REQUIRE(root->getFrequency() ==
            leftChild->getFrequency() + rightChild->getFrequency());

	// check for correct heights
	REQUIRE(t.getHeight() == root->getHeight());
    REQUIRE(root->getHeight() == 2);
	REQUIRE(std::min(leftChild->getHeight(), rightChild->getHeight()) == 0);
	REQUIRE(std::max(leftChild->getHeight(), rightChild->getHeight()) == 1);
  }
}
