#include "./tree_reconstruction.test.hpp"

void assertInputProducesCorrectBranches(const LengthInfo& input,
                                        const BranchInfo& branches) {
  TreeReconstruction::CodeLengths codeLengths = setUpCodeLengths(input);

  auto tree = TreeReconstruction::reconstructFrom(codeLengths);

  verifyTreeHasCorrectBranches(tree, branches);
}

TEST_CASE("Creates the correct HuffmanTree", "[TreeReconstruction]") {
  // 'l' means left branch; 'r' means right
  assertInputProducesCorrectBranches(
      {{'a', 2}, {'b', 1}, {'c', 3}, {'d', 3}},
      {{'a', "rl"}, {'b', "l"}, {'c', "rrl"}, {'d', "rrr"}});

  assertInputProducesCorrectBranches(
      {{'a', 1}, {'b', 3}, {'c', 3}, {'d', 3}, {'e', 3}},
      {{'a', "l"}, {'b', "rll"}, {'c', "rlr"}, {'d', "rrl"}, {'e', "rrr"}});
}
