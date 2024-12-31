cmake_minimum_required(VERSION 3.5)

project(EndlessRunner)

# Set the C++ standard (optional but recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib (if installed system-wide or via CMake's find_package)
find_package(raylib REQUIRED)

# Include the EASTL headers
# Adjust this path if EASTL is installed in a different directory
include_directories(/usr/local/include)

# Add the executable for your project
add_executable(MyRaylibProject src/main.cpp)

# Link raylib to your executable
target_link_libraries(MyRaylibProject PRIVATE raylib)
# Add tasks subprojects