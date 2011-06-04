#include <fstream>

#include "gui/qt/window.hh"
#include "view/qt/gmsc/all.hh"
#include "view/qt/decorator.hh"

#undef emit // Avoid the Qt's define to replace our emit vars/funs.

#include "parse/parser.hh"
#include "parse/exception.hh"
#include "msc/pretty-printer.hh"

using namespace gui;

Window::Window()
  : filename_ ("")
{
  config_.setupUi(this);
  this->create_toolbox();

  scene_ = new Scene();
  config_.graphics_view->setScene(scene_);

  connect(scene_, SIGNAL(itemInserted(QGraphicsPolygonItem*)), this, SLOT(itemInserted(QGraphicsPolygonItem*)));
  config_.actionOpen->setShortcut(tr("Ctrl+O"));
  connect(config_.actionOpen, SIGNAL(triggered()), this, SLOT(open_msc_file()));
  config_.actionSave->setShortcut(tr("Ctrl+S"));
  connect(config_.actionSave, SIGNAL(triggered()), this, SLOT(save_msc_file()));
  connect(config_.actionSave_as, SIGNAL(triggered()), this, SLOT(save_msc_file_as()));

  create_new_msc();
}

void Window::create_new_msc()
{
  if (scene_ != NULL)
  {
    std::vector<msc::Statement*>* statements = new std::vector<msc::Statement*> ();
    msc::DocumentHead*            documentHead = new msc::DocumentHead(new msc::String(misc::Symbol::fresh("document")),
                                                                       NULL);
    msc::BasicMsc*                basicMsc = new msc::BasicMsc(*statements);
    msc::MessageSequenceChart*    messageSequenceChart = new msc::MessageSequenceChart(misc::Symbol::fresh("msc"),
                                                                                     msc::MessageSequenceChart::UNKNOWN,
                                                                                     basicMsc);
    msc::Document*              document = new msc::Document(documentHead, messageSequenceChart);

    scene_->root_set(document);
    scene_->statements_set(statements);
  }
}

void Window::open_msc_file()
{
  // Ask whether to save the current scene if the old scene has objects
  if ((scene_ != NULL) && (scene_->items().count() != 0))
  {
    QMessageBox msgBox;

    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Save);

    {
      int ret = msgBox.exec();

      if (ret == QMessageBox::Save)
        save_msc_file();
    }

    delete scene_;
  }

  filename_ = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("MSC Files (*.mpr);; All files (*)"));

  // Create and set a new scene
  scene_ = new Scene();
  config_.graphics_view->setScene(scene_);

  // Parse the file
  try
  {
    parse::Parser     p((pANTLR3_UINT8)filename_.toLocal8Bit().data());
    msc::Ast*         ast = p.parse(true);

    if (p.error_count_get() != 0)
    {
      parse::Parser   p2k((pANTLR3_UINT8)filename_.toLocal8Bit().data());
      ast = p2k.parse(false);

      if (p2k.error_count_get() != 0)
      {
        QMessageBox msgBox;

        msgBox.setText("Parse error.");
        msgBox.exec();

        return;
      }
    }

    view::Decorator decorator;
    msc::Ast* gmsc = decorator.recurse(*ast);
    scene_->root_set(gmsc);
    (*config_.graphics_view)(*gmsc);
  }
  catch (std::exception e)
  {
    QMessageBox msgBox;

    msgBox.setText(e.what());
    msgBox.exec();
  }
}

void Window::save_msc_file()
{
  if (filename_ == "")
  {
    save_msc_file_as();
    return;
  }

  std::ofstream o;
  o.open(filename_.toStdString().c_str());
  msc::PrettyPrinter printer(o);
  printer(*scene_->root_get());
  o.close();
}

void Window::save_msc_file_as()
{
  filename_ = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("MSC Files (*.mpr);; All files (*)"));

  if (filename_ != "")
    this->save_msc_file();
}

// Private methods
void Window::create_toolbox()
{
  view::gmsc::Instance* gmsc_instance = view::gmsc::Factory::instance().create_instance();
  view::gmsc::Message*  gmsc_message = view::gmsc::Factory::instance().create_message();
  QIcon                 icon(gmsc_instance->to_image());
  QIcon                 icon2(gmsc_message->to_image());
  QToolButton*          button;
  QGridLayout*          layout;
  QWidget*              widget;

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
  button->setIcon(icon2);
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
  QList<QAbstractButton *> buttons = buttonGroup_->buttons();

  scene_->set_type(view::gmsc::Factory::ItemType(id));

  if (id == view::gmsc::Factory::ITEM_TYPE_MESSAGE)
    scene_->set_mode(Scene::MODE_LINE_INSERTION);
  else
    scene_->set_mode(Scene::MODE_ITEM_INSERTION);

  if (buttonGroup_->checkedButton() == NULL)
    scene_->set_mode(Scene::MODE_SELECT);

  foreach (QAbstractButton *button, buttons)
  {
    if (button != buttonGroup_->checkedButton())
      button->setChecked(false);
  }
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
