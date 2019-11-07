#include "catch.hpp"
#include "./compression_codes_builder.hpp"

class MockNode {
public:
  MockNode(int frequency, char value) : frequency(frequency), value(value) {}

  bool hasChar() const { return value >= 0; }
  int getFrequency() const { return frequency; }
  int getChar() const { return value; }
  
  void setFrequency(int frequency) { this->frequency = frequency; }
  void setValue(int value) { this->value = value; }

  MockNode* getLeft() { return left; }
  MockNode* getRight() { return right; }

  const MockNode* getLeft() const { return left; }
  const MockNode* getRight() const { return right; }

  void setLeft(MockNode* node) { left = node; }
  void setRight(MockNode* node) { right = node; }
  
private:
  int frequency; char value;
  MockNode* left;
  MockNode* right;
};

class MockTree {
public:
  using node_t = MockNode;
  MockTree(MockNode* root) : root(root) {}
  MockNode* getRoot() {
	return root;
  }
  const MockNode* getRoot() const {
	return root;
  }
private:
  MockNode* root;
};

TEST_CASE("CompressionCodesBuilder", "[CompressionCodesBuilder]") {
  // set up the tree in this way
  /*
   *          (root)
   *          /    \
   *        (a+b)  (c)
   *        /   \
   *      (a)   (b)
   */
  MockNode a(1, 'a'), b(2, 'b'), c(3, 'c');
  MockNode aPlusB(a.getFrequency() + b.getFrequency(), -1);
  MockNode root(aPlusB.getFrequency() + c.getFrequency(), -1);
  aPlusB.setLeft(&a);
  aPlusB.setRight(&b);
  root.setLeft(&aPlusB);
  root.setRight(&c);
  MockTree tree(&root);
  // test for mock objects
  REQUIRE(a.getChar() == 'a');
  REQUIRE(b.getChar() == 'b');
  REQUIRE(c.getChar() == 'c');

  REQUIRE(tree.getRoot() == &root);
  REQUIRE(tree.getRoot()->getLeft() == &aPlusB);
  REQUIRE(tree.getRoot()->getRight() == &c);
  REQUIRE(tree.getRoot()->getLeft()->getLeft() == &a);
  REQUIRE(tree.getRoot()->getLeft()->getRight() == &b);

  CompressionCodesBuilder<MockTree> builder;
  
  const auto& codeWordArray = builder.buildFrom(tree);
  REQUIRE(codeWordArray['a']->size() == 2);
  REQUIRE(codeWordArray['b']->size() == 2);
  REQUIRE(codeWordArray['c']->size() == 1);
}
