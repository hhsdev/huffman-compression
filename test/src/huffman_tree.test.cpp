#include "catch.hpp"
#include "huffman_tree.hpp"
#include "compressor.hpp"
TEST_CASE("HuffmanTree works", "[HuffmanTree]") {
	Compressor::ArrayFittingAllChars arr = {};
	arr['a'] = 3;
	arr['e'] = 5;
	SECTION("Constructor works") {
		HuffmanTree t(arr);
		REQUIRE(t.getRoot()->getCount() == 8);
		REQUIRE(((t.getRoot()->getLeft()->getCount() == 3 && t.getRoot()->getRight()->getCount() == 5) ||
				(t.getRoot()->getLeft()->getCount() == 5 && t.getRoot()->getRight()->getCount() == 3)));
	}
}
