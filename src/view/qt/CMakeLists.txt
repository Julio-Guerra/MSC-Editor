ADD_LIBRARY(view  graph-view.cc
                  dtor.cc
                  gmsc/instance.cc
                  gmsc/factory.cc
                  gmsc/message.cc
)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/lib
)
