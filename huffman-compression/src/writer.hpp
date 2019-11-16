#pragma once
#include <climits>
#include <cmath>
#include <iostream>

#include "./compressor.hpp"
#include "./metadata.hpp"
class Writer {
 public:
  Writer() = default;

  void compress(std::istream& source);
  void write(std::ostream& output);

 private:

  std::string getContents(std::istream& source);

  void writeHeaderChunk(std::ostream& output);
  void writeCompressionTable(std::ostream& output);
  std::string createRow(unsigned char c, const BaseBitset& code);
  void writeHeaderChunkSize(std::ostream& output);

  void writeDataChunk(std::ostream& output);
  void writeDataChunkSize(std::ostream& output);
  void writeDataPaddingSize(std::ostream& output);
  void writeCompressedData(std::ostream& output);
  
  uint32_t headerChunkSize = 0;
  Compressor compressor;
};
