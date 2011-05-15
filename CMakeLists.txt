cmake_minimum_required(VERSION 2.8)
project(msc-editor)

set(CMAKE_C_COMPILER    g++)
set(MAKE                make)

#include(ExternalProject)
#externalproject_add(
#  antlr3c
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
#  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.13
#  BUILD_COMMAND $(MAKE)
#  BUILD_IN_SOURCE 1
#)

add_subdirectory(src)
#add_subdirectory(tests)

add_definitions(-Wall -Wextra -pedantic -Werror -std=c++98)

# add the executable
# add_executable (MscEditor main.cc)
#target_link_libraries (msc-editor libmsc)
