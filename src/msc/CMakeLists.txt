add_library(msc gen-visitor.cc
                default-visitor.cc
                labelable.cc
                message-sequence-chart.cc
                basic-msc.cc
                instance.cc
                instance-head.cc
                identifier.cc
                message.cc
                factory.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/lib
                    ${Boost_INCLUDE_DIR})
