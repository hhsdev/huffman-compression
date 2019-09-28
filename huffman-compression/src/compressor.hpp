#pragma once
#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <string>
#include <climits>
class Compressor {
public:
	static constexpr int NUM_ALL_CHARS = CHAR_MAX + 1;
	using ArrayBigEnoughForAllChars
		= std::array<int, NUM_ALL_CHARS>;

	Compressor();
	void countFrequencies(const std::string& input);
	int getFrequency(char c);
private:
	ArrayBigEnoughForAllChars characterFrequencies;

};

#endif //!H_COMPRESSOR_COMPRESSOR_H_

