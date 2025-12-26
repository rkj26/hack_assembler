cmake_minimum_required(VERSION 3.10)

# 1. Project Metadata
project(HackAssembler VERSION 1.0 LANGUAGES CXX)

# 2. Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Include Directories
# This allows you to use #include "Parser.h" instead of "../include/Parser.h"
include_directories(include)

# 4. Collect Source Files
file(GLOB SOURCES "src/*.cpp")

# 5. Create the Executable
add_executable(HackAssembler ${SOURCES})