#include "gui/qt/window.hh"

// temp
#include "msc/instance.hh"
#include "view/qt/gmsc/instance.hh"
// !temp

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
  msc::Instance*          msc_i = new msc::Instance("Instance");
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
  msc::Instance*          msc_instance = new msc::Instance("Instance");
  view::gmsc::Instance*   gmsc_instance = new view::gmsc::Instance(*msc_instance);

  //
  {
    QIcon         icon(gmsc_instance->to_image());
    QToolButton*  button;
    QGridLayout*  layout;
    QWidget*      widget;

    //
    button = new QToolButton();
    button->setIcon(icon);
    button->setIconSize(QSize(70, 70));
    button->setCheckable(true);

    layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel("Instance"), 1, 0, Qt::AlignCenter);

    widget = new QWidget;
    widget->setLayout(layout);

    config_.basic_msc_layout->addWidget(widget, 0, 0, Qt::AlignCenter);

    //
    button = new QToolButton();
    button->setIcon(icon);
    button->setIconSize(QSize(70, 70));
    button->setCheckable(true);

    layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel("Instance"), 1, 0, Qt::AlignCenter);

    widget = new QWidget;
    widget->setLayout(layout);

    config_.basic_msc_layout->addWidget(widget, 0, 1, Qt::AlignCenter);
  }
}
