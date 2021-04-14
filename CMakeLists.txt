cmake_minimum_required(VERSION 3.10)

project(
  hcomp
  VERSION 0.0
  DESCRIPTION "Compresses files using Huffman algorithm"
  LANGUAGES CXX)

find_file(
  CATCH catch.hpp
  PATHS "${PROJECT_SOURCE_DIR}/include"
  PATH_SUFFIXES "catch"
  DOC "catch.hpp location")

if(CATCH STREQUAL "CATCH-NOTFOUND")
  # download catch.hpp from github
  execute_process(
    COMMAND
      "wget" "-P" "${PROJECT_SOURCE_DIR}/include"
      "https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp"
    RESULT_VARIABLE CATCH_DOWNLOAD_RESULT)

  if(NOT (CATCH_DOWNLOAD_RESULT EQUAL 0))
    message(
      SEND_ERROR
        "Failed to download catch.hpp. "
        "Please manually download catch.hpp from "
        "https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp"
        "and put it into ${PROJECT_SOURCE_DIR}/include")
  endif()
endif()

# Running ctags
find_program(CTAGS ctags)

if(CTAGS)
  set_source_files_properties(tags PROPERTIES GENERATED true)
  add_custom_command(
    OUTPUT tags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extras=+q .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  add_custom_target(dummy_target ALL DEPENDS tags)
endif()

# exports a compile_commands.json file which can then be used by linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_IPO "Enables Interprocedural optimization" ON)
if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)
  if(result)
    # set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/huffman-compression)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
