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
CMAKE_COMMAND = "/Users/lokyin/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/lokyin/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/EXP_src.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EXP_src.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EXP_src.dir/flags.make

CMakeFiles/EXP_src.dir/main.cpp.o: CMakeFiles/EXP_src.dir/flags.make
CMakeFiles/EXP_src.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EXP_src.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EXP_src.dir/main.cpp.o -c "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/main.cpp"

CMakeFiles/EXP_src.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EXP_src.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/main.cpp" > CMakeFiles/EXP_src.dir/main.cpp.i

CMakeFiles/EXP_src.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EXP_src.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/main.cpp" -o CMakeFiles/EXP_src.dir/main.cpp.s

# Object files for target EXP_src
EXP_src_OBJECTS = \
"CMakeFiles/EXP_src.dir/main.cpp.o"

# External object files for target EXP_src
EXP_src_EXTERNAL_OBJECTS =

EXP_src: CMakeFiles/EXP_src.dir/main.cpp.o
EXP_src: CMakeFiles/EXP_src.dir/build.make
EXP_src: CMakeFiles/EXP_src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EXP_src"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EXP_src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EXP_src.dir/build: EXP_src

.PHONY : CMakeFiles/EXP_src.dir/build

CMakeFiles/EXP_src.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EXP_src.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EXP_src.dir/clean

CMakeFiles/EXP_src.dir/depend:
	cd "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src" "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src" "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug" "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug" "/Users/lokyin/OneDrive/MyEXP/DataStructure/EXP src/cmake-build-debug/CMakeFiles/EXP_src.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/EXP_src.dir/depend

