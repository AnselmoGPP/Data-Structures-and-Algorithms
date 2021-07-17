@ECHO OFF
ECHO Current directory: 
CD

RD /S /Q ..\_BUILD\projects
MKDIR ..\_BUILD
MKDIR ..\_BUILD\projects
CD ..\_BUILD\projects

cmake -G"Visual Studio 16 2019" ..\..\projects
PAUSE

REM The next step is to build the binaries:
REM 	- Open MVS and set the project you want as "startup project" (proyecto de inicio).
REM 	- Compile with MVS: first, compile static libraries (dependencies); then, the project you want. 
REM 	- Compile both in the same mode (release, debug...) because your program should link (in his CMakeLists.txt) the static libraries compiled in a certain mode.
