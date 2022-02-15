cmake_minimum_required(VERSION 3.17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)

# Add executable called "TestProjectExecutable" that is built from the source files
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC POGEngine)