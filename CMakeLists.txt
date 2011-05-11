cmake_minimum_required(VERSION 2.6)
project(msc-editor)

#set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(lib)
#add_subdirectory(src)

add_definitions(-Wall -Wextra -pedantic -Werror -std=c++98)

# add the executable
# add_executable (MscEditor main.cc)
#target_link_libraries (msc-editor libparse)
