# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maks/Programming/EndlessRunner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maks/Programming/EndlessRunner/build

# Include any dependencies generated for this target.
include CMakeFiles/MyExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyExecutable.dir/flags.make

CMakeFiles/MyExecutable.dir/codegen:
.PHONY : CMakeFiles/MyExecutable.dir/codegen

CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/main.cpp
CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/main.cpp

CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/main.cpp > CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/main.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Game.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Game.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Game.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Game.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/StateMachine.cpp
CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/StateMachine.cpp

CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/StateMachine.cpp > CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/StateMachine.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/WelcomeScreen.cpp
CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/WelcomeScreen.cpp

CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/WelcomeScreen.cpp > CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/WelcomeScreen.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/GameScreen.cpp
CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/GameScreen.cpp

CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/GameScreen.cpp > CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/GameScreen.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/DeadScreen.cpp
CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/DeadScreen.cpp

CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/DeadScreen.cpp > CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/DeadScreen.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Background.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Background.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Background.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Background.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Character.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Character.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Character.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Character.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Cloud.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Cloud.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Cloud.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Cloud.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Interface.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Interface.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Interface.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Interface.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Obstacle.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Obstacle.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Obstacle.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Obstacle.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Platform.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Platform.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Platform.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Platform.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.s

CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o: /home/maks/Programming/EndlessRunner/src/cpp/Table.cpp
CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o -MF CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o -c /home/maks/Programming/EndlessRunner/src/cpp/Table.cpp

CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maks/Programming/EndlessRunner/src/cpp/Table.cpp > CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.i

CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maks/Programming/EndlessRunner/src/cpp/Table.cpp -o CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.s

# Object files for target MyExecutable
MyExecutable_OBJECTS = \
"CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o"

# External object files for target MyExecutable
MyExecutable_EXTERNAL_OBJECTS =

MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/main.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Game.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/StateMachine.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/WelcomeScreen.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/GameScreen.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/DeadScreen.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Background.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Character.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Cloud.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Interface.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Obstacle.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Platform.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/src/cpp/Table.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/build.make
MyExecutable: CMakeFiles/MyExecutable.dir/compiler_depend.ts
MyExecutable: /usr/lib/libraylib.so
MyExecutable: CMakeFiles/MyExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/maks/Programming/EndlessRunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable MyExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyExecutable.dir/build: MyExecutable
.PHONY : CMakeFiles/MyExecutable.dir/build

CMakeFiles/MyExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyExecutable.dir/clean

CMakeFiles/MyExecutable.dir/depend:
	cd /home/maks/Programming/EndlessRunner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maks/Programming/EndlessRunner /home/maks/Programming/EndlessRunner /home/maks/Programming/EndlessRunner/build /home/maks/Programming/EndlessRunner/build /home/maks/Programming/EndlessRunner/build/CMakeFiles/MyExecutable.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyExecutable.dir/depend

