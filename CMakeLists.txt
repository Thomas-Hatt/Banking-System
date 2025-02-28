cmake_minimum_required(VERSION 3.5)
project(Banking-System)

set(CMAKE_CXX_STANDARD 11)

# Include subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Specify include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add executable
add_executable(BankingSystem src/Main.cpp)

# Link libraries if needed
