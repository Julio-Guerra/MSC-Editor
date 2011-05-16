#include <QtGui/QApplication>
#include <iostream>

#include "view/qt/graph-view.hh"
#include "gui/qt/msc-editor.h"
#include "view/qt/gmsc/types.hh"

int main(int argc, char **argv)
{
  QApplication          app(argc, argv);
  QMainWindow*          window = new QMainWindow();
  Ui_MainWindow*        gui = new Ui_MainWindow();
  QGraphicsScene        scene;
  msc::Instance*        msc_i = new msc::Instance();
  view::gmsc::Instance* i = new view::gmsc::Instance(*msc_i);

  gui->setupUi(window);

  i->label_set("Instance1");
  gui->graphicsView->setScene(&scene);
  (*gui->graphicsView)(*i);

  window->show();

  return app.exec();
}