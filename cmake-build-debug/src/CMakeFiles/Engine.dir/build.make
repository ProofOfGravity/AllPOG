# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CodeBase\AllPOG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CodeBase\AllPOG\cmake-build-debug

# Include any dependencies generated for this target.
include src\CMakeFiles\Engine.dir\depend.make

# Include the progress variables for this target.
include src\CMakeFiles\Engine.dir\progress.make

# Include the compile flags for this target's objects.
include src\CMakeFiles\Engine.dir\flags.make

src\CMakeFiles\Engine.dir\testLib.cpp.obj: src\CMakeFiles\Engine.dir\flags.make
src\CMakeFiles\Engine.dir\testLib.cpp.obj: ..\src\testLib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CodeBase\AllPOG\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Engine.dir/testLib.cpp.obj"
	cd C:\CodeBase\AllPOG\cmake-build-debug\src
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Engine.dir\testLib.cpp.obj /FdCMakeFiles\Engine.dir\ /FS -c C:\CodeBase\AllPOG\src\testLib.cpp
<<
	cd C:\CodeBase\AllPOG\cmake-build-debug

src\CMakeFiles\Engine.dir\testLib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/testLib.cpp.i"
	cd C:\CodeBase\AllPOG\cmake-build-debug\src
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\Engine.dir\testLib.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CodeBase\AllPOG\src\testLib.cpp
<<
	cd C:\CodeBase\AllPOG\cmake-build-debug

src\CMakeFiles\Engine.dir\testLib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/testLib.cpp.s"
	cd C:\CodeBase\AllPOG\cmake-build-debug\src
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Engine.dir\testLib.cpp.s /c C:\CodeBase\AllPOG\src\testLib.cpp
<<
	cd C:\CodeBase\AllPOG\cmake-build-debug

# Object files for target Engine
Engine_OBJECTS = \
"CMakeFiles\Engine.dir\testLib.cpp.obj"

# External object files for target Engine
Engine_EXTERNAL_OBJECTS =

bin\Engine.dll: src\CMakeFiles\Engine.dir\testLib.cpp.obj
bin\Engine.dll: src\CMakeFiles\Engine.dir\build.make
bin\Engine.dll: src\CMakeFiles\Engine.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CodeBase\AllPOG\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ..\bin\Engine.dll"
	cd C:\CodeBase\AllPOG\cmake-build-debug\src
	"C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_dll --intdir=CMakeFiles\Engine.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Engine.dir\objects1.rsp @<<
 /out:..\bin\Engine.dll /implib:Engine.lib /pdb:C:\CodeBase\AllPOG\cmake-build-debug\bin\Engine.pdb /dll /version:0.0 /machine:X86 /debug /INCREMENTAL  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<
	cd C:\CodeBase\AllPOG\cmake-build-debug

# Rule to build all files generated by this target.
src\CMakeFiles\Engine.dir\build: bin\Engine.dll

.PHONY : src\CMakeFiles\Engine.dir\build

src\CMakeFiles\Engine.dir\clean:
	cd C:\CodeBase\AllPOG\cmake-build-debug\src
	$(CMAKE_COMMAND) -P CMakeFiles\Engine.dir\cmake_clean.cmake
	cd C:\CodeBase\AllPOG\cmake-build-debug
.PHONY : src\CMakeFiles\Engine.dir\clean

src\CMakeFiles\Engine.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\CodeBase\AllPOG C:\CodeBase\AllPOG\src C:\CodeBase\AllPOG\cmake-build-debug C:\CodeBase\AllPOG\cmake-build-debug\src C:\CodeBase\AllPOG\cmake-build-debug\src\CMakeFiles\Engine.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src\CMakeFiles\Engine.dir\depend

