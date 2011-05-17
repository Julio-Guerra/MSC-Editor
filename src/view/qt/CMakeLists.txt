INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_LIBRARY(libview graph-view.cc
                    gmsc/instance.cc
)
