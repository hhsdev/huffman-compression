#include "./writer.hpp"
#include "./util.hpp"
#include "./bit_util.hpp"

#include <sstream>

void Writer::compress(std::istream& source) {
  std::string buffer = getContents(source);
  compressor.buildCodeTable(buffer);
  compressor.compress(buffer);
}

void Writer::write(std::ostream& output) {
  writeHeaderChunk(output);
  writeDataChunk(output);
}

std::string Writer::getContents(std::istream& source) {
  std::ostringstream sstr;
  sstr << source.rdbuf();
  return sstr.str();
}

void Writer::writeHeaderChunk(std::ostream& output) {
  output << MetaData().createMetaData(compressor);
}

void Writer::writeDataChunk(std::ostream& output) {
  output << "DATA";
  writeDataChunkSize(output);
  writeDataPaddingSize(output);
  writeCompressedData(output);
}

void Writer::writeCompressionTable(std::ostream& output) {
  for (int ch = 0; ch < Huffman::NUM_ALL_CHARS; ++ch) {
    const BaseBitset& code = compressor.getCode(ch);
    if (code.size() > 0) {
      std::string row = createRow(ch, code);
      output << row;
      headerChunkSize += row.size();
    }
  }
}

void Writer::writeHeaderChunkSize(std::ostream& output) {
  output.seekp(std::string("HEAD").size());
  std::cout << "Header chunk size: " << headerChunkSize << std::endl;
  output.write(reinterpret_cast<char*>(&headerChunkSize),
               sizeof(headerChunkSize));
  output.seekp(0, std::ios_base::end);
}

std::string Writer::createRow(unsigned char c, const BaseBitset& code) {
  // Format:
  // {1 byte of character}{1 byte for length of bits}
  // {0-7 bits of padding}{compressed bits}
  std::string buffer;
  buffer.push_back(c);
  buffer.push_back((unsigned char)code.size());
  const int sizeInByte = std::ceil(code.size() / (double)CHAR_BIT);
  for (int i = sizeInByte - 1; i >= 0; --i) {
    buffer.push_back(code.getByte(i));
  }
  return buffer;
}

void Writer::writeDataChunkSize(std::ostream& output) {
  uint32_t bitSize = compressor.getBits().size();
  uint32_t byteSize = BitUtil::toByteSize(bitSize);
  output.write(reinterpret_cast<char*>(&byteSize), sizeof(byteSize));
}

void Writer::writeDataPaddingSize(std::ostream& output) {
  unsigned char padding = CHAR_BIT - compressor.getBits().size() % CHAR_BIT;
  if (padding == CHAR_BIT) padding = 0;
  output.write(reinterpret_cast<char*>(&padding), sizeof(padding));
}

void Writer::writeCompressedData(std::ostream& output) {
  const auto& bits = compressor.getBits();
  int byteSize = BitUtil::toByteSize(bits.size());
  for (int i = byteSize - 1; i >= 0; --i) {
	output << bits.getByte(i);
  }
}
