/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QFrame *frame_2;
    QGroupBox *groupBox_display;
    QGridLayout *gridLayout_3;
    QListView *view_logging;
    QLabel *label_slammap;
    QLabel *label_cameraImg;
    QWidget *widget_webmap;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;
    QDockWidget *dock_status;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkbox_remember_settings;
    QLineEdit *line_edit_topic;
    QCheckBox *checkbox_use_environment;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *line_edit_master;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_roscore;
    QPushButton *button_openCam;
    QPushButton *button_connect;
    QLabel *label;
    QLineEdit *line_edit_host;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_onestep;
    QPushButton *button_saveMap;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *button_rviz;
    QPushButton *button_loadMap;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *button_speechListen;
    QPushButton *button_positionCal;
    QGroupBox *groupBox_3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *line_edit_mcnn;
    QPushButton *button_test;
    QPushButton *quit_button;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->setWindowModality(Qt::NonModal);
        MainWindowDesign->resize(1300, 691);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowDesign->sizePolicy().hasHeightForWidth());
        MainWindowDesign->setSizePolicy(sizePolicy);
        MainWindowDesign->setFocusPolicy(Qt::TabFocus);
        MainWindowDesign->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        MainWindowDesign->setAnimated(true);
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hboxLayout = new QHBoxLayout(centralwidget);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        groupBox_display = new QGroupBox(frame_2);
        groupBox_display->setObjectName(QString::fromUtf8("groupBox_display"));
        groupBox_display->setGeometry(QRect(0, 0, 971, 621));
        sizePolicy.setHeightForWidth(groupBox_display->sizePolicy().hasHeightForWidth());
        groupBox_display->setSizePolicy(sizePolicy);
        groupBox_display->setMinimumSize(QSize(0, 0));
        groupBox_display->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_display);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        view_logging = new QListView(groupBox_display);
        view_logging->setObjectName(QString::fromUtf8("view_logging"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(view_logging->sizePolicy().hasHeightForWidth());
        view_logging->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(view_logging, 0, 2, 1, 1);

        label_slammap = new QLabel(groupBox_display);
        label_slammap->setObjectName(QString::fromUtf8("label_slammap"));
        label_slammap->setMinimumSize(QSize(450, 300));

        gridLayout_3->addWidget(label_slammap, 1, 1, 1, 1);

        label_cameraImg = new QLabel(groupBox_display);
        label_cameraImg->setObjectName(QString::fromUtf8("label_cameraImg"));
        sizePolicy.setHeightForWidth(label_cameraImg->sizePolicy().hasHeightForWidth());
        label_cameraImg->setSizePolicy(sizePolicy);
        label_cameraImg->setMinimumSize(QSize(450, 300));

        gridLayout_3->addWidget(label_cameraImg, 0, 1, 1, 1);

        widget_webmap = new QWidget(groupBox_display);
        widget_webmap->setObjectName(QString::fromUtf8("widget_webmap"));

        gridLayout_3->addWidget(widget_webmap, 1, 2, 1, 1);


        hboxLayout->addWidget(frame_2);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1300, 20));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        dock_status = new QDockWidget(MainWindowDesign);
        dock_status->setObjectName(QString::fromUtf8("dock_status"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dock_status->sizePolicy().hasHeightForWidth());
        dock_status->setSizePolicy(sizePolicy2);
        dock_status->setMinimumSize(QSize(300, 617));
        dock_status->setMaximumSize(QSize(300, 649));
        dock_status->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QString::fromUtf8("checkbox_remember_settings"));
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 7, 0, 1, 2);

        line_edit_topic = new QLineEdit(groupBox);
        line_edit_topic->setObjectName(QString::fromUtf8("line_edit_topic"));
        line_edit_topic->setEnabled(false);

        gridLayout->addWidget(line_edit_topic, 5, 0, 1, 2);

        checkbox_use_environment = new QCheckBox(groupBox);
        checkbox_use_environment->setObjectName(QString::fromUtf8("checkbox_use_environment"));
        checkbox_use_environment->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_use_environment, 6, 0, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 23));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(1000000, 23));
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        line_edit_master = new QLineEdit(groupBox);
        line_edit_master->setObjectName(QString::fromUtf8("line_edit_master"));

        gridLayout->addWidget(line_edit_master, 1, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        button_roscore = new QPushButton(groupBox);
        button_roscore->setObjectName(QString::fromUtf8("button_roscore"));
        sizePolicy.setHeightForWidth(button_roscore->sizePolicy().hasHeightForWidth());
        button_roscore->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(button_roscore);

        button_openCam = new QPushButton(groupBox);
        button_openCam->setObjectName(QString::fromUtf8("button_openCam"));

        horizontalLayout_5->addWidget(button_openCam);

        button_connect = new QPushButton(groupBox);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));
        button_connect->setEnabled(true);
        sizePolicy.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(button_connect);


        gridLayout->addLayout(horizontalLayout_5, 9, 0, 1, 2);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 23));
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        line_edit_host = new QLineEdit(groupBox);
        line_edit_host->setObjectName(QString::fromUtf8("line_edit_host"));

        gridLayout->addWidget(line_edit_host, 3, 0, 1, 2);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(287, 80));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 20, 189, 58));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        button_onestep = new QPushButton(layoutWidget);
        button_onestep->setObjectName(QString::fromUtf8("button_onestep"));

        horizontalLayout->addWidget(button_onestep);

        button_saveMap = new QPushButton(layoutWidget);
        button_saveMap->setObjectName(QString::fromUtf8("button_saveMap"));

        horizontalLayout->addWidget(button_saveMap);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        button_rviz = new QPushButton(layoutWidget);
        button_rviz->setObjectName(QString::fromUtf8("button_rviz"));

        horizontalLayout_2->addWidget(button_rviz);

        button_loadMap = new QPushButton(layoutWidget);
        button_loadMap->setObjectName(QString::fromUtf8("button_loadMap"));

        horizontalLayout_2->addWidget(button_loadMap);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(287, 60));
        horizontalLayoutWidget_4 = new QWidget(groupBox_4);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(60, 20, 181, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        button_speechListen = new QPushButton(horizontalLayoutWidget_4);
        button_speechListen->setObjectName(QString::fromUtf8("button_speechListen"));

        horizontalLayout_4->addWidget(button_speechListen);

        button_positionCal = new QPushButton(horizontalLayoutWidget_4);
        button_positionCal->setObjectName(QString::fromUtf8("button_positionCal"));

        horizontalLayout_4->addWidget(button_positionCal);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(100287, 50));
        horizontalLayoutWidget_3 = new QWidget(groupBox_3);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 20, 261, 25));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        line_edit_mcnn = new QLineEdit(horizontalLayoutWidget_3);
        line_edit_mcnn->setObjectName(QString::fromUtf8("line_edit_mcnn"));

        horizontalLayout_3->addWidget(line_edit_mcnn);


        verticalLayout_3->addWidget(groupBox_3);

        button_test = new QPushButton(frame);
        button_test->setObjectName(QString::fromUtf8("button_test"));

        verticalLayout_3->addWidget(button_test);


        verticalLayout->addWidget(frame);

        quit_button = new QPushButton(dockWidgetContents_2);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(quit_button);

        dock_status->setWidget(dockWidgetContents_2);
        MainWindowDesign->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_status);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));
        QObject::connect(quit_button, SIGNAL(clicked()), MainWindowDesign, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "TravelAssistanceRobot", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", 0, QApplication::UnicodeUTF8));
        groupBox_display->setTitle(QApplication::translate("MainWindowDesign", "                                                                                                    display area", 0, QApplication::UnicodeUTF8));
        label_slammap->setText(QApplication::translate("MainWindowDesign", "slamMap", 0, QApplication::UnicodeUTF8));
        label_cameraImg->setText(QApplication::translate("MainWindowDesign", "cameraImg", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", 0, QApplication::UnicodeUTF8));
        dock_status->setWindowTitle(QApplication::translate("MainWindowDesign", "Command Panel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindowDesign", "Ros Master", 0, QApplication::UnicodeUTF8));
        checkbox_remember_settings->setText(QApplication::translate("MainWindowDesign", "Remember settings on startup", 0, QApplication::UnicodeUTF8));
        line_edit_topic->setText(QApplication::translate("MainWindowDesign", "unused", 0, QApplication::UnicodeUTF8));
        checkbox_use_environment->setText(QApplication::translate("MainWindowDesign", "Use environment variables", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowDesign", "Ros Hostname", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowDesign", "Ros IP", 0, QApplication::UnicodeUTF8));
        line_edit_master->setText(QApplication::translate("MainWindowDesign", "http://192.168.1.2:11311/", 0, QApplication::UnicodeUTF8));
        button_roscore->setText(QApplication::translate("MainWindowDesign", "roscore", 0, QApplication::UnicodeUTF8));
        button_openCam->setText(QApplication::translate("MainWindowDesign", "openCam", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        button_connect->setToolTip(QApplication::translate("MainWindowDesign", "Set the target to the current joint trajectory state.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        button_connect->setStatusTip(QApplication::translate("MainWindowDesign", "Clear all waypoints and set the target to the current joint trajectory state.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        button_connect->setText(QApplication::translate("MainWindowDesign", "connect", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowDesign", "Ros Master Url", 0, QApplication::UnicodeUTF8));
        line_edit_host->setText(QApplication::translate("MainWindowDesign", "192.168.1.67", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindowDesign", "Run Laser SLAM", 0, QApplication::UnicodeUTF8));
        button_onestep->setText(QApplication::translate("MainWindowDesign", "onestepSLAM", 0, QApplication::UnicodeUTF8));
        button_saveMap->setText(QApplication::translate("MainWindowDesign", "saveMap", 0, QApplication::UnicodeUTF8));
        button_rviz->setText(QApplication::translate("MainWindowDesign", "rviz", 0, QApplication::UnicodeUTF8));
        button_loadMap->setText(QApplication::translate("MainWindowDesign", "loadMap", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindowDesign", "SpeechAssistance", 0, QApplication::UnicodeUTF8));
        button_speechListen->setText(QApplication::translate("MainWindowDesign", "speechListen", 0, QApplication::UnicodeUTF8));
        button_positionCal->setText(QApplication::translate("MainWindowDesign", "positionCal", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindowDesign", "Get Resault", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowDesign", "peopleNumber:", 0, QApplication::UnicodeUTF8));
        button_test->setText(QApplication::translate("MainWindowDesign", "buttton_test", 0, QApplication::UnicodeUTF8));
        quit_button->setText(QApplication::translate("MainWindowDesign", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
