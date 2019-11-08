add_executable(test_all ${CMAKE_CURRENT_SOURCE_DIR}/src/main.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_node.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/huffman_node.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/compressor.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/compressor.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_tree.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/huffman_tree.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/bit_util.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/bit_util.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/bitset_32.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/bitset_32.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/dynamic_bitset.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/dynamic_bitset.test.cpp

					${CMAKE_SOURCE_DIR}/huffman-compression/src/bit_buffer.cpp
					${CMAKE_CURRENT_SOURCE_DIR}/src/bit_buffer.test.cpp)

add_executable(code_word_array_builder ${CMAKE_CURRENT_SOURCE_DIR}/src/main.test.cpp
									    ${CMAKE_CURRENT_SOURCE_DIR}/src/compression_codes_builder.test.cpp)

set_target_properties(test_all code_word_array_builder
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	CXX_STANDARD 17)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(test_all
	PUBLIC
	${PARENT_DIR}/include
	${PARENT_DIR}/huffman-compression/src)

target_include_directories(code_word_array_builder
	PUBLIC
	${PARENT_DIR}/include
	${PARENT_DIR}/huffman-compression/src)

target_compile_options(test_all PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-g -fsanitize=leak>)
