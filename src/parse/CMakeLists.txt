add_library(libparse    MscLexer.c
                        MscParser.c)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/lib/libantlr3c-3.1.3")
