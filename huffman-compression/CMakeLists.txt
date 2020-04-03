add_executable(hc
	${CMAKE_SOURCE_DIR}/huffman-compression/src/hc.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/reader.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/writer.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/compressor.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/decompressor.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_node.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/huffman_tree.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/tree_reconstruction.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/all_bitsets.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/string_view_bitset.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/flag.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/string_arg.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/command_line.cpp
	${CMAKE_SOURCE_DIR}/huffman-compression/src/config.cpp

	${CMAKE_SOURCE_DIR}/huffman-compression/src/bit_util.cpp
)

set_target_properties(hc
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	CXX_STANDARD 17)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(hc
	PUBLIC
	${PARENT_DIR}/include
	${PARENT_DIR}/huffman-compression/src)
