#include "./command_line.test.hpp"
#include "string_arg.hpp"

TEST_CASE("Flags get updated after parsing", "[CommandLine]") {
  CommandLine commandLine;
  Flag a("-a", "--flag-a", false);
  commandLine.add(a);
  REQUIRE(bool(a) == false);
  
  SECTION("Flag gets updated after parsing the short form") {
	int argc = 2;
	const char* argv[] = {"executable", "-a"};
    commandLine.parse(argc, const_cast<char**>(argv));
  	REQUIRE(bool(a) == true);
  }

  SECTION("Flag gets updated after parsing the long form") {
	int argc = 2;
	const char* argv[] ={"executable", "--flag-a"};
    commandLine.parse(argc, const_cast<char**>(argv));
    REQUIRE(bool(a) == true);
  }
  SECTION("Flag does not get updated with irrevalent argument") {
	int argc = 4;
	const char* argv[] = {"executableName", "-b", "--not-flag-a", "notThisOneEither"};
    commandLine.parse(argc, const_cast<char**>(argv));
    REQUIRE(bool(a) == false);
  }
}

TEST_CASE("xorAdd works as intended", "[CommandLine]") {
  CommandLine commandLine;
  Flag a("-a", "--flag-a", false);
  Flag b("-b", "--flag-b", true);

  commandLine.xorAdd(a, b);

  SECTION("Having neither flag have no effect") {
	int argc = 2;
	const char* argv[] = {"executable", "-c", "--neither-a-nor-b"};
    commandLine.parse(argc, const_cast<char**>(argv));
	REQUIRE(bool(a) == false);
	REQUIRE(bool(b) == true);
	REQUIRE(a.isDoneProcessing() == false);
	REQUIRE(b.isDoneProcessing() == false);
  }

  SECTION("Having one flag sets the concerned flag and unsets the other") {
	int argc = 2;
	const char* argv[] = {"executable", "-a"};
    commandLine.parse(argc, const_cast<char**>(argv));
	REQUIRE(bool(a) == true);
	REQUIRE(bool(b) == false);
	REQUIRE(a.isDoneProcessing() == true);
	REQUIRE(b.isDoneProcessing() == true);
	
  }

  SECTION("Having both flags raises an error") {
    int argc = 3;
    const char* argv[] = {"executable", "-a", "--flag-b"};
    REQUIRE_THROWS_AS(commandLine.parse(argc, const_cast<char**>(argv)),
                      std::runtime_error);
  }
}

TEST_CASE("StringArgs", "[CommandLine]") {
  CommandLine commandLine;

  StringArg s("-s", "--string", "");
  commandLine.add(s);

  int argc = 3;
  const char* argv[] = {"executable", "-s", "some string"};
  commandLine.parse(argc, const_cast<char**>(argv));

  REQUIRE(s.getVal() == "some string");
}
