# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /cygdrive/c/Users/Kian/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Kian/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Kian/CLionProjects/trivialtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/trivialtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/trivialtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trivialtest.dir/flags.make

CMakeFiles/trivialtest.dir/main.cpp.o: CMakeFiles/trivialtest.dir/flags.make
CMakeFiles/trivialtest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trivialtest.dir/main.cpp.o"
	/cygdrive/c/cygwin64/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trivialtest.dir/main.cpp.o -c /cygdrive/c/Users/Kian/CLionProjects/trivialtest/main.cpp

CMakeFiles/trivialtest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trivialtest.dir/main.cpp.i"
	/cygdrive/c/cygwin64/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Kian/CLionProjects/trivialtest/main.cpp > CMakeFiles/trivialtest.dir/main.cpp.i

CMakeFiles/trivialtest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trivialtest.dir/main.cpp.s"
	/cygdrive/c/cygwin64/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Kian/CLionProjects/trivialtest/main.cpp -o CMakeFiles/trivialtest.dir/main.cpp.s

# Object files for target trivialtest
trivialtest_OBJECTS = \
"CMakeFiles/trivialtest.dir/main.cpp.o"

# External object files for target trivialtest
trivialtest_EXTERNAL_OBJECTS =

trivialtest.exe: CMakeFiles/trivialtest.dir/main.cpp.o
trivialtest.exe: CMakeFiles/trivialtest.dir/build.make
trivialtest.exe: CMakeFiles/trivialtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable trivialtest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trivialtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trivialtest.dir/build: trivialtest.exe

.PHONY : CMakeFiles/trivialtest.dir/build

CMakeFiles/trivialtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trivialtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trivialtest.dir/clean

CMakeFiles/trivialtest.dir/depend:
	cd /cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Kian/CLionProjects/trivialtest /cygdrive/c/Users/Kian/CLionProjects/trivialtest /cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug /cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug /cygdrive/c/Users/Kian/CLionProjects/trivialtest/cmake-build-debug/CMakeFiles/trivialtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/trivialtest.dir/depend
