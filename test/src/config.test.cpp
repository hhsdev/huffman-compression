#include "./config.test.hpp"

TEST_CASE("output file is correctly parsed", "[Config]") {
  const std::string outputFile = "some output file";

  int argc = 3;
  const char *argv[] = { "program", "-o", outputFile.c_str() };
  Config c; 
  c.update(argc, const_cast<char**>(argv));
  REQUIRE(c.getOutputFile() == outputFile);
}

TEST_CASE("input file is correcly parsed", "[Config]") {
  const std::string inputFile = "some input file";
  int argc = 3;
  const char *argv[] = { "program", "-i", inputFile.c_str() };
  
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getInputFile() == inputFile);
}

TEST_CASE("setting compress flag works", "[Config]") {
  int argc = 4;
  const char* argv[] = { "program", "-c", "-i", "some input file" };
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::COMPRESS);
}


TEST_CASE("setting decompress flag works", "[Config]") {
  int argc = 4;
  const char* argv[] = { "program", "-d", "-i", "some input file" };
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::DECOMPRESS);
}

TEST_CASE("not setting any mode flags defaults to compress mode", "[Config]") {
  int argc = 3;
  const char* argv[] = { "program", "-i", "some input file" };
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getMode() == Config::COMPRESS);
}

TEST_CASE("absence of output file is interpreted as <input file>.out",
          "[Config]") {
  const std::string inputFile = "some_input_file";
  int argc = 3;
  const char* argv[] = { "program", "-i", inputFile.c_str() };
  Config c; 
  c.update(argc, const_cast<char**>(argv));

  REQUIRE(c.getOutputFile() == inputFile + ".out");

}
