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

add_definitions(-g -ggdb)

# Qt4 package
FIND_PACKAGE(Qt4 REQUIRED)

# Qt modules
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_SUBDIRECTORY(src)

# add the executable
ADD_EXECUTABLE(msce src/msce.cc)
TARGET_LINK_LIBRARIES(msce libgui libview libmsc ${QT_LIBRARIES})
