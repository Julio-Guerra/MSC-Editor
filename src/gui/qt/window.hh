#ifndef WINDOW_HH_
# define	WINDOW_HH_

# include <QtGui/QGraphicsScene>
# include <QtGui/QToolButton>
# include <QtGui/QMessageBox>
# include <QtGui/QFileDialog>

# include "view/qt/gmsc/factory.hh"
# include "gui/qt/msc-editor.hh"
# include "gui/qt/scene.hh"

namespace gui
{
  class Window : public QMainWindow
  {
      Q_OBJECT

    public:
      Window ();

    private slots:
      void buttonGroupClicked(int id);
      void itemInserted(QGraphicsPolygonItem* item);
      void open_msc_file();
      void save_msc_file();
      void save_msc_file_as();

    private:
      Ui::Config      config_;
      Scene*          scene_;
      QButtonGroup*   buttonGroup_;
      QString         filename_;

      void create_toolbox();
  };
}

#endif	/* !WINDOW_HH_ */

