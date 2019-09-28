#include "./compressor.hpp"

Compressor::Compressor() : characterFrequencies() {}


void Compressor::countFrequencies(const std::string& input) {
	for (char c : input) {
		characterFrequencies[c] += 1;
	}
}

int Compressor::getFrequency(char c) {
	return characterFrequencies[c];
}
