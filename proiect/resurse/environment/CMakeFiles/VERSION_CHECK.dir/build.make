# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/luigi/Documente/pa/proiect/resurse/environment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luigi/Documente/pa/proiect/resurse/environment

# Utility rule file for VERSION_CHECK.

# Include the progress variables for this target.
include CMakeFiles/VERSION_CHECK.dir/progress.make

CMakeFiles/VERSION_CHECK:
	./set_version.sh

VERSION_CHECK: CMakeFiles/VERSION_CHECK
VERSION_CHECK: CMakeFiles/VERSION_CHECK.dir/build.make

.PHONY : VERSION_CHECK

# Rule to build all files generated by this target.
CMakeFiles/VERSION_CHECK.dir/build: VERSION_CHECK

.PHONY : CMakeFiles/VERSION_CHECK.dir/build

CMakeFiles/VERSION_CHECK.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VERSION_CHECK.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VERSION_CHECK.dir/clean

CMakeFiles/VERSION_CHECK.dir/depend:
	cd /home/luigi/Documente/pa/proiect/resurse/environment && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luigi/Documente/pa/proiect/resurse/environment /home/luigi/Documente/pa/proiect/resurse/environment /home/luigi/Documente/pa/proiect/resurse/environment /home/luigi/Documente/pa/proiect/resurse/environment /home/luigi/Documente/pa/proiect/resurse/environment/CMakeFiles/VERSION_CHECK.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VERSION_CHECK.dir/depend
