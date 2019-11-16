#include <string>

#include "./decompressor.test.hpp"
#include "./tree_reconstruction.hpp"
#include "./compressor.hpp"

TEST_CASE("Normal decompression usage", "[Decompressor]") {
  std::string uncompressedString = "Huffman coding is a data compression algorithm";
  
  Compressor c;
  Decompressor d;

  c.buildCodeTable(uncompressedString);
  c.compress(uncompressedString);

  HuffmanTree tree = TreeReconstruction::buildTree(c.getCodeTable());
  std::string output = d.decompress(tree, c.getBits());

  REQUIRE(output == uncompressedString);
}
