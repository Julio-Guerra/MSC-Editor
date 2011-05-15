add_library(msc gen-visitor.cc
                msc.cc
                labelable.cc
                instance.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src)
