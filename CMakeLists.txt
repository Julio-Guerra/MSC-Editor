cmake_minimum_required(VERSION 2.8)
project(msc-editor)

#set(CMAKE_VERBOSE_MAKEFILE on)

#add_subdirectory(lib)
#add_subdirectory(src)
include(ExternalProject)
ExternalProject_Add(
  libantlr3c
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)

add_definitions(-Wall -Wextra -pedantic -Werror -std=c++98)

# add the executable
# add_executable (MscEditor main.cc)
#target_link_libraries (msc-editor libparse)
