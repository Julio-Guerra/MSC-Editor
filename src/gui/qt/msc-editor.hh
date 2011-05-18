/********************************************************************************
** Form generated from reading UI file 'msc-editor.ui'
**
** Created: Wed May 18 15:23:50 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MSC_2D_EDITOR_H
#define MSC_2D_EDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QWidget>
#include "view/qt/graph-view.hh"

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QAction *action_selection;
    QWidget *central_widget;
    QHBoxLayout *horizontalLayout;
    QToolBox *msc_toobox;
    QWidget *basic_msc_page;
    QWidget *gridLayoutWidget;
    QGridLayout *basic_msc_layout;
    QWidget *messages_page;
    view::GraphView *graphics_view;
    QMenuBar *menu;
    QMenu *file_menu;
    QMenu *edit_menu;
    QMenu *view_menu;
    QMenu *help_menu;
    QStatusBar *status_bar;
    QToolBar *tool_bar;

    void setupUi(QMainWindow *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QString::fromUtf8("Config"));
        Config->setWindowModality(Qt::NonModal);
        Config->resize(980, 765);
        Config->setDocumentMode(false);
        Config->setDockNestingEnabled(false);
        Config->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        Config->setUnifiedTitleAndToolBarOnMac(false);
        action_selection = new QAction(Config);
        action_selection->setObjectName(QString::fromUtf8("action_selection"));
        action_selection->setCheckable(true);
        central_widget = new QWidget(Config);
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        horizontalLayout = new QHBoxLayout(central_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        msc_toobox = new QToolBox(central_widget);
        msc_toobox->setObjectName(QString::fromUtf8("msc_toobox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(msc_toobox->sizePolicy().hasHeightForWidth());
        msc_toobox->setSizePolicy(sizePolicy);
        msc_toobox->setMinimumSize(QSize(200, 0));
        basic_msc_page = new QWidget();
        basic_msc_page->setObjectName(QString::fromUtf8("basic_msc_page"));
        basic_msc_page->setGeometry(QRect(0, 0, 200, 607));
        gridLayoutWidget = new QWidget(basic_msc_page);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 201, 601));
        basic_msc_layout = new QGridLayout(gridLayoutWidget);
        basic_msc_layout->setObjectName(QString::fromUtf8("basic_msc_layout"));
        basic_msc_layout->setContentsMargins(0, 0, 5, 0);
        msc_toobox->addItem(basic_msc_page, QString::fromUtf8("Basic MSC"));
        messages_page = new QWidget();
        messages_page->setObjectName(QString::fromUtf8("messages_page"));
        messages_page->setGeometry(QRect(0, 0, 200, 607));
        msc_toobox->addItem(messages_page, QString::fromUtf8("Messages"));

        horizontalLayout->addWidget(msc_toobox);

        graphics_view = new view::GraphView(central_widget);
        graphics_view->setObjectName(QString::fromUtf8("graphics_view"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphics_view->sizePolicy().hasHeightForWidth());
        graphics_view->setSizePolicy(sizePolicy1);
        graphics_view->setMaximumSize(QSize(16777215, 16777215));
        graphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphics_view->setSceneRect(QRectF(0, 0, 0, 0));

        horizontalLayout->addWidget(graphics_view);

        Config->setCentralWidget(central_widget);
        menu = new QMenuBar(Config);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setGeometry(QRect(0, 0, 980, 27));
        file_menu = new QMenu(menu);
        file_menu->setObjectName(QString::fromUtf8("file_menu"));
        edit_menu = new QMenu(menu);
        edit_menu->setObjectName(QString::fromUtf8("edit_menu"));
        view_menu = new QMenu(menu);
        view_menu->setObjectName(QString::fromUtf8("view_menu"));
        help_menu = new QMenu(menu);
        help_menu->setObjectName(QString::fromUtf8("help_menu"));
        Config->setMenuBar(menu);
        status_bar = new QStatusBar(Config);
        status_bar->setObjectName(QString::fromUtf8("status_bar"));
        Config->setStatusBar(status_bar);
        tool_bar = new QToolBar(Config);
        tool_bar->setObjectName(QString::fromUtf8("tool_bar"));
        Config->addToolBar(Qt::TopToolBarArea, tool_bar);

        menu->addAction(file_menu->menuAction());
        menu->addAction(edit_menu->menuAction());
        menu->addAction(view_menu->menuAction());
        menu->addAction(help_menu->menuAction());
        tool_bar->addAction(action_selection);

        retranslateUi(Config);

        msc_toobox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QMainWindow *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "MSC Editor", 0, QApplication::UnicodeUTF8));
        action_selection->setText(QApplication::translate("Config", "Selection", 0, QApplication::UnicodeUTF8));
        msc_toobox->setItemText(msc_toobox->indexOf(basic_msc_page), QApplication::translate("Config", "Basic MSC", 0, QApplication::UnicodeUTF8));
        msc_toobox->setItemText(msc_toobox->indexOf(messages_page), QApplication::translate("Config", "Messages", 0, QApplication::UnicodeUTF8));
        file_menu->setTitle(QApplication::translate("Config", "File", 0, QApplication::UnicodeUTF8));
        edit_menu->setTitle(QApplication::translate("Config", "Edit", 0, QApplication::UnicodeUTF8));
        view_menu->setTitle(QApplication::translate("Config", "View", 0, QApplication::UnicodeUTF8));
        help_menu->setTitle(QApplication::translate("Config", "Help", 0, QApplication::UnicodeUTF8));
        tool_bar->setWindowTitle(QApplication::translate("Config", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MSC_2D_EDITOR_H
