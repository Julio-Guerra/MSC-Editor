cmake_minimum_required(VERSION 2.6)
project(MscEditor)

include_directories("${PROJECT_SOURCE_DIR}/parse")
add_subdirectory(parse)

# add the executable
# add_executable (MscEditor main.cc)
target_link_libraries (MscEditor parse)
