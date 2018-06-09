/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date june 2018
 *
 * @auth  wangZuWu
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/guitest/main_window.hpp"

#include <QWebView>
#include <QUrl>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
  , qnode(argc,argv)  //TODO HERE,ADD YOUR NODE INIT WITH PARAM
  , imagesavenode(argc,argv)
  , socketsendnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application
    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    QObject::connect(&imagesavenode,SIGNAL(rosShutdown()),this,SLOT(close()));
    QObject::connect(&socketsendnode,SIGNAL(rosShutdown()),this,SLOT(close()));

  /*********************
  ** Logging & Camera image display
	**********************/
	ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
  /*********************
  ** TODO HERE,ADD YOUR trigger FUNC
  **********************/
  // init

  // display in ui
    QObject::connect(&imagesavenode,SIGNAL(displayCameraImage()),this,SLOT(displayCameraImageLabel()));

    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
    /*******
     *  load webmap & get slam map & load map
     *************/
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
  msgBox.setText("Couldn't find the ros master,please run commond 'roscor'.");
	msgBox.exec();
    close();
}

void MainWindow::showSocketInitFailedMessage()
{
  QMessageBox msgBox;
  msgBox.setText(" Connect server failed, please try again.");
  msgBox.exec();
    close();
}
/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check )
{
  /*******************
   *   init
   * *********************/
  //  environment init
  if ( ui.checkbox_use_environment->isChecked() )
  {
    if ( !qnode.init() )
    {
      showNoMasterMessage();
    }
    else
    {
      ui.button_connect->setEnabled(false);
    }
  }
  // qnode init
  if ( ! qnode.init(ui.line_edit_master->text().toStdString(),ui.line_edit_host->text().toStdString()) )
  {
    showSocketInitFailedMessage();
  }
  else
  {
    ui.button_connect->setEnabled(false);
    ui.line_edit_master->setReadOnly(true);
    ui.line_edit_host->setReadOnly(true);
    ui.line_edit_topic->setReadOnly(true);
  }
  // imagesavenode init
  if( ! imagesavenode.init() )
  {
    showNoMasterMessage();
  }
  else
  {

  }
 // socketsendnode init
  if( ! socketsendnode.init() )
  {
       showSocketInitFailedMessage();
  }
  else
  {

  }
  // node to init


  /*********************
   * node.start
   * ********************/
  qnode.start();
  imagesavenode.start();
  socketsendnode.start();
 // speech node

 // calPosition node

 // load webmap
  {
//    QWebView webmap;
//   // webmap.load(QUrl("http://www.baidu.com"));
//    webmap.load(QUrl::fromLocalFile("file:///home/nvidia/qt_ros_ws/test.html"));
//    webmap.show();
  }
}

void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
		enabled = true;
	} else {
		enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
	//ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
void MainWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}

void MainWindow::displayCameraImageLabel(){
  //TODO
  // display image in widget
         //ui.label_cameraImg->
  struct tm* fileTime;
  char filePath[100] = {0};
  char fileName[100] = {0};
  time_t t;
  t = time(NULL);
  fileTime = localtime(&t);
  strftime(filePath,100,"/home/nvidia/qt_ros_ws/image2/%Y%m%d_%H%M%S.jpg",fileTime);
  strftime(fileName,100,"%Y%m%d_%H%M%S.jpg",fileTime);

  cv::Mat img2display = imagesavenode.cameraImage;
  cv::imwrite(filePath,img2display);


  cv::cvtColor(img2display,img2display,CV_BGR2RGB);
  QImage idsImage(img2display.data,img2display.cols,img2display.rows,img2display.cols*img2display.channels(),QImage::Format_RGB888);
  QImage cameraImageScaled;
  cameraImageScaled = idsImage.scaled(ui.label_cameraImg->size(),Qt::KeepAspectRatio);
  ui.label_cameraImg->setPixmap(QPixmap::fromImage(cameraImageScaled));
}

void MainWindow::mcnnResaultShow(){
  long num =atof(socketsendnode.peopleNum);
  QString mcnnNum = QString::number( num,10);
  ui.line_edit_mcnn->setText(mcnnNum);
}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "guitest");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    	//ui.line_edit_topic->setEnabled(false);
    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "guitest");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
}

void MainWindow::closeEvent(QCloseEvent *event){
	WriteSettings();
  // TODO
  // add your destory function
	QMainWindow::closeEvent(event);
}




/*****************************************************************************
** Implementation [ Add Your Button Response Here ]
*****************************************************************************/

void MainWindow::on_button_onestepSLAM_clicked(bool checked){
  // all in one launch file
  //system("gnome-terminal -x bash -c 'source /home/ubuntu/turtlebot/devel/setup.bash;roslaunch turtlebot_bringup minimal.launch limited:=true'&");
    system("gnome-terminal  -x bash -c ' roslaunch usb_cam usb_cam-test.launch '");
}

void MainWindow::on_button_roscore_clicked(bool checked)
{
//  system("gnome-terminal -x bash -c 'source /home/nvidia/qt_ros_ws/devel/setup.bash;roscore limited:=true'&"); // this is run on TX2
//  system("gnome-terminal  -x bash -c ' roscore '");  // this cmd is run on asus 14.04
//  QWebView webmap;
//  webmap.load(QUrl("http://www.baidu.com"));
//  webmap.load(QUrl::fromLocalFile("file:///home/nvidia/qt_ros_ws/test.html"));
//  webmap.show();
  system("gnome-terminal  -x bash -c ' roscore '");
}

void MainWindow::on_button_openCam_clicked(bool checked){
  system("gnome-terminal  -x bash -c ' roslaunch usb_cam usb_cam-test.launch '");
}

}  // namespace guitest


