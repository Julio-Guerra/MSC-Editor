PROJECT(MSC_EDITOR)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#include(ExternalProject)
#externalproject_add(
#  libantlr3c
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
#  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
#  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
#  BUILD_COMMAND make
#  BUILD_IN_SOURCE 1
#)

add_subdirectory(src)

# add the executable
# add_executable (MscEditor main.cc)
#target_link_libraries (msc-editor libmsc)
