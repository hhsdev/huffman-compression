cmake_minimum_required(VERSION 3.1...3.12)

project(hcomp
	VERSION 0.0
	DESCRIPTION "Compresses files using Huffman algorithm"
	LANGUAGES CXX)


set(INCLUDE_DIR 
	"${PROJECT_SOURCE_DIR}/include"
	CACHE
	FILEPATH "Include directory for external libraries"
	FORCE)

find_file(CATCH
	catch.hpp
	PATHS "${PROJECT_SOURCE_DIR}/include"
	PATH_SUFFIXES "catch"
	DOC "catch.hpp location")

if (CATCH-NOTFOUND)
# download catch.hpp from github
	set(CATCH_URL 
		"https://raw.githubusercontent.com/catchorg/Catch2/master/include/catch.hpp"
		CACHE
		"Url for catch.hpp")
	execute_process(COMMAND "wget"
		"https://raw.githubusercontent.com/catchorg/Catch2/master/include/catch.hpp"
		"${INCLUDE_DIR}"
		RESULT_VARIABLE CATCH_DOWNLOAD_RESULT)

	if (CATCH_DOWNLOAD_RESULT NOT_EQUAL 0)
		message(SEND_ERROR "Failed to download catch.hpp. "
			"Please manually download catch.hpp from ${CATCH_URL} "
			"and put it into ${INCLUDE_DIR}")
	endif()
endif()


