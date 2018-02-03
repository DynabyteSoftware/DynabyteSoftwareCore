cmake_minimum_required (VERSION 3.8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
project (DynabyteSoftware)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core)
add_subdirectory(Testing)
