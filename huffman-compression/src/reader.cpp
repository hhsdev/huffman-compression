#include "./reader.hpp"

const std::string Reader::headMagicBytes = "HEAD";
const std::string Reader::bodyMagicBytes = "DATA";

std::string Reader::decompress(std::istream& source) {
  std::string contents = getContents(source);
  if (!this->isWellFormed(contents))
    throw std::runtime_error("Wrong file type");

  Huffman::CharSizedArray<unsigned char> codeLengths =
      this->extractHead(contents);
  HuffmanTree tree = TreeReconstruction::reconstructFrom(codeLengths);
  return mDecompressor.decompress(tree, extractBitset(contents));
}

Huffman::CharSizedArray<unsigned char> Reader::extractHead(
    const std::string& contents) {
  Huffman::CharSizedArray<unsigned char> ret;
  const int offset = headMagicBytes.size();
  for (int i = offset, ch = 0; i < Huffman::NUM_ALL_CHARS + offset; ++i, ++ch) {
    int chLength = contents[i];
    ret[ch] = chLength;
  }
  return ret;
}

Bitset Reader::extractBitset(const std::string& contents) {
  const int paddingByteSize = 1;
  const int paddingByteLocation = headMagicBytes.size() +
                                  Huffman::NUM_ALL_CHARS +
                                  bodyMagicBytes.size() + 4;
  const int padding = contents[paddingByteLocation];
  std::string_view view = contents;
  view = view.substr(paddingByteLocation + 1);
  return Bitset(view, view.size() * CHAR_BIT - padding);
}


StringViewBitset Reader::extractData(const std::string& contents) {
  const int paddingByteSize = 1;
  const int paddingByteLocation = headMagicBytes.size() +
                                  Huffman::NUM_ALL_CHARS +
                                  bodyMagicBytes.size() + 4;
  const int padding = contents[paddingByteLocation];
  std::string_view view = contents;
  view = view.substr(paddingByteLocation + 1);
  return StringViewBitset(view, view.size() * CHAR_BIT - padding);
}

bool Reader::isWellFormed(const std::string& contents) {
	if (contents.empty()) return false;	
  return contents.substr(0, 4) == headMagicBytes;
}

std::string Reader::getContents(std::istream& source) {
  std::ostringstream sstr;
  sstr << source.rdbuf();
  return sstr.str();
}
