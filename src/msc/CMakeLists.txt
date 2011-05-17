add_library(msc gen-visitor.cc
                labelable.cc
                message-sequence-chart.cc
                basic-msc.cc
                text-definition.cc

                message.cc
                instance.cc
)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIR})
