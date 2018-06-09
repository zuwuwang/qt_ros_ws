/**
 * @file /include/guitest/socketsendnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2018
 *
 * @autho  wangZuWu
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/
#ifndef guitest_SOCKETSENDNODE_HPP_
#define guitest_SOCKETSENDNODE_HPP_

#define HELLO_WORLD_SERVER_PORT  37677
#define SERVER_IP_ADDRESS "112.74.89.58"  // 地面工作站IP
#define BUFFER_SIZE 1024


/*****************************************************************************
** Includes
*****************************************************************************/
// from qnode
#include <ros/ros.h>
#include <QThread>
#include <QStringListModel>
#include <image_transport/image_transport.h>

//socket headfile
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for qDebug
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <time.h>                //for time_t and time
#include <arpa/inet.h>
#include <unistd.h>    //close(client_socket);

//opencv headfile
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

// qt include
#include <QDebug>

/*****************************************************************************
** Namespaces
*****************************************************************************/
using namespace std;
using namespace cv;

namespace guitest {

/*****************************************************************************
** Class
*****************************************************************************/
class SocketSendNode : public QThread {
    Q_OBJECT
public:
  SocketSendNode(int argc, char** argv );
  virtual ~SocketSendNode();
  bool init();
  void run();
  void socketSendImage(const sensor_msgs::ImageConstPtr& msg);
  bool socketSendFlag = true;
  cv::Mat socket2Send;
  char peopleNum[11] = {0};
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
  void socketSend();
    void socketSendFailed();
    void mcnnResault();

private:
  int init_argc;
  char** init_argv;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  int client_socket;
  char buffer[BUFFER_SIZE];
  int length;
  vector<uchar> encode_img;
  image_transport::Subscriber socketSend_subscriber;
    QStringListModel logging_model;
};


} // namespace guitest
#endif // guitest_SOCKETSENDNODE_HPP_
