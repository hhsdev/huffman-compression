add_executable(test_all ${CMAKE_CURRENT_SOURCE_DIR}/src/main.test.cpp
					${CMAKE_SOURCE_DIR}/huffman-compression/src/all_bitsets.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_node.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/huffman_node.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/compressor.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/compressor.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/config.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/config.test.cpp
					
					${CMAKE_SOURCE_DIR}/huffman-compression/src/command_line.cpp
					${CMAKE_SOURCE_DIR}/huffman-compression/src/flag.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/command_line.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/string_arg.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/string_arg.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/decompressor.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/decompressor.test.cpp

					${CMAKE_CURRENT_SOURCE_DIR}/src/compression_codes_builder.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_tree.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/huffman_tree.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/bit_util.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/bit_util.test.cpp

					${CMAKE_CURRENT_SOURCE_DIR}/src/bitset_common.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/reader.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/reader.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/string_view_bitset.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/string_view_bitset.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/tree_reconstruction.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/tree_reconstruction.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/writer.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/writer.test.cpp

					${CMAKE_CURRENT_SOURCE_DIR}/src/dynamic_bitset.test.cpp)

set_target_properties(test_all
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	CXX_STANDARD 17)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(test_all
	PUBLIC
	${PARENT_DIR}/include
	${PARENT_DIR}/huffman-compression/src)

target_compile_options(test_all PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-g -fsanitize=leak>)
