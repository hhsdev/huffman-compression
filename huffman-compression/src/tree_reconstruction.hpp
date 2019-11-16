#pragma once
#include <exception>
#include <utility>
#include <vector>

#include "./all_bitsets.hpp"
#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"
#include "./util.hpp"

namespace TreeReconstruction {
using CodeLengths = Huffman::CharSizedArray<unsigned char>;

using CodeLengthAndCharPair = std::pair<int, unsigned char>;
using CodeLengthAndCharPairs = std::vector<CodeLengthAndCharPair>;

using CodeAndCharPair = std::pair<std::unique_ptr<BaseBitset>, unsigned char>;
using CodeAndCharPairs = std::vector<CodeAndCharPair>;

HuffmanTree reconstructFrom(const CodeLengths&);

CodeLengthAndCharPairs pairCharsWithLengths(const CodeLengths&);
CodeAndCharPairs buildCodes(const CodeLengthAndCharPairs& pairs);
HuffmanTree buildTree(
    const Huffman::CharSizedArray<std::unique_ptr<BaseBitset>>& codeTable);
HuffmanTree buildTree(CodeAndCharPairs& pairs);

void pushBackNZeroes(BaseBitset& code, int n);

int findLongestCodeLength(const CodeLengthAndCharPairs& pairs);

std::unique_ptr<BaseBitset> generateNextCode(const BaseBitset&, int);

void buildBranch(HuffmanNode* root, const BaseBitset& code, unsigned char ch);


}  // namespace TreeReconstruction
