# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/juliano/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/juliano/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/PCSemaforo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PCSemaforo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PCSemaforo.dir/flags.make

CMakeFiles/PCSemaforo.dir/main.cpp.o: CMakeFiles/PCSemaforo.dir/flags.make
CMakeFiles/PCSemaforo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PCSemaforo.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PCSemaforo.dir/main.cpp.o -c "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/main.cpp"

CMakeFiles/PCSemaforo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCSemaforo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/main.cpp" > CMakeFiles/PCSemaforo.dir/main.cpp.i

CMakeFiles/PCSemaforo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCSemaforo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/main.cpp" -o CMakeFiles/PCSemaforo.dir/main.cpp.s

CMakeFiles/PCSemaforo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/PCSemaforo.dir/main.cpp.o.requires

CMakeFiles/PCSemaforo.dir/main.cpp.o.provides: CMakeFiles/PCSemaforo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/PCSemaforo.dir/build.make CMakeFiles/PCSemaforo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/PCSemaforo.dir/main.cpp.o.provides

CMakeFiles/PCSemaforo.dir/main.cpp.o.provides.build: CMakeFiles/PCSemaforo.dir/main.cpp.o


# Object files for target PCSemaforo
PCSemaforo_OBJECTS = \
"CMakeFiles/PCSemaforo.dir/main.cpp.o"

# External object files for target PCSemaforo
PCSemaforo_EXTERNAL_OBJECTS =

PCSemaforo: CMakeFiles/PCSemaforo.dir/main.cpp.o
PCSemaforo: CMakeFiles/PCSemaforo.dir/build.make
PCSemaforo: CMakeFiles/PCSemaforo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PCSemaforo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PCSemaforo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PCSemaforo.dir/build: PCSemaforo

.PHONY : CMakeFiles/PCSemaforo.dir/build

CMakeFiles/PCSemaforo.dir/requires: CMakeFiles/PCSemaforo.dir/main.cpp.o.requires

.PHONY : CMakeFiles/PCSemaforo.dir/requires

CMakeFiles/PCSemaforo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PCSemaforo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PCSemaforo.dir/clean

CMakeFiles/PCSemaforo.dir/depend:
	cd "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo" "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo" "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug" "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug" "/home/juliano/Projetos/Sistemas Distribuídos/TP2/PCSemaforo/cmake-build-debug/CMakeFiles/PCSemaforo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PCSemaforo.dir/depend

