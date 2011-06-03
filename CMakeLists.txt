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
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/configure -prefix=${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr3c-3.1.3/lib/libantlr3c.a)

# Boost
find_package(Boost REQUIRED)

# Qt4
find_package(Qt4 REQUIRED)

# Qt modules
include(${QT_USE_FILE})

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/src)

# add the executable
add_executable(msce src/msce.cc)
target_link_libraries(msce gui view ${QT_LIBRARIES} parse msc misc)
