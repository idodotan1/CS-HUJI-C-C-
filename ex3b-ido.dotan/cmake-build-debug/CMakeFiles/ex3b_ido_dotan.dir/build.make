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
CMAKE_SOURCE_DIR = "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ex3b_ido_dotan.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ex3b_ido_dotan.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3b_ido_dotan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3b_ido_dotan.dir/flags.make

CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o: CMakeFiles/ex3b_ido_dotan.dir/flags.make
CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o: ../linked_list.c
CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o: CMakeFiles/ex3b_ido_dotan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o -MF CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o.d -o CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o -c "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/linked_list.c"

CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/linked_list.c" > CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.i

CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/linked_list.c" -o CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.s

CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o: CMakeFiles/ex3b_ido_dotan.dir/flags.make
CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o: ../markov_chain.c
CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o: CMakeFiles/ex3b_ido_dotan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o -MF CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o.d -o CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o -c "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/markov_chain.c"

CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/markov_chain.c" > CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.i

CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/markov_chain.c" -o CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.s

CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o: CMakeFiles/ex3b_ido_dotan.dir/flags.make
CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o: ../tweets_generator.c
CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o: CMakeFiles/ex3b_ido_dotan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o -MF CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o.d -o CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o -c "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/tweets_generator.c"

CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/tweets_generator.c" > CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.i

CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/tweets_generator.c" -o CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.s

# Object files for target ex3b_ido_dotan
ex3b_ido_dotan_OBJECTS = \
"CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o" \
"CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o" \
"CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o"

# External object files for target ex3b_ido_dotan
ex3b_ido_dotan_EXTERNAL_OBJECTS =

ex3b_ido_dotan: CMakeFiles/ex3b_ido_dotan.dir/linked_list.c.o
ex3b_ido_dotan: CMakeFiles/ex3b_ido_dotan.dir/markov_chain.c.o
ex3b_ido_dotan: CMakeFiles/ex3b_ido_dotan.dir/tweets_generator.c.o
ex3b_ido_dotan: CMakeFiles/ex3b_ido_dotan.dir/build.make
ex3b_ido_dotan: CMakeFiles/ex3b_ido_dotan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ex3b_ido_dotan"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex3b_ido_dotan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3b_ido_dotan.dir/build: ex3b_ido_dotan
.PHONY : CMakeFiles/ex3b_ido_dotan.dir/build

CMakeFiles/ex3b_ido_dotan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex3b_ido_dotan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex3b_ido_dotan.dir/clean

CMakeFiles/ex3b_ido_dotan.dir/depend:
	cd "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan" "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan" "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug" "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug" "/mnt/c/Users/idodo/Desktop/לימודים/C & C++/ex3b-ido.dotan/cmake-build-debug/CMakeFiles/ex3b_ido_dotan.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ex3b_ido_dotan.dir/depend

