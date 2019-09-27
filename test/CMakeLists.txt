add_executable(dummy ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp)

set_target_properties(dummy
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	CXX_STANDARD 14)


get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(dummy
	PUBLIC
	${PARENT_DIR}/include)

target_compile_options(dummy PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall>
	$<$<CXX_COMPILER_ID:MSVC>:
		/W4>)
