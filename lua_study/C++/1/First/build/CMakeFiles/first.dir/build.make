# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aspotashev/Github/photobooth/lua_study/C++/1/First

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build

# Include any dependencies generated for this target.
include CMakeFiles/first.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/first.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/first.dir/flags.make

CMakeFiles/first.dir/main.o: CMakeFiles/first.dir/flags.make
CMakeFiles/first.dir/main.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/first.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/first.dir/main.o -c /home/aspotashev/Github/photobooth/lua_study/C++/1/First/main.cpp

CMakeFiles/first.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/first.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/lua_study/C++/1/First/main.cpp > CMakeFiles/first.dir/main.i

CMakeFiles/first.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/first.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/lua_study/C++/1/First/main.cpp -o CMakeFiles/first.dir/main.s

CMakeFiles/first.dir/main.o.requires:
.PHONY : CMakeFiles/first.dir/main.o.requires

CMakeFiles/first.dir/main.o.provides: CMakeFiles/first.dir/main.o.requires
	$(MAKE) -f CMakeFiles/first.dir/build.make CMakeFiles/first.dir/main.o.provides.build
.PHONY : CMakeFiles/first.dir/main.o.provides

CMakeFiles/first.dir/main.o.provides.build: CMakeFiles/first.dir/main.o

# Object files for target first
first_OBJECTS = \
"CMakeFiles/first.dir/main.o"

# External object files for target first
first_EXTERNAL_OBJECTS =

first: CMakeFiles/first.dir/main.o
first: CMakeFiles/first.dir/build.make
first: CMakeFiles/first.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable first"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/first.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/first.dir/build: first
.PHONY : CMakeFiles/first.dir/build

CMakeFiles/first.dir/requires: CMakeFiles/first.dir/main.o.requires
.PHONY : CMakeFiles/first.dir/requires

CMakeFiles/first.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/first.dir/cmake_clean.cmake
.PHONY : CMakeFiles/first.dir/clean

CMakeFiles/first.dir/depend:
	cd /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aspotashev/Github/photobooth/lua_study/C++/1/First /home/aspotashev/Github/photobooth/lua_study/C++/1/First /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build /home/aspotashev/Github/photobooth/lua_study/C++/1/First/build/CMakeFiles/first.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/first.dir/depend
