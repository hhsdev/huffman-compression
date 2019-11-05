#include "catch.hpp"
#include "huffman_node.hpp"

TEST_CASE("HuffmanNode", "[HuffmanNode]") {
  HuffmanNode leafNode1('a', 3);
  HuffmanNode leafNode2('b', 5);

  HuffmanNode branchNode(leafNode1, leafNode2);

  SECTION("Constructors") {
    REQUIRE(leafNode1.getChar() == 'a');
    REQUIRE(leafNode1.getFrequency() == 3);
    REQUIRE(leafNode2.getChar() == 'b');
    REQUIRE(leafNode2.getFrequency() == 5);

    REQUIRE(branchNode.getChar() == -1);
    REQUIRE(branchNode.getFrequency() ==
            leafNode1.getFrequency() + leafNode2.getFrequency());
  }

  SECTION("Comparisons") {
    REQUIRE(leafNode1 < leafNode2);
    REQUIRE(leafNode1 <= leafNode2);
    REQUIRE(leafNode2 > leafNode1);
    REQUIRE(leafNode2 >= leafNode1);
    REQUIRE(leafNode1 == leafNode1);
    REQUIRE(leafNode1 != leafNode2);
  }
}
