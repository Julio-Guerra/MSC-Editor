#include <QtGui/QApplication>

#include "view/qt/graph-view.hh"
#include "gui/qt/msc-editor.h"

int main(int argc, char **argv)
{
  QApplication    app(argc, argv);
  QMainWindow*    window = new QMainWindow();
  Ui_MainWindow*  gui = new Ui_MainWindow();

  gui->setupUi(window);
  window->show();

  return app.exec();
}