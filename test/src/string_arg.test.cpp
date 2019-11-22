#include "./string_arg.test.hpp"

TEST_CASE("process() works as intended", "[StringArg]") {
  StringArg arg("-s", "--string", "");
  REQUIRE(arg.getValue() == "");
  
  int argc = 3;
  const char* argv[] = { "program", "-s", "some string" };
  arg.process(1, argc, const_cast<char**>(argv));

  REQUIRE(arg.getValue() == "some string");
}

TEST_CASE("xorProcess() works as intended", "[StringArg]") {
  const std::string someDefaultString = "great-input-file";
  StringArg arg("-s", "--string", someDefaultString);

  REQUIRE(arg.getValue() == someDefaultString);
  REQUIRE(arg.isResolved() == false); 

  arg.xorProcess();

  REQUIRE(arg.getValue() == "");
  REQUIRE(arg.isResolved() == true); 
}
