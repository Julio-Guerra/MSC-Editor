#include "gui/qt/window.hh"
#include "view/qt/gmsc/all.hh"


using namespace gui;

Window::Window()
{
  config_.setupUi(this);
  this->create_toolbox();

  scene_ = new Scene();
  config_.graphics_view->setScene(scene_);

  connect(scene_, SIGNAL(itemInserted(QGraphicsPolygonItem*)), this, SLOT(itemInserted(QGraphicsPolygonItem*)));
}

void Window::open_msc_file()
{
  // Ask whether to save the current scene if the old scene has objects

  // Create a new scene
  scene_ = new Scene();

  // Set the new scene
  config_.graphics_view->setScene(scene_);

}

void Window::save_msc_file()
{

}

// Private methods
void Window::create_toolbox()
{
  view::gmsc::Instance* gmsc_instance = view::gmsc::Factory::instance().create_instance();
  QIcon                 icon(gmsc_instance->to_image());
  QToolButton*          button;
  QGridLayout*          layout;
  QWidget*              widget;

  //
  buttonGroup_ = new QButtonGroup(this);
  buttonGroup_->setExclusive(false);
  connect(buttonGroup_, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));

  //
  button = new QToolButton();
  button->setIcon(icon);
  button->setIconSize(QSize(70, 70));
  button->setCheckable(true);
  buttonGroup_->addButton(button, view::gmsc::Factory::ITEM_TYPE_INSTANCE);

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
  buttonGroup_->addButton(button, view::gmsc::Factory::ITEM_TYPE_MESSAGE);

  layout = new QGridLayout;
  layout->addWidget(button, 0, 0, Qt::AlignHCenter);
  layout->addWidget(new QLabel("Message"), 1, 0, Qt::AlignCenter);

  widget = new QWidget;
  widget->setLayout(layout);

  config_.basic_msc_layout->addWidget(widget, 0, 1, Qt::AlignCenter);
}

// Slots
void Window::buttonGroupClicked(int id)
{
  scene_->set_type(view::gmsc::Factory::ItemType(id));

  if (id == view::gmsc::Factory::ITEM_TYPE_MESSAGE)
    scene_->set_mode(Scene::MODE_LINE_INSERTION);
  else
    scene_->set_mode(Scene::MODE_ITEM_INSERTION);

  if (buttonGroup_->checkedButton() == NULL)
    scene_->set_mode(Scene::MODE_SELECT);
}

void Window::itemInserted(QGraphicsPolygonItem*)
{
  QList<QAbstractButton *> buttons = buttonGroup_->buttons();

  foreach (QAbstractButton *button, buttons)
  {
    button->setChecked(false);
  }

  scene_->set_mode(Scene::MODE_SELECT);
}
