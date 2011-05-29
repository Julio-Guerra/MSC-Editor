include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3/include)

add_executable(testparse parse)
target_link_libraries(testparse parse msc misc ${antlr3c})

add_executable(testpretty-printer pretty-printer)
target_link_libraries(testpretty-printer parse msc misc ${antlr3c})
