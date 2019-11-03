#include "catch.hpp"
#include "code_word.hpp"
#include <sstream>
TEST_CASE("CodeWord", "[CodeWord]") {
  CodeWord w1(0b101, 3);
  CodeWord w2(0b0, 2);
  CodeWord w3(0b111111, 2);
  SECTION("Constructor works") {
	REQUIRE(w1.getCode() == 0b101);
	REQUIRE(w2.getCode() == 0b0);
	REQUIRE(w3.getCode() == 0b11);

	REQUIRE(w1.length() == 3);
	REQUIRE(w2.length() == 2);
	REQUIRE(w3.length() == 2);
	
  }

  SECTION("toBitString works") {
	REQUIRE(w1.toBitString() == "101");
	REQUIRE(w2.toBitString() == "00");
	REQUIRE(w3.toBitString() == "11");
  }

  SECTION("operator+ works") {
	REQUIRE((w1 + w3).toBitString() == w1.toBitString() + w3.toBitString());
	REQUIRE((w1 + w2).toBitString() == w1.toBitString() + w2.toBitString());
	REQUIRE((w3 + w2).toBitString() == w3.toBitString() + w2.toBitString());
  }

  SECTION("operator+= works") {
	CodeWord w1plus3 = w1 + w3;
	w1 += w3;
	REQUIRE(w1.getCode() == w1plus3.getCode());
  }

  SECTION("willFit works") {
	w1 = CodeWord(0, CodeWord::CODE_MAX - 2);
	REQUIRE(w1.willFit(CodeWord(0, 1)) == true);
	REQUIRE(w1.willFit(CodeWord(0, 2)) == true);
	REQUIRE(w1.willFit(CodeWord(0, 3)) == false);
  }

  SECTION("split works") {
	CodeWord whole(0b11111, 5);
	auto [ front, back ] = CodeWord::split(whole, 3);
	REQUIRE(front.getCode() == 0b111);
	REQUIRE(front.length() == 3);

	REQUIRE(back.getCode() == 0b11);
	REQUIRE(back.length() == 2);
  }

  SECTION("clear works") {
	w1.clear();
	REQUIRE(w1.getCode() == CodeWord().getCode());
	REQUIRE(w1.length() == CodeWord().length());
  }
}
