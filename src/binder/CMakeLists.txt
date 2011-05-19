add_library(binder binder.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIR})
