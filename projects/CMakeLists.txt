# cd /home/username/dev/visual/_BUILD
# cmake -G"Unix Makefiles" ..
# cmake -G"Visual Studio 15 2017 Win64" ..
# cmake -G"Visual Studio 15 2017 Win32" ..

CMAKE_MINIMUM_REQUIRED (VERSION 3.12)
PROJECT (Data_Structures_and_Algorithms)

MESSAGE(STATUS "CMake version: " ${CMAKE_MAJOR_VERSION} "." ${CMAKE_MINOR_VERSION})

SET(PROJ_NAME "data_structures")
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_NAME})
SET(PROJ_NAME "algorithms")
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_NAME})
SET(PROJ_NAME "design_patterns")
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_NAME})