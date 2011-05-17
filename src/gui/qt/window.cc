#include "window.hh"

using namespace gui;

Window::Window()
{
  scene_ = new QGraphicsScene();

  config_.setupUi(this);
  this->create_toolbox();
  
  config_.graphics_view->setScene(scene_);
}

void Window::open_msc_file()
{
  // Ask whether to save the current scene if the old scene has objects
  
  // Create a new scene
  scene_ = new QGraphicsScene();
  
  // Set the new scene
  config_.graphics_view->setScene(scene_);
  
  // Temporary test
  msc::Instance*          msc_i = new msc::Instance();
  view::gmsc::Instance*   i = new view::gmsc::Instance(*msc_i);
  
  i->label_set("Instance 1");
  (*config_.graphics_view)(*i);
}

void Window::save_msc_file()
{
  
}

// Private methods
void Window::create_toolbox()
{
  msc::Instance*          msc_instance = new msc::Instance();
  view::gmsc::Instance*   gmsc_instance = new view::gmsc::Instance(*msc_instance);

  //
  gmsc_instance->label_set("Instance");
    
  //
  QPixmap  pixmap(250, 250);
  QPainter painter(&pixmap);
  pixmap.fill(Qt::transparent);
  painter.setPen(QPen(Qt::black, 4));
  painter.translate(100, 100);
  painter.drawPolyline(gmsc_instance->polygon());
  
  //
  QIcon         icon(pixmap);
  QToolButton*  button = new QToolButton();
  button->setIcon(icon);
  button->setIconSize(QSize(50, 50));
  button->setCheckable(true);
  
  //
  config_.basic_msc_layout->addWidget(button);
}