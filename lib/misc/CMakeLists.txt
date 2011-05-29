add_library(misc symbol.cc exception.cc)

include_directories(${PROJECT_SOURCE_DIR}/lib ${Boost_INCLUDE_DIR})
