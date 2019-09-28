#include "catch.hpp"
#include "huffman_node.hpp"

TEST_CASE("HuffmanNode works", "[HuffmanNode]") {
	HuffmanNode leafNode1('a', 3);
	HuffmanNode leafNode2('b', 5);

	HuffmanNode branchNode(leafNode1, leafNode2);

	SECTION("Constructors work") {
		REQUIRE(leafNode1.getChar() == 'a');
		REQUIRE(leafNode1.getCount() == 3);
		REQUIRE(leafNode2.getChar() == 'b');
		REQUIRE(leafNode2.getCount() == 5);

		REQUIRE(branchNode.getChar() == -1);
		REQUIRE(branchNode.getCount() == leafNode1.getCount()
									   + leafNode2.getCount());
	}

	SECTION("Comparisons work") {
		REQUIRE(leafNode1 < leafNode2);
		REQUIRE(leafNode1 <= leafNode2);
		REQUIRE(leafNode2 > leafNode1);
		REQUIRE(leafNode2 >= leafNode1);
		REQUIRE(leafNode1 == leafNode1);
		REQUIRE(leafNode1 != leafNode2);
	}
}
