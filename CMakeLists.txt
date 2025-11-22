# Minimum CMake version required
cmake_minimum_required(VERSION 3.25)

# Project name
project(EndlessRunner)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Try to find raylib installed on the system first
find_package(raylib QUIET)

# If not found, fetch it from GitHub
if(NOT raylib_FOUND)
  message(STATUS "raylib not found locally, fetching from GitHub...")
  include(FetchContent)
  
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master
  )
  
  FetchContent_MakeAvailable(raylib)
else()
  message(STATUS "Using locally installed raylib")
endif()


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
        src/cpp/Platform.cpp
        src/cpp/Star.cpp
        src/cpp/Snow.cpp
        src/cpp/StarPopout.cpp
        src/cpp/ReplayScreen.cpp
        src/cpp/ReplaySystem.cpp
        src/cpp/ReplayGameScreen.cpp
)

# Link the raylib library
target_link_libraries(MyExecutable PRIVATE raylib)