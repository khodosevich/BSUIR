# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/khodosevich/BSUIR/C++/function

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/khodosevich/BSUIR/C++/function/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/function.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/function.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/function.dir/flags.make

CMakeFiles/function.dir/main.cpp.o: CMakeFiles/function.dir/flags.make
CMakeFiles/function.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/khodosevich/BSUIR/C++/function/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/function.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/function.dir/main.cpp.o -c /Users/khodosevich/BSUIR/C++/function/main.cpp

CMakeFiles/function.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/function.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/khodosevich/BSUIR/C++/function/main.cpp > CMakeFiles/function.dir/main.cpp.i

CMakeFiles/function.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/function.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/khodosevich/BSUIR/C++/function/main.cpp -o CMakeFiles/function.dir/main.cpp.s

# Object files for target function
function_OBJECTS = \
"CMakeFiles/function.dir/main.cpp.o"

# External object files for target function
function_EXTERNAL_OBJECTS =

function: CMakeFiles/function.dir/main.cpp.o
function: CMakeFiles/function.dir/build.make
function: CMakeFiles/function.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/khodosevich/BSUIR/C++/function/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable function"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/function.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/function.dir/build: function
.PHONY : CMakeFiles/function.dir/build

CMakeFiles/function.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/function.dir/cmake_clean.cmake
.PHONY : CMakeFiles/function.dir/clean

CMakeFiles/function.dir/depend:
	cd /Users/khodosevich/BSUIR/C++/function/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/khodosevich/BSUIR/C++/function /Users/khodosevich/BSUIR/C++/function /Users/khodosevich/BSUIR/C++/function/cmake-build-debug /Users/khodosevich/BSUIR/C++/function/cmake-build-debug /Users/khodosevich/BSUIR/C++/function/cmake-build-debug/CMakeFiles/function.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/function.dir/depend
