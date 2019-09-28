#pragma once

class HuffmanNode {
public:
	HuffmanNode();
	HuffmanNode(char ch, int count);
	HuffmanNode(const HuffmanNode& left, const HuffmanNode& right);

	short getChar() const;
	int getCount() const;
	const HuffmanNode& getLeft();
	const HuffmanNode& getRight();

	bool operator<(const HuffmanNode& other) const;
	bool operator<=(const HuffmanNode& other) const;
	bool operator>(const HuffmanNode& other) const;
	bool operator>=(const HuffmanNode& other) const;
	bool operator==(const HuffmanNode& other) const;
	bool operator!=(const HuffmanNode& other) const;
private:
	const HuffmanNode* left;
	const HuffmanNode* right;
	int count;
	short ch;
};

