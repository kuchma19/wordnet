cmake_minimum_required(VERSION 3.13)

include(tests/Strict.cmake)

set(PROJECT_NAME wordnet)
project(${PROJECT_NAME})

# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inlcude directories
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

# Source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Compile source files into a library
add_library(wordnet_lib ${SRC_FILES})
target_compile_options(wordnet_lib PUBLIC ${COMPILE_OPTS})
target_link_options(wordnet_lib PUBLIC ${LINK_OPTS})

# Main is separate
add_executable(wordnet ${PROJECT_SOURCE_DIR}/src/main.cpp src/WordNet.cpp src/Digraph.cpp src/Outcast.cpp src/ShortestCommonAncestor.cpp)
target_compile_options(wordnet PRIVATE ${COMPILE_OPTS})
target_link_options(wordnet PRIVATE ${LINK_OPTS})

# linking Main against the library
target_link_libraries(wordnet wordnet_lib)

# google test is a git submodule
add_subdirectory(googletest)

enable_testing()

# test is a git submodule
add_subdirectory(tests)
