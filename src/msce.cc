#include <QtGui/QApplication>

#include "view/qt/graph-view.hh"
#include "view/qt/gmsc/types.hh"
#include "gui/qt/window.hh"

int main(int argc, char **argv)
{
  QApplication          app(argc, argv);
  gui::Window*          window = new gui::Window();

  window->show();

  return app.exec();
}