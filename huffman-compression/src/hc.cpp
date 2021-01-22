#include "./config.hpp"
#include "./reader.hpp"
#include "./writer.hpp"

#include <fstream>

int main(int argc, char** argv) {
  Config config;
  config.update(argc, argv);

  std::ifstream input(config.getInputFile());
  std::ofstream output(config.getOutputFile());

  if (config.getMode() == Config::COMPRESS) {
    Writer compressor;
    compressor.compress(input);
    compressor.write(output);
  } else {
    Reader decompressor;
    output << decompressor.decompress(input);
  }
}
