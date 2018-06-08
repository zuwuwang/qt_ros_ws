#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include <QThread>
#include <QStringListModel>
#include "../include/guitest/socketsend_node.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

/*****************************************************************************
** Implementation
*****************************************************************************/

SocketSendNode::SocketSendNode(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
  {}

SocketSendNode::~SocketSendNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
  wait();
}

bool SocketSendNode::init() {
  ros::init(init_argc,init_argv,"guitest");
  if ( ! ros::master::check() ) {
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n;
  // Add your ros communications here. Socket Init Here, Connect Socket
  qDebug("start  init socket ...");
     //get server ip addr

  qDebug("ServerIPAddress %s\n",SERVER_IP_ADDRESS);
   log(Info,std::string("ServerIPAddress "));
  bzero(&client_addr,sizeof(client_addr)); //把一段内存区的内容全部设置为0
  client_addr.sin_family = AF_INET;    //internet协议族
  client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
  client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
  client_socket = socket(AF_INET,SOCK_STREAM,0);
  if( client_socket < 0)
         {
             qDebug("Create Socket Failed!\n");
               return false;
               exit(1);
         }
   /******
    * bind port
    * 把客户机的socket和客户机的socket地址结构联系起来,zhiding client_socket ip,point to addr
    * *******/
   if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
       {
           qDebug("Client Bind Port Failed!\n");
           exit(1);
       }
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
  server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

  socklen_t server_addr_length = sizeof(server_addr);
  /***
   * connect request,to server ip.success return 0;fail is 1
   * 向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
   * **/
   if(::connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
      {
          qDebug("Can Not Connect To %s!\n",SERVER_IP_ADDRESS);
          Q_EMIT socketSendFailed();
          exit(1);
      }
  qDebug("success connect To %s!\n",SERVER_IP_ADDRESS);

  start();  // thread function
  return true;
}

void SocketSendNode::run() {
  ros::NodeHandle n;
  ros::Rate loop(1); // HZ
  while(ros::ok())
  {
    // socket send
      // trogger mode
        Q_EMIT socketSend();  // trigger socket send
      // timer mode
        // img2send
    loop.sleep();
  }
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void SocketSendNode::log( const LogLevel &level, const std::string &msg) {
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
