/********************************************************************************
** Form generated from reading UI file 'msc-editor.ui'
**
** Created: Mon May 30 21:51:55 2011
**      by: Qt User Interface Compiler version 4.7.2
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "view/qt/graph-view.hh"

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QAction *action_selection;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QWidget *central_widget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *msc_toolbox;
    QWidget *gridLayoutWidget;
    QGridLayout *basic_msc_layout;
    view::GraphView *graphics_view;
    QMenuBar *menu;
    QMenu *file_menu;
    QStatusBar *status_bar;

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
        actionOpen = new QAction(Config);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(Config);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(Config);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        central_widget = new QWidget(Config);
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        horizontalLayout = new QHBoxLayout(central_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        msc_toolbox = new QGroupBox(central_widget);
        msc_toolbox->setObjectName(QString::fromUtf8("msc_toolbox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(msc_toolbox->sizePolicy().hasHeightForWidth());
        msc_toolbox->setSizePolicy(sizePolicy);
        msc_toolbox->setMinimumSize(QSize(175, 0));
        gridLayoutWidget = new QWidget(msc_toolbox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 20, 171, 181));
        basic_msc_layout = new QGridLayout(gridLayoutWidget);
        basic_msc_layout->setObjectName(QString::fromUtf8("basic_msc_layout"));
        basic_msc_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        basic_msc_layout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(msc_toolbox);

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
        menu->setGeometry(QRect(0, 0, 980, 25));
        file_menu = new QMenu(menu);
        file_menu->setObjectName(QString::fromUtf8("file_menu"));
        Config->setMenuBar(menu);
        status_bar = new QStatusBar(Config);
        status_bar->setObjectName(QString::fromUtf8("status_bar"));
        Config->setStatusBar(status_bar);

        menu->addAction(file_menu->menuAction());
        file_menu->addAction(actionOpen);
        file_menu->addAction(actionSave);
        file_menu->addAction(actionSave_as);

        retranslateUi(Config);

        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QMainWindow *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "MSC Editor", 0, QApplication::UnicodeUTF8));
        action_selection->setText(QApplication::translate("Config", "Selection", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("Config", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("Config", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("Config", "Save as", 0, QApplication::UnicodeUTF8));
        msc_toolbox->setTitle(QApplication::translate("Config", "Elements", 0, QApplication::UnicodeUTF8));
        file_menu->setTitle(QApplication::translate("Config", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MSC_2D_EDITOR_H
