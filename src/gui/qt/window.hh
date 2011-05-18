#ifndef WINDOW_HH_
# define	WINDOW_HH_

#include <QtGui/QGraphicsScene>
#include <QtGui/QToolButton>

# include "gui/qt/msc-editor.hh"

namespace gui
{
  class Window : public QMainWindow
  {
    public:
      Window ();
      
      void open_msc_file();
      void save_msc_file();

    private:
      Ui::Config      config_;
      QGraphicsScene* scene_;
      
      void create_toolbox();
  };
}

#endif	/* !WINDOW_HH_ */

