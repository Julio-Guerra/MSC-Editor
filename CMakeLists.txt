PROJECT(MSC_EDITOR)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(CMAKE_C_COMPILER    g++)
set(MAKE                make)
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

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

set(CMAKE_C_COMPILER    g++)
set(MAKE                make)

# Qt4 package
FIND_PACKAGE(Qt4 REQUIRED)

# Qt modules
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)

# add the executable
ADD_EXECUTABLE(msce src/msce.cc)
TARGET_LINK_LIBRARIES(msce gui view msc ${QT_LIBRARIES})
