# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ivy/emptydemo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivy/emptydemo/build

# Include any dependencies generated for this target.
include CMakeFiles/emptydemo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/emptydemo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/emptydemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/emptydemo.dir/flags.make

CMakeFiles/emptydemo.dir/main.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/main.cpp.o: ../main.cpp
CMakeFiles/emptydemo.dir/main.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/emptydemo.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/main.cpp.o -MF CMakeFiles/emptydemo.dir/main.cpp.o.d -o CMakeFiles/emptydemo.dir/main.cpp.o -c /home/ivy/emptydemo/main.cpp

CMakeFiles/emptydemo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/main.cpp > CMakeFiles/emptydemo.dir/main.cpp.i

CMakeFiles/emptydemo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/main.cpp -o CMakeFiles/emptydemo.dir/main.cpp.s

CMakeFiles/emptydemo.dir/connect.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/connect.cpp.o: ../connect.cpp
CMakeFiles/emptydemo.dir/connect.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/emptydemo.dir/connect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/connect.cpp.o -MF CMakeFiles/emptydemo.dir/connect.cpp.o.d -o CMakeFiles/emptydemo.dir/connect.cpp.o -c /home/ivy/emptydemo/connect.cpp

CMakeFiles/emptydemo.dir/connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/connect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/connect.cpp > CMakeFiles/emptydemo.dir/connect.cpp.i

CMakeFiles/emptydemo.dir/connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/connect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/connect.cpp -o CMakeFiles/emptydemo.dir/connect.cpp.s

CMakeFiles/emptydemo.dir/basicSockets.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/basicSockets.cpp.o: ../basicSockets.cpp
CMakeFiles/emptydemo.dir/basicSockets.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/emptydemo.dir/basicSockets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/basicSockets.cpp.o -MF CMakeFiles/emptydemo.dir/basicSockets.cpp.o.d -o CMakeFiles/emptydemo.dir/basicSockets.cpp.o -c /home/ivy/emptydemo/basicSockets.cpp

CMakeFiles/emptydemo.dir/basicSockets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/basicSockets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/basicSockets.cpp > CMakeFiles/emptydemo.dir/basicSockets.cpp.i

CMakeFiles/emptydemo.dir/basicSockets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/basicSockets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/basicSockets.cpp -o CMakeFiles/emptydemo.dir/basicSockets.cpp.s

CMakeFiles/emptydemo.dir/secondary.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/secondary.cpp.o: ../secondary.cpp
CMakeFiles/emptydemo.dir/secondary.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/emptydemo.dir/secondary.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/secondary.cpp.o -MF CMakeFiles/emptydemo.dir/secondary.cpp.o.d -o CMakeFiles/emptydemo.dir/secondary.cpp.o -c /home/ivy/emptydemo/secondary.cpp

CMakeFiles/emptydemo.dir/secondary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/secondary.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/secondary.cpp > CMakeFiles/emptydemo.dir/secondary.cpp.i

CMakeFiles/emptydemo.dir/secondary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/secondary.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/secondary.cpp -o CMakeFiles/emptydemo.dir/secondary.cpp.s

CMakeFiles/emptydemo.dir/Precompute.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/Precompute.cpp.o: ../Precompute.cpp
CMakeFiles/emptydemo.dir/Precompute.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/emptydemo.dir/Precompute.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/Precompute.cpp.o -MF CMakeFiles/emptydemo.dir/Precompute.cpp.o.d -o CMakeFiles/emptydemo.dir/Precompute.cpp.o -c /home/ivy/emptydemo/Precompute.cpp

CMakeFiles/emptydemo.dir/Precompute.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/Precompute.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/Precompute.cpp > CMakeFiles/emptydemo.dir/Precompute.cpp.i

CMakeFiles/emptydemo.dir/Precompute.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/Precompute.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/Precompute.cpp -o CMakeFiles/emptydemo.dir/Precompute.cpp.s

CMakeFiles/emptydemo.dir/tools.cpp.o: CMakeFiles/emptydemo.dir/flags.make
CMakeFiles/emptydemo.dir/tools.cpp.o: ../tools.cpp
CMakeFiles/emptydemo.dir/tools.cpp.o: CMakeFiles/emptydemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/emptydemo.dir/tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emptydemo.dir/tools.cpp.o -MF CMakeFiles/emptydemo.dir/tools.cpp.o.d -o CMakeFiles/emptydemo.dir/tools.cpp.o -c /home/ivy/emptydemo/tools.cpp

CMakeFiles/emptydemo.dir/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emptydemo.dir/tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivy/emptydemo/tools.cpp > CMakeFiles/emptydemo.dir/tools.cpp.i

CMakeFiles/emptydemo.dir/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emptydemo.dir/tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivy/emptydemo/tools.cpp -o CMakeFiles/emptydemo.dir/tools.cpp.s

# Object files for target emptydemo
emptydemo_OBJECTS = \
"CMakeFiles/emptydemo.dir/main.cpp.o" \
"CMakeFiles/emptydemo.dir/connect.cpp.o" \
"CMakeFiles/emptydemo.dir/basicSockets.cpp.o" \
"CMakeFiles/emptydemo.dir/secondary.cpp.o" \
"CMakeFiles/emptydemo.dir/Precompute.cpp.o" \
"CMakeFiles/emptydemo.dir/tools.cpp.o"

# External object files for target emptydemo
emptydemo_EXTERNAL_OBJECTS =

emptydemo: CMakeFiles/emptydemo.dir/main.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/connect.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/basicSockets.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/secondary.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/Precompute.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/tools.cpp.o
emptydemo: CMakeFiles/emptydemo.dir/build.make
emptydemo: CMakeFiles/emptydemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivy/emptydemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable emptydemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/emptydemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/emptydemo.dir/build: emptydemo
.PHONY : CMakeFiles/emptydemo.dir/build

CMakeFiles/emptydemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/emptydemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/emptydemo.dir/clean

CMakeFiles/emptydemo.dir/depend:
	cd /home/ivy/emptydemo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivy/emptydemo /home/ivy/emptydemo /home/ivy/emptydemo/build /home/ivy/emptydemo/build /home/ivy/emptydemo/build/CMakeFiles/emptydemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/emptydemo.dir/depend

