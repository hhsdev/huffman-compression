#include <iostream>
#include "catch.hpp"
#include "compressor.hpp"
#include "huffman_node.hpp"
#include "huffman_tree.hpp"

TEST_CASE("HuffmanTree", "[HuffmanTree]") {
  Huffman::CharSizedArray<int> charFrequencies = {};
  int aFrequency = 1, bFrequency = 2, cFrequency = 3;
  charFrequencies['a'] = aFrequency;
  charFrequencies['b'] = bFrequency;
  charFrequencies['c'] = cFrequency;

  HuffmanTree t(charFrequencies);
  SECTION("Constructor works") {
	// check nodes have correct frequency counts
    REQUIRE(t.getRoot()->getFrequency() == aFrequency + bFrequency + cFrequency);
    REQUIRE(t.getRoot()->getFrequency() == t.getRoot()->getLeft()->getFrequency() +
                                           t.getRoot()->getRight()->getFrequency());
  }

}
