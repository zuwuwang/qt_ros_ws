
#ifndef guitest_GETGPSDATA_NODE_HPP_
#define guitest_GETGPSDATA_NODE_HPP_


#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>

#include "std_msgs/String.h"
#include <sstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>   /* 文件控制定义*/
#include <termios.h> /* PPSIX 终端控制定义*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "gps.h"

#define GPS_LEN 1024
/*****************************************************************************
** Namespaces
*****************************************************************************/
using namespace std;
namespace guitest {

/*****************************************************************************
** Class
*****************************************************************************/

class GetGpsDataNode : public QThread {
    Q_OBJECT
public:
  GetGpsDataNode(int argc, char** argv );
  virtual ~GetGpsDataNode();
  bool init();
  void run();
  /********************
   * GpsData
   * ******************/
  int set_serial(int fd,int nSpeed, int nBits, char nEvent, int nStop);
  int gps_analyse(char *buff,GPRMC *gps_data);
  int print_gps(GPRMC *gps_data);
  /*********************
  ** Logging
  **********************/
  enum LogLevel {
           Debug,
           Info,
           Warn,
           Error,
           Fatal
   };

  QStringListModel* loggingModel() { return &logging_model; }
  void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
  void loggingUpdated();
    void rosShutdown();

private:
  int init_argc;
  char** init_argv;
  int fd=0;
  int readLabel=0;
  int i;
  GPRMC gprmc;
  char buff[GPS_LEN];
  char *dev_name="/dev/ttyUSB0";
    ros::Publisher gps_publisher;
    QStringListModel logging_model;
};

}  // namespace guitest

#endif // guitest_GETGPSDATA_NODE_HPP_
