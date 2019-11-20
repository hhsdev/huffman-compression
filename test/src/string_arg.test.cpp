#include "./string_arg.test.hpp"

TEST_CASE("process works as intended", "[StringArg]") {
  StringArg arg("-s", "--string", "");
  REQUIRE(arg.getVal() == "");
  
  int argc = 3;
  const char* argv[] = { "program", "-s", "some string" };
  arg.process(1, argc, const_cast<char**>(argv));

  REQUIRE(arg.getVal() == "some string");
}
