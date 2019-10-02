#include "catch.hpp"
#include "huffman_tree.hpp"
#include "compressor.hpp"
#include <iostream>
TEST_CASE("HuffmanTree", "[HuffmanTree]") {
	Huffman::CharSizedArray<int> arr = {};
	arr['a'] = 3;
	arr['b'] = 5;
	arr['c'] = 1;
	HuffmanTree t(arr);
	SECTION("Constructor works") {
		REQUIRE(t.getRoot()->getCount() == 9);
                REQUIRE(t.getRoot()->getCount() ==
                        t.getRoot()->getLeft()->getCount() +
                            t.getRoot()->getRight()->getCount());
        }

	SECTION("Correctly assigns prefixes") {
	  auto prefixes = t.buildPrefixArray();
	  REQUIRE(prefixes['b'].getCodeLength() == 1);
	  REQUIRE(prefixes['a'].getCodeLength() == 2);
	  REQUIRE(prefixes['c'].getCodeLength() == 2);
	  
	  REQUIRE(prefixes['b'].getCode() != prefixes['a'].getCode() >> 1);
	  REQUIRE(prefixes['b'].getCode() != prefixes['c'].getCode() >> 1);
	}

	SECTION("Codes are correctly packed into buffer") {
	}
}
