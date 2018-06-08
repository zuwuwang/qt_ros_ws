/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date june 2018
 *
 * @auth  wangZuWu
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/guitest/main_window.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    guitest::MainWindow w(argc,argv);  // shilihua mainwindow w & show
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
