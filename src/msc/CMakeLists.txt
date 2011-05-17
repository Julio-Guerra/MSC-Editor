add_library(msc gen-visitor.cc
                message-sequence-chart.cc
                labelable.cc
                message.cc
                instance.cc

)

include_directories(${PROJECT_SOURCE_DIR}/src)
