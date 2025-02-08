# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(EndlessRunner)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and include raylib
find_package(raylib REQUIRED)

# Add the executable target
add_executable(MyExecutable
        src/main.cpp
        src/cpp/New_operator.cpp
)


# Link the raylib and EA::StdC libraries
target_link_libraries(MyExecutable PRIVATE raylib )