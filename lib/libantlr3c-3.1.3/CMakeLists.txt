set(SHELL_EXECUTABLE /bin/sh)
set(MAKE make)

add_custom_target(
  configure-antlr3c
  ${SHELL_EXECUTABLE}  configure
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
  antlr3c
   ${MAKE}
   DEPENDS configure-antlr3c
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
