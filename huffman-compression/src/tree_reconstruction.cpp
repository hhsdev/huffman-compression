#include "./tree_reconstruction.hpp"

namespace TreeReconstruction {

HuffmanTree reconstructFrom(const CodeLengths& codeLengths) {
  auto charsAndLengths = pairCharsWithLengths(codeLengths);

  std::sort(charsAndLengths.begin(), charsAndLengths.end());
  auto codesAndChars = buildCodes(charsAndLengths);

  return buildTree(codesAndChars);
}

CodeLengthAndCharPairs pairCharsWithLengths(const CodeLengths& codeLengths) {
  CodeLengthAndCharPairs ret;

  for (int i = 0; i < codeLengths.size(); ++i) {
    if (codeLengths[i] > 0) {
      ret.emplace_back(codeLengths[i], i);
    }
  }

  return ret;
}

CodeAndCharPairs buildCodes(const CodeLengthAndCharPairs& pairs) {
  CodeAndCharPairs ret;

  int longestCodeLength = findLongestCodeLength(pairs);
  auto genesisBitset = getLargeEnoughBitset(longestCodeLength);

  std::unique_ptr<BaseBitset> currentCode(genesisBitset->clone());

  bool first = true;
  for (const auto& [length, ch] : pairs) {
    if (first) {
      // TODO: Make this a member of BaseBitset
      pushBackNZeroes(*currentCode, length);
      first = false;
    } else {
      currentCode = generateNextCode(*currentCode, length);
    }
    ret.emplace_back(currentCode->clone(), ch);
  }
  return ret;
}

void pushBackNZeroes(BaseBitset& code, int n) {
  for (int i = 0; i < n; ++i) code.push_back(0);
}

int findLongestCodeLength(const CodeLengthAndCharPairs& pairs) {
  using pair_t = CodeLengthAndCharPairs::value_type;
  return std::max_element(pairs.begin(), pairs.end())->first;
}

std::unique_ptr<BaseBitset> generateNextCode(const BaseBitset& code,
                                             int nextCodeLength) {
  std::unique_ptr<BaseBitset> ret(code.clone());
  ++(*ret);
  pushBackNZeroes(*ret, (nextCodeLength - ret->size()));
  return ret;
}

HuffmanTree buildTree(CodeAndCharPairs& pairs) {
  HuffmanNode* root = new HuffmanNode();

  for (const auto& [code_ptr, ch] : pairs) {
    buildBranch(root, *code_ptr, ch);
  }

  return HuffmanTree(root);
}

void buildBranch(HuffmanNode* root, const BaseBitset& code, unsigned char ch) {
  auto curr = root;
  for (int i = code.size() - 1; i >= 0; --i) {
    if (code[i] == 0) {
      if (!curr->getLeft()) curr->setLeft(new HuffmanNode());
      curr = curr->getLeft();
    } else {
      if (!curr->getRight()) curr->setRight(new HuffmanNode());
      curr = curr->getRight();
    }
  }
  curr->setChar(ch);
}

}  // namespace TreeReconstruction

