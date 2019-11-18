#include "./bitset_common.test.hpp"

TEMPLATE_TEST_CASE("Default constructed Bitset is empty",
                   "[BitsetCommon], [Bitset32], [DynamicBitset], "
                   "[StaticBitset], [StringViewBitset]",
                   (DynamicBitset<>), Bitset32, StringViewBitset,
                   (StaticBitset<uint64_t>)) {
  TestType bits;
  assertDataAndSizeEquals(bits, "");
}

TEMPLATE_TEST_CASE("Pushing back bits works as intended",
                   "[BitsetCommon], [Bitset32], [DynamicBitset], "
                   "[StaticBitset], [StringViewBitset]",
                   (DynamicBitset<>), Bitset32, StringViewBitset,
                   (StaticBitset<uint64_t>)) {
  const std::vector<std::string> testStrings = {"00001111", "10101010",
                                                "1111000011110000"};

  for (const std::string& testString : testStrings) {
    TestType bits;
    repeatedlyCallPushBack(bits, testString);
    assertDataAndSizeEquals(bits, testString);
  }
}

TEMPLATE_TEST_CASE("Incrementing bitset works as intended",
                   "[BitsetCommon], [Bitset32], [DynamicBitset], "
                   "[StaticBitset], [StringViewBitset]",
                   (DynamicBitset<>), Bitset32, /*TODO: StringViewBitset*/
                   (StaticBitset<uint64_t>)) {
  TestType bits;

  repeatedlyCallPushBack(bits, "00");
  ++bits;
  assertDataAndSizeEquals(bits, "01");
  ++bits;
  ++bits;
  assertDataAndSizeEquals(bits, "11");
  ++bits;
  assertDataAndSizeEquals(bits, "00");
}

TEMPLATE_TEST_CASE("Operator[] querying works as intended",
                   "[BitsetCommon], [Bitset32], [DynamicBitset], "
                   "[StaticBitset], [StringViewBitset]",
                   (DynamicBitset<>), Bitset32, StringViewBitset,
                   (StaticBitset<uint64_t>)) {
  TestType bits;
  repeatedlyCallPushBack(bits, "101010");

  assertEqualWithBrackets(bits, "101010");
}

TEMPLATE_TEST_CASE("Operator[] assignment works as intended",
                   "[BitsetCommon], [Bitset32], [DynamicBitset], "
                   "[StaticBitset], [StringViewBitset]",
                   (DynamicBitset<>), Bitset32, StringViewBitset,
                   (StaticBitset<uint64_t>)) {
  TestType bits;
  repeatedlyCallPushBack(bits, "101010");

  bits[1] = 0;
  bits[3] = 0;
  bits[5] = 0;

  assertEqualWithBrackets(bits, "000000");
}
