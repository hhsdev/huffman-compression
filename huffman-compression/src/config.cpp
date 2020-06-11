#include "./config.hpp"
#include <iostream>

void Config::update(int argc, char** argv) {
  StringArg outputArg("-o", "--output", "");
  StringArg inputArg("-i", "--input", "");
  Flag compressFlag("-c", "--compress", false);
  Flag decompressFlag("-d", "--decompress", false);

  CommandLine cmd;
  cmd.add(outputArg);
  cmd.add(inputArg);
  cmd.xorAdd(compressFlag, decompressFlag);
  cmd.parse(argc, argv);
  
  if (inputArg.getValue().empty()) {
    throw ConfigException("No input file given");
  }

  if (!inputArg.getValue().empty()) {
    input_file = inputArg.getValue();
  }

  if (!outputArg.getValue().empty()) {
    output_file = outputArg.getValue();
  } else {
    output_file = input_file + ".out";
  }
  
  setMode(decompressFlag ? DECOMPRESS : COMPRESS);
}

void Config::printHelp() const {
  std::cout << "hc: compress/decompress files using huffman compression\n"
    << "Usage: hc -c|-d <-i|--input> file <-o|--output> file\n";
}
