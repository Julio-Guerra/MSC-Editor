include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3)
include_directories(${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3/include)

add_executable(testparse main)

target_link_libraries(testparse parse msc ${antlr3c})
