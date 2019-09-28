add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.test.cpp
					${CMAKE_SOURCE_DIR}/huffman-compression/src/compressor.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/compressor.test.cpp
					${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_node.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/huffman_node.test.cpp)

set_target_properties(main
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	CXX_STANDARD 14)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(main
	PUBLIC
	${PARENT_DIR}/include
	${PARENT_DIR}/huffman-compression/src)

target_compile_options(main PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall>
	$<$<CXX_COMPILER_ID:MSVC>:
		/W4>)
