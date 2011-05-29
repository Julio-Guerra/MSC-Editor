add_library(parse       MscLexer.c
                        MscParser.c
)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/parse")
include_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories("${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3")
