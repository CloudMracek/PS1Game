# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/jracek/code/engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jracek/code/engine/build

# Include any dependencies generated for this target.
include CMakeFiles/bandwidth.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bandwidth.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bandwidth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bandwidth.dir/flags.make

CMakeFiles/bandwidth.dir/main.c.obj: CMakeFiles/bandwidth.dir/flags.make
CMakeFiles/bandwidth.dir/main.c.obj: ../main.c
CMakeFiles/bandwidth.dir/main.c.obj: CMakeFiles/bandwidth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jracek/code/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bandwidth.dir/main.c.obj"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/bandwidth.dir/main.c.obj -MF CMakeFiles/bandwidth.dir/main.c.obj.d -o CMakeFiles/bandwidth.dir/main.c.obj -c /home/jracek/code/engine/main.c

CMakeFiles/bandwidth.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bandwidth.dir/main.c.i"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jracek/code/engine/main.c > CMakeFiles/bandwidth.dir/main.c.i

CMakeFiles/bandwidth.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bandwidth.dir/main.c.s"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jracek/code/engine/main.c -o CMakeFiles/bandwidth.dir/main.c.s

CMakeFiles/bandwidth.dir/display.c.obj: CMakeFiles/bandwidth.dir/flags.make
CMakeFiles/bandwidth.dir/display.c.obj: ../display.c
CMakeFiles/bandwidth.dir/display.c.obj: CMakeFiles/bandwidth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jracek/code/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/bandwidth.dir/display.c.obj"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/bandwidth.dir/display.c.obj -MF CMakeFiles/bandwidth.dir/display.c.obj.d -o CMakeFiles/bandwidth.dir/display.c.obj -c /home/jracek/code/engine/display.c

CMakeFiles/bandwidth.dir/display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bandwidth.dir/display.c.i"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jracek/code/engine/display.c > CMakeFiles/bandwidth.dir/display.c.i

CMakeFiles/bandwidth.dir/display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bandwidth.dir/display.c.s"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jracek/code/engine/display.c -o CMakeFiles/bandwidth.dir/display.c.s

CMakeFiles/bandwidth.dir/models/cube.c.obj: CMakeFiles/bandwidth.dir/flags.make
CMakeFiles/bandwidth.dir/models/cube.c.obj: ../models/cube.c
CMakeFiles/bandwidth.dir/models/cube.c.obj: CMakeFiles/bandwidth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jracek/code/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/bandwidth.dir/models/cube.c.obj"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/bandwidth.dir/models/cube.c.obj -MF CMakeFiles/bandwidth.dir/models/cube.c.obj.d -o CMakeFiles/bandwidth.dir/models/cube.c.obj -c /home/jracek/code/engine/models/cube.c

CMakeFiles/bandwidth.dir/models/cube.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bandwidth.dir/models/cube.c.i"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jracek/code/engine/models/cube.c > CMakeFiles/bandwidth.dir/models/cube.c.i

CMakeFiles/bandwidth.dir/models/cube.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bandwidth.dir/models/cube.c.s"
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jracek/code/engine/models/cube.c -o CMakeFiles/bandwidth.dir/models/cube.c.s

# Object files for target bandwidth
bandwidth_OBJECTS = \
"CMakeFiles/bandwidth.dir/main.c.obj" \
"CMakeFiles/bandwidth.dir/display.c.obj" \
"CMakeFiles/bandwidth.dir/models/cube.c.obj"

# External object files for target bandwidth
bandwidth_EXTERNAL_OBJECTS =

bandwidth.elf: CMakeFiles/bandwidth.dir/main.c.obj
bandwidth.elf: CMakeFiles/bandwidth.dir/display.c.obj
bandwidth.elf: CMakeFiles/bandwidth.dir/models/cube.c.obj
bandwidth.elf: CMakeFiles/bandwidth.dir/build.make
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxgpu.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxgte.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxspu.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxcd.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxpress.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxsio.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxetc.a
bandwidth.elf: /usr/local/lib/libpsn00b/libpsxapi.a
bandwidth.elf: /usr/local/lib/libpsn00b/liblzp.a
bandwidth.elf: /usr/local/lib/libpsn00b/libc.a
bandwidth.elf: CMakeFiles/bandwidth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jracek/code/engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bandwidth.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bandwidth.dir/link.txt --verbose=$(VERBOSE)
	/usr/local/bin/elf2x -q bandwidth.elf bandwidth.exe
	/usr/local/mipsel-none-elf/bin/mipsel-none-elf-nm -f posix -l -n bandwidth.elf >bandwidth.map

# Rule to build all files generated by this target.
CMakeFiles/bandwidth.dir/build: bandwidth.elf
.PHONY : CMakeFiles/bandwidth.dir/build

CMakeFiles/bandwidth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bandwidth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bandwidth.dir/clean

CMakeFiles/bandwidth.dir/depend:
	cd /home/jracek/code/engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jracek/code/engine /home/jracek/code/engine /home/jracek/code/engine/build /home/jracek/code/engine/build /home/jracek/code/engine/build/CMakeFiles/bandwidth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bandwidth.dir/depend
