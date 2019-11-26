#include "./config.hpp"

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

  if (!inputArg.getValue().empty()) {
    input_file = inputArg.getValue();
  }
  if (!outputArg.getValue().empty()) {
    output_file = outputArg.getValue();
  } else {
    output_file = input_file + ".out";
  }
  if (decompressFlag)
    setMode(DECOMPRESS);
  else
    setMode(COMPRESS);
}
