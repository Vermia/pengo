# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vermia/pengo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vermia/pengo/build

# Include any dependencies generated for this target.
include CMakeFiles/Huevos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Huevos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Huevos.dir/flags.make

CMakeFiles/Huevos.dir/probarHuevo.cpp.o: CMakeFiles/Huevos.dir/flags.make
CMakeFiles/Huevos.dir/probarHuevo.cpp.o: ../probarHuevo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vermia/pengo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Huevos.dir/probarHuevo.cpp.o"
	/usr/bin/g++-5   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Huevos.dir/probarHuevo.cpp.o -c /home/vermia/pengo/probarHuevo.cpp

CMakeFiles/Huevos.dir/probarHuevo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Huevos.dir/probarHuevo.cpp.i"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vermia/pengo/probarHuevo.cpp > CMakeFiles/Huevos.dir/probarHuevo.cpp.i

CMakeFiles/Huevos.dir/probarHuevo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Huevos.dir/probarHuevo.cpp.s"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vermia/pengo/probarHuevo.cpp -o CMakeFiles/Huevos.dir/probarHuevo.cpp.s

CMakeFiles/Huevos.dir/probarHuevo.cpp.o.requires:

.PHONY : CMakeFiles/Huevos.dir/probarHuevo.cpp.o.requires

CMakeFiles/Huevos.dir/probarHuevo.cpp.o.provides: CMakeFiles/Huevos.dir/probarHuevo.cpp.o.requires
	$(MAKE) -f CMakeFiles/Huevos.dir/build.make CMakeFiles/Huevos.dir/probarHuevo.cpp.o.provides.build
.PHONY : CMakeFiles/Huevos.dir/probarHuevo.cpp.o.provides

CMakeFiles/Huevos.dir/probarHuevo.cpp.o.provides.build: CMakeFiles/Huevos.dir/probarHuevo.cpp.o


# Object files for target Huevos
Huevos_OBJECTS = \
"CMakeFiles/Huevos.dir/probarHuevo.cpp.o"

# External object files for target Huevos
Huevos_EXTERNAL_OBJECTS =

Huevos: CMakeFiles/Huevos.dir/probarHuevo.cpp.o
Huevos: CMakeFiles/Huevos.dir/build.make
Huevos: liblibClases.a
Huevos: /usr/lib/x86_64-linux-gnu/libsfml-system.so
Huevos: /usr/lib/x86_64-linux-gnu/libsfml-window.so
Huevos: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
Huevos: /usr/lib/x86_64-linux-gnu/libsfml-network.so
Huevos: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
Huevos: CMakeFiles/Huevos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vermia/pengo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Huevos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Huevos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Huevos.dir/build: Huevos

.PHONY : CMakeFiles/Huevos.dir/build

CMakeFiles/Huevos.dir/requires: CMakeFiles/Huevos.dir/probarHuevo.cpp.o.requires

.PHONY : CMakeFiles/Huevos.dir/requires

CMakeFiles/Huevos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Huevos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Huevos.dir/clean

CMakeFiles/Huevos.dir/depend:
	cd /home/vermia/pengo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vermia/pengo /home/vermia/pengo /home/vermia/pengo/build /home/vermia/pengo/build /home/vermia/pengo/build/CMakeFiles/Huevos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Huevos.dir/depend

