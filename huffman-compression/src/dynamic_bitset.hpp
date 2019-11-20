#pragma once
#include <cassert>
#include <deque>
#include <vector>
#include <iostream>
#include <climits>
#include "./base_bitset.hpp"

namespace IndexOperations {

template <typename Block>
int bitToBlock(int bitIndex) {
  return bitIndex / (sizeof(Block) * CHAR_BIT);
}

template <typename Block>
int byteToBlock(int byteIndex) {
  return byteIndex / sizeof(Block);
}

template <typename Block>
int bitOffset(int bitIndex) {
  return bitIndex % (sizeof(Block) * CHAR_BIT);
}

template <typename Block>
int byteOffset(int byteIndex) {
  return byteIndex % sizeof(Block);
}

}  // namespace IndexOperations

template <typename Block = uint64_t>
class DynamicBitset : public BaseBitset {
 public:
  using block_type = Block; 
  DynamicBitset() : BaseBitset(), blocks(), bufferBlock(0), bufferBlockSize(0) {}
  
  void push_back(bool val) override {
	if (bufferBlockSize == sizeof(bufferBlock) * CHAR_BIT) {
	  blocks.push_back(bufferBlock);
	  bufferBlock = val;
	  bufferBlockSize = 1;
	}
	else {
	  bufferBlock = (bufferBlock << 1) | val;
	  ++bufferBlockSize;
	}
  }

  bool operator[](int bitIndex) const override {
	return get(bitIndex);
  }

  reference operator[](int index) {
	return reference(this, index);
  }

  BaseBitset& operator++() override {
	++bufferBlock;
	if (!isPowerOf2(bufferBlock)) return *this;
	Block mask = ~Block(0) >> (sizeof(Block) * CHAR_BIT - bufferBlockSize);
	bufferBlock &= mask;
	const int numBlocks = blocks.size();
	for (int i = 0; i < numBlocks; ++i) {
	  ++blocks[i];
	  // we will break out of the loop unless the incremented block overflows
	  if (blocks[i] != 0) {
		break;
	  }
	}
	return *this;
  }


  void clear() override {
	blocks.clear();
	bufferBlock = 0;
	bufferBlockSize = 0;
  }

  unsigned char getByte(int byteIndex) const override {
	unsigned char ret = 0;
	const int bitIndex = byteIndex * CHAR_BIT;
	for (int i = std::min(bitIndex + CHAR_BIT - 1, size() - 1); i >= bitIndex; --i) {
	  ret = (ret << 1) | get(i);
	}
	return ret;
  }

  int size() const override { return bufferBlockSize + (blocks.size() * sizeof(Block) * CHAR_BIT); }

  std::string toString() const override {
	std::string ret;
	const int sz = size();
	for (int i = sz - 1; i >= 0; --i) {
	  ret.push_back(get(i) ? '1' : '0');
	}
	return ret;
  }

  BaseBitset* clone() const override { return new DynamicBitset(*this); }

 protected:
  bool get(int bitIndex) const override {
	if (bitIndex < bufferBlockSize) {
	  return nthBit(bufferBlock, bitIndex);
	} else {
	  int adjustedBitIndex = bitIndex - bufferBlockSize;
	  int blockIndex = blocks.size() - 1 - (adjustedBitIndex / (sizeof(Block) * CHAR_BIT));
	  int bitOffset = adjustedBitIndex % (sizeof(Block) * CHAR_BIT);
	  return nthBit(blocks[blockIndex], bitOffset);
	}
  }

  bool nthBit(Block block, int index) const {
	return (block >> index) & 1;
  }

  unsigned char nthByte(Block block, int index) const {
	return (block >> (index * CHAR_BIT)) & 0b1111'1111;
  }

  void set(int bitIndex) override {
	if (bitIndex < bufferBlockSize) {
	  const int bitOffset = IndexOperations::bitOffset<Block>(bitIndex);
	  const Block mask = Block(1) << bitOffset;
	  bufferBlock |= mask;
	} else {
	  bitIndex -= bufferBlockSize;
	  auto blockIndex = IndexOperations::bitToBlock<Block>(bitIndex);
	  auto bitOffset = IndexOperations::bitOffset<Block>(bitIndex);
	  Block mask = Block(1) << bitOffset;	
	  blocks[blockIndex] |= mask;
	}
  }

  void unset(int bitIndex) override {
	if (bitIndex < bufferBlockSize) {
	  auto bitOffset = IndexOperations::bitOffset<Block>(bitIndex);
	  Block mask = ~(Block(1) << bitOffset);
	  bufferBlock &= mask;
	} else {
	  bitIndex -= bufferBlockSize;
	  auto blockIndex = IndexOperations::bitToBlock<Block>(bitIndex);
	  auto bitOffset = IndexOperations::bitOffset<Block>(bitIndex);
	  Block mask = ~(Block(1) << bitOffset);
	  blocks[blockIndex] &= mask;
	}
  }
 private:
  bool isPowerOf2(Block n) {
	return (n & (n - 1)) == 0;
  }
  void pushBackNewBlock(block_type value) {
	blocks.push_back(value);
  }
  std::vector<Block> blocks;
  Block bufferBlock;
  int bufferBlockSize;
};

