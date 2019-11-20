#include <fstream>

#include "./compressor.hpp"
#include "catch.hpp"
#include "reader.hpp"
// pretested result from a compression
const std::string fixtureCodeString = {
    72,  69,  65,  68,  0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   3,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   6,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  6,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   3,  0,   5,  5,   5,   4,  5,  6,  4,    0,   0,
    5,   4,   4,   3,   5,   0,  5,   4,  5,   6,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   0,   0,  0,   0,  0,   0,   0,  0,  0,  0,    0,   0,
    0,   0,   0,   0,   68,  65, 84,  65, 25,  0,   0,  0,  6,  3,    -33, -39,
    -96, -56, -78, -69, -50, 67, -48, 34, -25, -92, 89, 70, -7, -118, -89, 82,
    14,  -78, -72, -3,  -6,  60};

TEST_CASE("Code table is extracted properly", "[Reader]") {
  Reader r;
  auto output = r.extractHead(fixtureCodeString);
  REQUIRE(output.size() == Huffman::NUM_ALL_CHARS);
}

TEST_CASE("Data is extracted properly", "[Reader]") {
  Reader r;
  auto output = r.extractData(fixtureCodeString);
  REQUIRE(output.size() == 194);
}

TEST_CASE("Decompression works", "[Reader]") {
  std::istringstream source(fixtureCodeString);
  Reader r;
  REQUIRE(r.decompress(source) == "Huffman coding is a data compression algorithm.");
}
