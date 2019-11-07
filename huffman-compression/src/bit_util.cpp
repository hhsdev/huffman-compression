#include "./bit_util.hpp"
namespace BitUtil {

std::pair<unsigned char, unsigned char> split(unsigned char byte,
                                              int frontBitsLength) {
  const int backBitsLength = CHAR_BIT - frontBitsLength;
  const unsigned char frontPart = byte >> backBitsLength;
  // this makes a mask with value 0b111..backBitsLength times..11
  const unsigned char mask = (1 << backBitsLength) - 1;
  const unsigned char backPart = byte & mask;
  
  return {frontPart, backPart};
}

}
