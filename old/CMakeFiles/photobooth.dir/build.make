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
CMAKE_SOURCE_DIR = /home/aspotashev/Github/photobooth/old

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aspotashev/Github/photobooth/old

# Include any dependencies generated for this target.
include CMakeFiles/photobooth.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/photobooth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/photobooth.dir/flags.make

ui_mainwindow.h: mainwindow.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_mainwindow.h"
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic -o /home/aspotashev/Github/photobooth/old/ui_mainwindow.h /home/aspotashev/Github/photobooth/old/mainwindow.ui

ui_parameterslider.h: parameterslider.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_parameterslider.h"
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic -o /home/aspotashev/Github/photobooth/old/ui_parameterslider.h /home/aspotashev/Github/photobooth/old/parameterslider.ui

qrc_photobooth.cpp: icons/document-export.png
qrc_photobooth.cpp: icons/applications-development.png
qrc_photobooth.cpp: icons/system-shutdown.png
qrc_photobooth.cpp: icons/view-refresh.png
qrc_photobooth.cpp: icons/camera-photo.png
qrc_photobooth.cpp: photobooth.qrc.depends
qrc_photobooth.cpp: photobooth.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_photobooth.cpp"
	/usr/lib/x86_64-linux-gnu/qt5/bin/rcc -name photobooth -o /home/aspotashev/Github/photobooth/old/qrc_photobooth.cpp /home/aspotashev/Github/photobooth/old/photobooth.qrc

CMakeFiles/photobooth.dir/parameterslider.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/parameterslider.cpp.o: parameterslider.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/parameterslider.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/parameterslider.cpp.o -c /home/aspotashev/Github/photobooth/old/parameterslider.cpp

CMakeFiles/photobooth.dir/parameterslider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/parameterslider.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/parameterslider.cpp > CMakeFiles/photobooth.dir/parameterslider.cpp.i

CMakeFiles/photobooth.dir/parameterslider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/parameterslider.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/parameterslider.cpp -o CMakeFiles/photobooth.dir/parameterslider.cpp.s

CMakeFiles/photobooth.dir/parameterslider.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/parameterslider.cpp.o.requires

CMakeFiles/photobooth.dir/parameterslider.cpp.o.provides: CMakeFiles/photobooth.dir/parameterslider.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/parameterslider.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/parameterslider.cpp.o.provides

CMakeFiles/photobooth.dir/parameterslider.cpp.o.provides.build: CMakeFiles/photobooth.dir/parameterslider.cpp.o

CMakeFiles/photobooth.dir/mainwindow.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/mainwindow.cpp.o: mainwindow.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/mainwindow.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/mainwindow.cpp.o -c /home/aspotashev/Github/photobooth/old/mainwindow.cpp

CMakeFiles/photobooth.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/mainwindow.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/mainwindow.cpp > CMakeFiles/photobooth.dir/mainwindow.cpp.i

CMakeFiles/photobooth.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/mainwindow.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/mainwindow.cpp -o CMakeFiles/photobooth.dir/mainwindow.cpp.s

CMakeFiles/photobooth.dir/mainwindow.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/mainwindow.cpp.o.requires

CMakeFiles/photobooth.dir/mainwindow.cpp.o.provides: CMakeFiles/photobooth.dir/mainwindow.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/mainwindow.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/mainwindow.cpp.o.provides

CMakeFiles/photobooth.dir/mainwindow.cpp.o.provides.build: CMakeFiles/photobooth.dir/mainwindow.cpp.o

CMakeFiles/photobooth.dir/camera.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/camera.cpp.o: camera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/camera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/camera.cpp.o -c /home/aspotashev/Github/photobooth/old/camera.cpp

CMakeFiles/photobooth.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/camera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/camera.cpp > CMakeFiles/photobooth.dir/camera.cpp.i

CMakeFiles/photobooth.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/camera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/camera.cpp -o CMakeFiles/photobooth.dir/camera.cpp.s

CMakeFiles/photobooth.dir/camera.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/camera.cpp.o.requires

CMakeFiles/photobooth.dir/camera.cpp.o.provides: CMakeFiles/photobooth.dir/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/camera.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/camera.cpp.o.provides

CMakeFiles/photobooth.dir/camera.cpp.o.provides.build: CMakeFiles/photobooth.dir/camera.cpp.o

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o: chdkptpmanager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o -c /home/aspotashev/Github/photobooth/old/chdkptpmanager.cpp

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/chdkptpmanager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/chdkptpmanager.cpp > CMakeFiles/photobooth.dir/chdkptpmanager.cpp.i

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/chdkptpmanager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/chdkptpmanager.cpp -o CMakeFiles/photobooth.dir/chdkptpmanager.cpp.s

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.requires

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.provides: CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.provides

CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.provides.build: CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o

CMakeFiles/photobooth.dir/main.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/main.cpp.o -c /home/aspotashev/Github/photobooth/old/main.cpp

CMakeFiles/photobooth.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/main.cpp > CMakeFiles/photobooth.dir/main.cpp.i

CMakeFiles/photobooth.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/main.cpp -o CMakeFiles/photobooth.dir/main.cpp.s

CMakeFiles/photobooth.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/main.cpp.o.requires

CMakeFiles/photobooth.dir/main.cpp.o.provides: CMakeFiles/photobooth.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/main.cpp.o.provides

CMakeFiles/photobooth.dir/main.cpp.o.provides.build: CMakeFiles/photobooth.dir/main.cpp.o

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o: qrc_photobooth.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o -c /home/aspotashev/Github/photobooth/old/qrc_photobooth.cpp

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/qrc_photobooth.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/qrc_photobooth.cpp > CMakeFiles/photobooth.dir/qrc_photobooth.cpp.i

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/qrc_photobooth.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/qrc_photobooth.cpp -o CMakeFiles/photobooth.dir/qrc_photobooth.cpp.s

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.requires

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.provides: CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.provides

CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.provides.build: CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o: CMakeFiles/photobooth.dir/flags.make
CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o: photobooth_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/aspotashev/Github/photobooth/old/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o -c /home/aspotashev/Github/photobooth/old/photobooth_automoc.cpp

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photobooth.dir/photobooth_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/aspotashev/Github/photobooth/old/photobooth_automoc.cpp > CMakeFiles/photobooth.dir/photobooth_automoc.cpp.i

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photobooth.dir/photobooth_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/aspotashev/Github/photobooth/old/photobooth_automoc.cpp -o CMakeFiles/photobooth.dir/photobooth_automoc.cpp.s

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.requires:
.PHONY : CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.requires

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.provides: CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/photobooth.dir/build.make CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.provides

CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.provides.build: CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o

# Object files for target photobooth
photobooth_OBJECTS = \
"CMakeFiles/photobooth.dir/parameterslider.cpp.o" \
"CMakeFiles/photobooth.dir/mainwindow.cpp.o" \
"CMakeFiles/photobooth.dir/camera.cpp.o" \
"CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o" \
"CMakeFiles/photobooth.dir/main.cpp.o" \
"CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o" \
"CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o"

# External object files for target photobooth
photobooth_EXTERNAL_OBJECTS =

photobooth: CMakeFiles/photobooth.dir/parameterslider.cpp.o
photobooth: CMakeFiles/photobooth.dir/mainwindow.cpp.o
photobooth: CMakeFiles/photobooth.dir/camera.cpp.o
photobooth: CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o
photobooth: CMakeFiles/photobooth.dir/main.cpp.o
photobooth: CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o
photobooth: CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o
photobooth: CMakeFiles/photobooth.dir/build.make
photobooth: /home/aspotashev/chdkptp/libchdkptp.so
photobooth: /usr/lib/x86_64-linux-gnu/liblua5.2.so
photobooth: /usr/lib/x86_64-linux-gnu/libm.so
photobooth: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.2.1
photobooth: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.2.1
photobooth: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.2.1
photobooth: CMakeFiles/photobooth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable photobooth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/photobooth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/photobooth.dir/build: photobooth
.PHONY : CMakeFiles/photobooth.dir/build

CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/parameterslider.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/mainwindow.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/camera.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/chdkptpmanager.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/main.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/qrc_photobooth.cpp.o.requires
CMakeFiles/photobooth.dir/requires: CMakeFiles/photobooth.dir/photobooth_automoc.cpp.o.requires
.PHONY : CMakeFiles/photobooth.dir/requires

CMakeFiles/photobooth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/photobooth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/photobooth.dir/clean

CMakeFiles/photobooth.dir/depend: ui_mainwindow.h
CMakeFiles/photobooth.dir/depend: ui_parameterslider.h
CMakeFiles/photobooth.dir/depend: qrc_photobooth.cpp
	cd /home/aspotashev/Github/photobooth/old && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aspotashev/Github/photobooth/old /home/aspotashev/Github/photobooth/old /home/aspotashev/Github/photobooth/old /home/aspotashev/Github/photobooth/old /home/aspotashev/Github/photobooth/old/CMakeFiles/photobooth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/photobooth.dir/depend

