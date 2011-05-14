add_library(libmsc gen-visitor.cc
                   msc.cc
                   labelable.cc
                   instance.cc
                   message.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src)
