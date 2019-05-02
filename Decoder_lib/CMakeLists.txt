cmake_minimum_required(VERSION 2.8) 

project(Decoder_lib)				

set(SOURCE_LIB Decoder.cpp)	
set(HEADER_LIB Decoder.h)

set(DECODER_LIB_DIR Decoder_lib)

add_library(Decoder_lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")