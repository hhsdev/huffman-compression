#include "./config.test.hpp"

TEST_CASE("input/output files arecorrectly parsed", "[Config]") {
  const std::string outputFile = "some output file";
  const std::string inputFile = "some input file";

  const char *argv[] = { "program", "-i", inputFile.c_str(), "-o", outputFile.c_str() };
  const int argc = sizeof(argv) / sizeof(const char *);

  Config c; 
  c.update(argc, const_cast<char**>(argv));
  REQUIRE(c.getOutputFile() == outputFile);
  REQUIRE(c.getInputFile() == inputFile);
}

TEST_CASE("setting compress flag works", "[Config]") {
  const char* argv[] = { "program", "-c", "-i", "some input file" };
  const int argc = sizeof(argv) / sizeof(const char *);
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::COMPRESS);
}


TEST_CASE("setting decompress flag works", "[Config]") {
  const char* argv[] = { "program", "-d", "-i", "some input file" };
  const int argc = sizeof(argv) / sizeof(const char *);
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::DECOMPRESS);
}

TEST_CASE("not setting any mode flags defaults to compress mode", "[Config]") {
  const char* argv[] = { "program", "-i", "some input file" };
  const int argc = sizeof(argv) / sizeof(const char *);
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::COMPRESS);
}

TEST_CASE("absence of output file is interpreted as <input file>.out",
          "[Config]") {
  const std::string inputFile = "some_input_file";
  const char* argv[] = { "program", "-i", inputFile.c_str() };
  const int argc = sizeof(argv) / sizeof(const char *);
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getOutputFile() == inputFile + ".out");

}
