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
CMAKE_SOURCE_DIR = /home/huziang/Desktop/MdServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huziang/Desktop/MdServer/build

# Include any dependencies generated for this target.
include src/CMakeFiles/CtpSystem.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CtpSystem.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CtpSystem.dir/flags.make

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o: src/CMakeFiles/CtpSystem.dir/flags.make
src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o: ../src/Md/CustomMdSpi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o -c /home/huziang/Desktop/MdServer/src/Md/CustomMdSpi.cpp

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.i"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huziang/Desktop/MdServer/src/Md/CustomMdSpi.cpp > CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.i

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.s"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huziang/Desktop/MdServer/src/Md/CustomMdSpi.cpp -o CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.s

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.requires:

.PHONY : src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.requires

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.provides: src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CtpSystem.dir/build.make src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.provides.build
.PHONY : src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.provides

src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.provides.build: src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o


src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o: src/CMakeFiles/CtpSystem.dir/flags.make
src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o: ../src/Md/MdEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o -c /home/huziang/Desktop/MdServer/src/Md/MdEngine.cpp

src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.i"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huziang/Desktop/MdServer/src/Md/MdEngine.cpp > CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.i

src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.s"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huziang/Desktop/MdServer/src/Md/MdEngine.cpp -o CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.s

src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.requires:

.PHONY : src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.requires

src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.provides: src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CtpSystem.dir/build.make src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.provides.build
.PHONY : src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.provides

src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.provides.build: src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o


src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o: src/CMakeFiles/CtpSystem.dir/flags.make
src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o: ../src/Main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CtpSystem.dir/Main/main.cpp.o -c /home/huziang/Desktop/MdServer/src/Main/main.cpp

src/CMakeFiles/CtpSystem.dir/Main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CtpSystem.dir/Main/main.cpp.i"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huziang/Desktop/MdServer/src/Main/main.cpp > CMakeFiles/CtpSystem.dir/Main/main.cpp.i

src/CMakeFiles/CtpSystem.dir/Main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CtpSystem.dir/Main/main.cpp.s"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huziang/Desktop/MdServer/src/Main/main.cpp -o CMakeFiles/CtpSystem.dir/Main/main.cpp.s

src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.requires:

.PHONY : src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.requires

src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.provides: src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CtpSystem.dir/build.make src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.provides

src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.provides.build: src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o


src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o: src/CMakeFiles/CtpSystem.dir/flags.make
src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o: ../src/Main/IniConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o -c /home/huziang/Desktop/MdServer/src/Main/IniConfig.cpp

src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.i"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huziang/Desktop/MdServer/src/Main/IniConfig.cpp > CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.i

src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.s"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huziang/Desktop/MdServer/src/Main/IniConfig.cpp -o CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.s

src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.requires:

.PHONY : src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.requires

src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.provides: src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CtpSystem.dir/build.make src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.provides.build
.PHONY : src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.provides

src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.provides.build: src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o


src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o: src/CMakeFiles/CtpSystem.dir/flags.make
src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o: ../src/OutputAdapter/OutputAdapter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o -c /home/huziang/Desktop/MdServer/src/OutputAdapter/OutputAdapter.cpp

src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.i"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huziang/Desktop/MdServer/src/OutputAdapter/OutputAdapter.cpp > CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.i

src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.s"
	cd /home/huziang/Desktop/MdServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huziang/Desktop/MdServer/src/OutputAdapter/OutputAdapter.cpp -o CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.s

src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.requires:

.PHONY : src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.requires

src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.provides: src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/CtpSystem.dir/build.make src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.provides.build
.PHONY : src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.provides

src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.provides.build: src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o


# Object files for target CtpSystem
CtpSystem_OBJECTS = \
"CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o" \
"CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o" \
"CMakeFiles/CtpSystem.dir/Main/main.cpp.o" \
"CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o" \
"CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o"

# External object files for target CtpSystem
CtpSystem_EXTERNAL_OBJECTS =

../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/build.make
../bin/CtpSystem: src/CMakeFiles/CtpSystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huziang/Desktop/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../../bin/CtpSystem"
	cd /home/huziang/Desktop/MdServer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CtpSystem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/CtpSystem.dir/build: ../bin/CtpSystem

.PHONY : src/CMakeFiles/CtpSystem.dir/build

src/CMakeFiles/CtpSystem.dir/requires: src/CMakeFiles/CtpSystem.dir/Md/CustomMdSpi.cpp.o.requires
src/CMakeFiles/CtpSystem.dir/requires: src/CMakeFiles/CtpSystem.dir/Md/MdEngine.cpp.o.requires
src/CMakeFiles/CtpSystem.dir/requires: src/CMakeFiles/CtpSystem.dir/Main/main.cpp.o.requires
src/CMakeFiles/CtpSystem.dir/requires: src/CMakeFiles/CtpSystem.dir/Main/IniConfig.cpp.o.requires
src/CMakeFiles/CtpSystem.dir/requires: src/CMakeFiles/CtpSystem.dir/OutputAdapter/OutputAdapter.cpp.o.requires

.PHONY : src/CMakeFiles/CtpSystem.dir/requires

src/CMakeFiles/CtpSystem.dir/clean:
	cd /home/huziang/Desktop/MdServer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/CtpSystem.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/CtpSystem.dir/clean

src/CMakeFiles/CtpSystem.dir/depend:
	cd /home/huziang/Desktop/MdServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huziang/Desktop/MdServer /home/huziang/Desktop/MdServer/src /home/huziang/Desktop/MdServer/build /home/huziang/Desktop/MdServer/build/src /home/huziang/Desktop/MdServer/build/src/CMakeFiles/CtpSystem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/CtpSystem.dir/depend
