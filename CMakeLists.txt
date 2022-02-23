cmake_minimum_required (VERSION 3.10)
project(ProtobufCarrigeReturn)

find_package(protobuf CONFIG REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS dummy.proto)

include_directories(${CMAKE_BINARY_DIR}) # the protobuf .h file is there

add_executable(test 
    test.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(test PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
