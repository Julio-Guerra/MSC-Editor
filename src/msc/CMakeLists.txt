add_library(msc gen-visitor.cc
                msc.cc
                labelable.cc
                message.cc
                instance.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src)
