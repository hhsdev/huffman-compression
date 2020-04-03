#include <fstream>

#include "./compressor.hpp"
#include "catch.hpp"
#include "reader.hpp"

const std::string decompressedString =
    "Huffman coding is a data compression algorithm.";
// pretested decompressed code from a compression
const std::string compressedString = {
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

TEST_CASE("Decompression works", "[Reader]") {
  std::istringstream source(compressedString);
  Reader r;
  REQUIRE(r.decompress(source) == decompressedString);
}
