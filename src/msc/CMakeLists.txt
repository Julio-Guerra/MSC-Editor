add_library(msc gen-visitor.cc
                default-visitor.cc
                labelable.cc
                message-sequence-chart.cc
                basic-msc.cc
                text-definition.cc
                instance.cc
                instance-head.cc
                identifier.cc
                message.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIR})
