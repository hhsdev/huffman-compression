#include "catch.hpp"
#include "compressor.hpp"
#include <string>
#include <limits>

TEST_CASE("countOccurrences works", "[Compressor]") {

	std::string testString = "aabbbccdcce    ee e\ne";
	Compressor c;
	c.countFrequencies(testString);

	SECTION("Counts of occurring chars are correct") {
		REQUIRE(c.getFrequency('a') == 2);
		REQUIRE(c.getFrequency('b') == 3);
		REQUIRE(c.getFrequency('c') == 4);
		REQUIRE(c.getFrequency('d') == 1);
		REQUIRE(c.getFrequency('e') == 5);
	}

	SECTION("Counts of unoccurring chars are set to 0") {
		REQUIRE(c.getFrequency(0) == 0);
		REQUIRE(c.getFrequency('f') == 0);
		REQUIRE(c.getFrequency(CHAR_MAX) == 0);
	}
}
