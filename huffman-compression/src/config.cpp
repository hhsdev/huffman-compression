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

  if (!outputArg.getValue().empty()) {
    output_file = outputArg.getValue();
  }
  if (!inputArg.getValue().empty()) {
    input_file = inputArg.getValue();
  }
  if (decompressFlag)
    setMode(DECOMPRESS);
  else
    setMode(COMPRESS);
}
