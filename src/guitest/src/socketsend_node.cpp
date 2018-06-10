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
 // image_transport::ImageTransport transport_socket(n);
 // socketSend_subscriber = transport_socket.subscribe("/usb_cam/image_raw",1,&SocketSendNode::socketSendImage,this); // TX2 different

  qDebug("start  init socket ...");
     //get server ip addr
  qDebug("ServerIPAddress %s\n",SERVER_IP_ADDRESS);
  bzero(&client_addr,sizeof(client_addr)); //把一段内存区的内容全部设置为0
  client_addr.sin_family = AF_INET;    //internet协议族
  client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
  client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
  client_socket = socket(AF_INET,SOCK_STREAM,0);
  if( client_socket < 0)
         {
             qDebug("Create Socket Failed!\n");
             return false;
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
          return false;
      }
  qDebug("success connect To %s!\n",SERVER_IP_ADDRESS);

  //start();  // thread function
  return true;
}

void SocketSendNode::run() {
  ros::NodeHandle n;
  ros::Rate loop_rate(0.2);
  while( ros::ok() )
  {
    // ros img to opencv img
    image_transport::ImageTransport transport_socket(n);
    socketSend_subscriber = transport_socket.subscribe("/usb_cam/image_raw",1,&SocketSendNode::socketSendImage,this); // TX2 different
    socketSendFlag = true;
    ros::spinOnce();
    loop_rate.sleep();
  }
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void SocketSendNode::socketSendImage(const sensor_msgs::ImageConstPtr &msg){
  if(socketSendFlag)
    {
      try
      {
          // set imgSaveFlag
          socketSendFlag = false;
          ROS_INFO("F");
          //get img & show,transfer ros img to cv img
          socket2Send = cv_bridge::toCvShare(msg, "bgr8")->image;
          struct tm* fileTime;
          char filePath[100] ;
          char fileName[20] ;
          time_t t;
          t = time(NULL);
          fileTime = localtime(&t);
         // strftime(filePath,100,"/home/nvidia/qt_ros_ws/imag3/%Y%m%d_%H%M%S.jpg",fileTime);
         // strftime(fileName,100,"%Y%m%d_%H%M%S.jpg",fileTime);
          strftime(filePath,100,"/home/nvidia/qt_ros_ws/image3/%Y%m%d_%H%M%S.jpg",fileTime);
          strftime(fileName,20,"%Y%m%d_%H%M%S.jpg",fileTime);
         // cv::imwrite(filePath,socket2Send);

          // TODO, socket send
          // local img test
         // cv::Mat test = cv::imread("/home/nvidia/qt_ros_ws/devel/lib/guitest/1.jpg");
          vector<uchar> socket2SendEncode;
          cv::imencode(".jpg",socket2Send,socket2SendEncode);
          cv::Mat decode;
          decode = cv::imdecode(socket2SendEncode,CV_LOAD_IMAGE_COLOR);
          cv::imwrite(filePath,decode);

          int socket2SendSize = 3*socket2Send.rows*socket2Send.cols;
          int socket2SendEncodeSize = socket2SendEncode.size();
          uchar* socketSendBuffer = new uchar[socket2SendEncodeSize];
          copy(socket2SendEncode.begin(),socket2SendEncode.end(),socketSendBuffer);

          // send $$
          // send(client_socket, "$$", 2, 0);
          int toSend = socket2SendEncodeSize, received = 0, finished = 0;
          char char_len[10]; // fileLen[10],save file size
          // send fineName
          send(client_socket,fileName,20,0);
          // send fileSize
          sprintf(char_len,"%d",toSend);
          send(client_socket, char_len, 10, 0);
          while( toSend >0 )
          {
            int realSendSize =qMin(toSend, 1000);
            received = send(client_socket, socketSendBuffer + finished, realSendSize, 0);
            toSend -= received;
            finished += finished;
          }
//        // receive resault
//        recv(client_socket, peopleNum, 10, 0);
//        // ui display mcnnResault
          Q_EMIT mcnnResault();
       }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
      }
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
