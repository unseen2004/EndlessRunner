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
        src/cpp/main.cpp
        src/cpp/Game.cpp
        src/cpp/StateMachine.cpp
        src/cpp/WelcomeScreen.cpp
        src/cpp/GameScreen.cpp
        src/cpp/DeadScreen.cpp
        src/cpp/Background.cpp
        src/cpp/Character.cpp
        src/cpp/Cloud.cpp
        src/cpp/Interface.cpp
        src/cpp/Obstacle.cpp
        src/cpp/Platform.cpp
        src/cpp/Table.cpp
)

# Link the raylib library
target_link_libraries(MyExecutable PRIVATE raylib)