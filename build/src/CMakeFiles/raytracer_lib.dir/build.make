# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/panagiotispetridis/Projects/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/panagiotispetridis/Projects/raytracer/build

# Include any dependencies generated for this target.
include src/CMakeFiles/raytracer_lib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/raytracer_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/raytracer_lib.dir/flags.make

src/CMakeFiles/raytracer_lib.dir/main.cpp.o: src/CMakeFiles/raytracer_lib.dir/flags.make
src/CMakeFiles/raytracer_lib.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/panagiotispetridis/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/raytracer_lib.dir/main.cpp.o"
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracer_lib.dir/main.cpp.o -c /Users/panagiotispetridis/Projects/raytracer/src/main.cpp

src/CMakeFiles/raytracer_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracer_lib.dir/main.cpp.i"
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/panagiotispetridis/Projects/raytracer/src/main.cpp > CMakeFiles/raytracer_lib.dir/main.cpp.i

src/CMakeFiles/raytracer_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracer_lib.dir/main.cpp.s"
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/panagiotispetridis/Projects/raytracer/src/main.cpp -o CMakeFiles/raytracer_lib.dir/main.cpp.s

# Object files for target raytracer_lib
raytracer_lib_OBJECTS = \
"CMakeFiles/raytracer_lib.dir/main.cpp.o"

# External object files for target raytracer_lib
raytracer_lib_EXTERNAL_OBJECTS =

src/libraytracer_lib.a: src/CMakeFiles/raytracer_lib.dir/main.cpp.o
src/libraytracer_lib.a: src/CMakeFiles/raytracer_lib.dir/build.make
src/libraytracer_lib.a: src/CMakeFiles/raytracer_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/panagiotispetridis/Projects/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libraytracer_lib.a"
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/raytracer_lib.dir/cmake_clean_target.cmake
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracer_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/raytracer_lib.dir/build: src/libraytracer_lib.a

.PHONY : src/CMakeFiles/raytracer_lib.dir/build

src/CMakeFiles/raytracer_lib.dir/clean:
	cd /Users/panagiotispetridis/Projects/raytracer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/raytracer_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/raytracer_lib.dir/clean

src/CMakeFiles/raytracer_lib.dir/depend:
	cd /Users/panagiotispetridis/Projects/raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/panagiotispetridis/Projects/raytracer /Users/panagiotispetridis/Projects/raytracer/src /Users/panagiotispetridis/Projects/raytracer/build /Users/panagiotispetridis/Projects/raytracer/build/src /Users/panagiotispetridis/Projects/raytracer/build/src/CMakeFiles/raytracer_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/raytracer_lib.dir/depend

