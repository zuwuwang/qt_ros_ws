/**
 * @file /src/ImageSaveNode.cpp
 *
 * @brief Ros communication central!
 *
 * @date june 2018
 *
 * @auth  wangZuWu
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <std_msgs/String.h>

#include <sstream>
#include "../include/guitest/imagesave_node.hpp"



#include <iostream>
#include <sys/time.h>
#include <stdio.h>        // for qDebug
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <time.h>          //for time_t and time



/*****************************************************************************
** Namespaces
*****************************************************************************/

using namespace cv;
namespace guitest {

/*****************************************************************************
** Implementation
*****************************************************************************/

ImageSaveNode::ImageSaveNode(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
  {}

ImageSaveNode::~ImageSaveNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
  wait();
}

bool ImageSaveNode::init() {
  ros::init(init_argc,init_argv,"guitest");
  if ( ! ros::master::check() ) {
    return false;
  }
  // CHECK CAMERA NODE
  // TODO

  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n;
  cv::startWindowThread();
  // Add your ros communications here.
  image_transport::ImageTransport transport(n);
  cameraImage_subscriber = transport.subscribe("/usb_cam/image_raw",1,&ImageSaveNode::imageTransCallback,this);
  start(); // Match with run() function
  return true;
}


void ImageSaveNode::run() {
  ros::NodeHandle n;
  //ros timer
  ros::Timer captureTimer = n.createTimer(ros::Duration(5),&ImageSaveNode::captureTimerCallback,this);
  // ros img to opencv img
  image_transport::ImageTransport transport(n);
  cameraImage_subscriber = transport.subscribe("/usb_cam/image_raw",1,&ImageSaveNode::imageTransCallback,this); // TX2 different
  saveImageFlag = true;
  ros::spin();

  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void ImageSaveNode::captureTimerCallback(const ros::TimerEvent& e){
  saveImageFlag = true;
}

void ImageSaveNode::imageTransCallback(const sensor_msgs::ImageConstPtr& msg){
  if(saveImageFlag)
    {
      try
      {
          // set imgSaveFlag
          saveImageFlag = false;
          ROS_INFO("F");
          //get img & show,transfer ros img to cv img
          cameraImage = cv_bridge::toCvShare(msg, "bgr8")->image;
          struct tm* fileTime;
          char filePath[100] = {0};
          char fileName[100] = {0};
          time_t t;
          t = time(NULL);
          fileTime = localtime(&t);
         // strftime(filePath,100,"/home/nvidia/qt_ros_ws/image/%Y%m%d_%H%M%S.jpg",fileTime);
         // strftime(fileName,100,"%Y%m%d_%H%M%S.jpg",fileTime);
          strftime(filePath,100,"/home/nvidia/qt_ros_ws/image/%H%M%S.jpg",fileTime);
          strftime(fileName,100,"%H%M%S.jpg",fileTime);

          cv::imwrite(filePath,cameraImage);
          Q_EMIT displayCameraImage();  // trigger signal , to run slot func: display in qt label
       }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
        //TODO ,socket send picture
      }

}

void ImageSaveNode::log( const LogLevel &level, const std::string &msg) {
  logging_model.insertRows(logging_model.rowCount(),1);
  std::stringstream logging_model_msg;
  switch ( level ) {
    case(Debug) : {
        ROS_DEBUG_STREAM(msg);
        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Info) : {
        ROS_INFO_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Warn) : {
        ROS_WARN_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Error) : {
        ROS_ERROR_STREAM(msg);
        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Fatal) : {
        ROS_FATAL_STREAM(msg);
        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
        break;
    }
  }
  QVariant new_row(QString(logging_model_msg.str().c_str()));
  logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
  Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}



}  // namespace guitest
