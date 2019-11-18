#include "writer.hpp"
#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

TEST_CASE("writer", "[Writer]") {
  Writer w;
  // taken from https://www.techiedelight.com/huffman-coding/
  const std::string uncompressedString =
      "Huffman coding is a data compression algorithm.";
  const std::string compressedBitData =
      "000010000011110111101000010101101100111100001011101011000101111101001011"
      "010011001001011011010011001111001000101001010111010110011001111011001011"
      "01101011010000011100101011110110111111101000111111";

  std::istringstream input(uncompressedString);
  w.compress(input);
  std::stringstream output;
  w.write(output);
  std::ofstream f("out", std::ios::binary);
  f << output.str();
  output.seekg(0);
  char headerStartIndicator[5] = {0};
  output.read(headerStartIndicator, 4);

  REQUIRE(std::string(headerStartIndicator) == std::string("HEAD"));

  int metaDataSize =  Huffman::NUM_ALL_CHARS;
  output.seekg(std::string("HEAD").size() + metaDataSize);
  char dataStartIndicator[5] = {0};
  output.read(dataStartIndicator, 4);
  REQUIRE(std::string(dataStartIndicator) == std::string("DATA"));

  uint32_t sizeInByte, padding;
  output.read(reinterpret_cast<char*>(&sizeInByte), sizeof(sizeInByte));
  output.read(reinterpret_cast<char*>(&padding), sizeof(padding));

  //REQUIRE((sizeInByte * CHAR_BIT) - padding == compressedBitData.size());
}
