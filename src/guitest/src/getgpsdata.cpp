/**
 * @file /include/guitest/getgpsdata.cpp
 *
 * @brief Communications central!
 *
 * @date june 2018
 *
 * @auth  wangZuWu
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sstream>

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>   /* 文件控制定义*/
#include <termios.h> /* PPSIX 终端控制定义*/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "../include/guitest/getgpsdata.hpp"

#define GPS_LEN 1024

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

/*****************************************************************************
** Implementation
*****************************************************************************/
GetGpsData::GetGpsData(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
  {}

GetGpsData::~GetGpsData() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
  wait();
}

bool GetGpsData::init() {
  ros::init(init_argc,init_argv,"guitest");
  if ( ! ros::master::check() ) {
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n;
  // Add your ros communications here.
  ros::Publisher pubGpsData = nh.advertise<std_msgs::String>("gpsInfo",1000);
  ROS_INFO(" gps model init !");
  //if((fd=open(dev_name,O_RDWR|O_NOCTTY|O_NDELAY))<0)
  if((fd=open(dev_name,O_RDWR))<0)
  {
          perror("Can't Open the ttyUSB0 Serial Port");
          return -1;
  }
  set_serial( fd,9600,8,'N',1);
  start();
  return true;
}

void GetGpsData::run() {
  ros::Rate loop_rate(1);
  while(1)
    {
       sleep(2);
       if((n=read(fd,buff,sizeof(buff)))<0)
        {
           perror("read error");
           return -1;
        }
        printf("buff:%s\n",buff);
        memset(&gprmc, 0 , sizeof(gprmc));
       // gps_analyse(buff,&gprmc);
       // print_gps(&gprmc);

        while(ros::ok())
        {
           std_msgs::String msg;
           std::stringstream ss;
           ss<<gprmc.latitude<<"$$"<<gprmc.longitude;
           msg.data = ss.str();
           ROS_INFO("gps data is %s",msg.data.c_str());
           pubGpsData.publish(msg);
           ros::spinOnce();
           loop_rate.sleep();
        }

    }

      close(fd);
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void GetGpsData::log( const LogLevel &level, const std::string &msg) {
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


}// namespace guitest
