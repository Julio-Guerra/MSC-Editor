PROJECT(MSC_EDITOR)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#include(ExternalProject)
#externalproject_add(
#  antlr3c
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
#  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.13
#  BUILD_COMMAND $(MAKE)
#  BUILD_IN_SOURCE 1
#)

set(CMAKE_C_COMPILER    g++)
set(MAKE                make)

# Qt4 package
FIND_PACKAGE(Qt4 REQUIRED)

# Qt modules
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
#add_subdirectory(tests)
add_definitions(-g -ggdb)

# add the executable
ADD_EXECUTABLE(msce src/msce.cc)
TARGET_LINK_LIBRARIES(msce gui view msc ${QT_LIBRARIES})
