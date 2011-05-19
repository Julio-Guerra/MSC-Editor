# Qt modules
INCLUDE(${QT_USE_FILE})

# UI Sources
SET(MSC_EDITOR_UI
  msc-editor.ui
)

# Build ui files
QT4_WRAP_UI(MSC_EDITOR_SOURCES ${MSC_EDITOR_UI})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_LIBRARY(gui window.cc
                window-moc.cc
                scene.cc
                scene-moc.cc
                arrow.cc
)

