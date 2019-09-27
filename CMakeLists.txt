cmake_minimum_required(VERSION 3.1...3.12)

project(hcomp
	VERSION 0.0
	DESCRIPTION "Compresses files using Huffman algorithm"
	LANGUAGES CXX)

find_file(CATCH
	catch.hpp
	PATHS "${PROJECT_SOURCE_DIR}/include"
	PATH_SUFFIXES "catch"
	DOC "catch.hpp location")

if (CATCH STREQUAL "CATCH-NOTFOUND")
# download catch.hpp from github
	execute_process(COMMAND "wget"
		"-P"
		"${PROJECT_SOURCE_DIR}/include"
		"https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp"
		RESULT_VARIABLE CATCH_DOWNLOAD_RESULT)

	if (NOT (CATCH_DOWNLOAD_RESULT EQUAL 0))
		message(SEND_ERROR "Failed to download catch.hpp. "
			"Please manually download catch.hpp from "
			"https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp"
			"and put it into ${PROJECT_SOURCE_DIR}/include")
	endif()
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/huffman-compression)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
