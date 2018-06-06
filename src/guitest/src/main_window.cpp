/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/guitest/main_window.hpp"

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
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    QObject::connect(&imagesavenode,SIGNAL(rosShutdown()),this,SLOT(close()));
	/*********************
  ** Logging & Camera image display
	**********************/
	ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

  //TODO HERE,ADD YOUR FUNC
    QObject::connect(&imagesavenode,SIGNAL(saveCameraImage()),this,SLOT(displayCameraImageLabel()));


    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
    /*******
     *  get slam map & load map
     *************/

}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check )
{
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
  else
  {
    // qnode init function to start
		if ( ! qnode.init(ui.line_edit_master->text().toStdString(),ui.line_edit_host->text().toStdString()) )
    {
			showNoMasterMessage();
    }
    else
    {
			ui.button_connect->setEnabled(false);
			ui.line_edit_master->setReadOnly(true);
			ui.line_edit_host->setReadOnly(true);
			ui.line_edit_topic->setReadOnly(true);
		}

    //TODO,RUN YOUR NODE
    if( ! imagesavenode.init() )
    {
      showNoMasterMessage();
    }
    else
    {
      // TODO here,display in label
      //displayCameraImageLabel();
      ROS_INFO(" run imageSaveNode ");
    }

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
  //ui.label_cameraImg->clear();
  //ui.label_cameraImg->setPixmap(QPixmap::fromImage(idsImage));
  //ui.label_cameraImg->resize(ui.label_cameraImg->pixmap()->size());
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
  //cv::destroyWindow("show source wimage");
	QMainWindow::closeEvent(event);
}

void MainWindow::showButtonTestMessage(){
  QMessageBox msgBox;
  msgBox.setText("button test ...");
  msgBox.exec();
}

void MainWindow::on_button_test_clicked(bool checkrd){
  showButtonTestMessage();

}

void MainWindow::on_button_onestepSLAM_clicked(bool check){
  // all in one launch file
  //system("gnome-terminal -x bash -c 'source /home/ubuntu/turtlebot/devel/setup.bash;roslaunch turtlebot_bringup minimal.launch limited:=true'&");
}

}  // namespace guitest
