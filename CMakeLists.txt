cmake_minimum_required(VERSION 2.8)
project(msc-editor)

set(CMAKE_C_COMPILER    g++)
set(MAKE                make)
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -std=c++98")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++98")


include(ExternalProject)
externalproject_add(
  libantlr3c
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)

find_library(
  antlr3c
  libantlr3c.a
  HINTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/lib
)

find_package(Boost REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

add_definitions()

# add the executable
# add_executable (MscEditor main.cc)

# target_link_libraries (msc-editor msc)
