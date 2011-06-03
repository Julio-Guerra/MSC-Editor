ADD_LIBRARY(view  graph-view.cc
                  dtor.cc
                  decorator.cc
                  gmsc/instance.cc
                  gmsc/factory.cc
                  gmsc/message.cc
)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3/include
  ${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3
)
