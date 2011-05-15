include_directories(${MSC-EDITOR_SOURCE_DIR}/msc)

add_executable(testparse main)

target_link_libraries(testparse msc parse libantlr3c)
