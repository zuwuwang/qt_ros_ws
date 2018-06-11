/**
 * @file /src/GetGpsDataNode.cpp
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
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/guitest/getgpsdata_node.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

/*****************************************************************************
** Implementation
*****************************************************************************/

GetGpsDataNode::GetGpsDataNode(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
  {}

GetGpsDataNode::~GetGpsDataNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
  wait();
}

bool GetGpsDataNode::init() {
  ros::init(init_argc,init_argv,"guitest");
  if ( ! ros::master::check() ) {
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n;
  // Add your ros communications here.

  start();
  return true;
}

void GetGpsDataNode::run() {
  ros::NodeHandle n;
  ros::Publisher gps_publisher = n.advertise<std_msgs::String>("gpsInfo",1000);
  ros::Rate loop_rate(10);

  while(1)
      {
         sleep(2);
         if((readLabel = read(fd,buff,sizeof(buff)))<0)
          {
             perror("read error");
             // showErrorMsgs();
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
             gps_publisher.publish(msg);
             ros::spinOnce();
             loop_rate.sleep();
          }
      }
      close(fd);

  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

int GetGpsDataNode::set_serial(int fd, int nSpeed, int nBits, char nEvent, int nStop){
  struct termios newttys1,oldttys1;

      /*保存原有串口配置*/
      if(tcgetattr(fd,&oldttys1)!=0)
      {
           perror("Setupserial 1");
           return -1;
           // rosShutdown();
      }
      memset(&newttys1,0,sizeof(newttys1));/* 先将新串口配置清0 */
      newttys1.c_cflag|=(CLOCAL|CREAD ); /* CREAD 开启串行数据接收，CLOCAL并打开本地连接模式 */

      newttys1.c_cflag &=~CSIZE;/* 设置数据位 */
      /* 数据位选择 */
      switch(nBits)
      {
          case 7:
              newttys1.c_cflag |=CS7;
              break;
          case 8:
              newttys1.c_cflag |=CS8;
              break;
      }
      /* 设置奇偶校验位 */
      switch( nEvent )
      {
          case '0':  /* 奇校验 */
              newttys1.c_cflag |= PARENB;/* 开启奇偶校验 */
              newttys1.c_iflag |= (INPCK | ISTRIP);/*INPCK打开输入奇偶校验；ISTRIP去除字符的第八个比特  */
              newttys1.c_cflag |= PARODD;/*启用奇校验(默认为偶校验)*/
              break;
          case 'E':/*偶校验*/
              newttys1.c_cflag |= PARENB; /*开启奇偶校验  */
              newttys1.c_iflag |= ( INPCK | ISTRIP);/*打开输入奇偶校验并去除字符第八个比特*/
              newttys1.c_cflag &= ~PARODD;/*启用偶校验*/
              break;
          case 'N': /*无奇偶校验*/
              newttys1.c_cflag &= ~PARENB;
              break;
      }
      /* 设置波特率 */
     switch( nSpeed )
     {
         case 2400:
             cfsetispeed(&newttys1, B2400);
             cfsetospeed(&newttys1, B2400);
             break;
         case 4800:
             cfsetispeed(&newttys1, B4800);
             cfsetospeed(&newttys1, B4800);
             break;
         case 9600:
             cfsetispeed(&newttys1, B9600);
             cfsetospeed(&newttys1, B9600);
             break;
         case 115200:
             cfsetispeed(&newttys1, B115200);
             cfsetospeed(&newttys1, B115200);
             break;
         default:
             cfsetispeed(&newttys1, B9600);
             cfsetospeed(&newttys1, B9600);
             break;
     }
      /*设置停止位*/
     if( nStop == 1)/* 设置停止位；若停止位为1，则清除CSTOPB，若停止位为2，则激活CSTOPB */
     {
         newttys1.c_cflag &= ~CSTOPB;/*默认为一位停止位； */
     }
     else if( nStop == 2)
     {
         newttys1.c_cflag |= CSTOPB;/* CSTOPB表示送两位停止位 */
     }

     /* 设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
     newttys1.c_cc[VTIME] = 0;/* 非规范模式读取时的超时时间；*/
     newttys1.c_cc[VMIN]  = 0; /* 非规范模式读取时的最小字符数*/
     tcflush(fd ,TCIFLUSH);/* tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */

      /*激活配置使其生效*/
     if((tcsetattr( fd, TCSANOW,&newttys1))!=0)
     {
         perror("com set error");
         exit(1);
     }

}

int GetGpsDataNode::gps_analyse(char *buff, GPRMC *gps_data){
  char *ptr=NULL;
       if(gps_data==NULL)
        {
           return -1;
        }
        if(strlen(buff)<10)
        {
           return -1;
        }
  /* 如果buff字符串中包含字符"$GPRMC"则将$GPRMC的地址赋值给ptr */
        if(NULL==(ptr=strstr(buff,"$GPRMC")))
        {
           return -1;
        }
  /* sscanf函数为从字符串输入，意思是将ptr内存单元的值作为输入分别输入到后面的结构体成员 */
        sscanf(ptr,"$GPRMC,%d.000,%c,%f,N,%f,E,%f,%f,%d,,,%c*",&(gps_data->time),&(gps_data->pos_state),&(gps_data->latitude),&(gps_data->longitude),&(gps_data->speed),&(gps_data->direction),&(gps_data->date),&(gps_data->mode));
}

int GetGpsDataNode::print_gps(GPRMC *gps_data){
      printf("                                                           \n");
      printf("                                                           \n");
      printf("===========================================================\n");
      printf("==                   全球GPS定位导航模块                 ==\n");
      printf("==              Author：555555                           ==\n");
      printf("==              Email：wangzuwu@shu.edu.cn               ==\n");
      printf("==              Platform：NMEA-0183                        ==\n");
      printf("===========================================================\n");
      printf("                                                           \n");
      printf("===========================================================\n");
      printf("==   GPS state bit : %c  [A:有效状态 V:无效状态]              \n",gps_data->pos_state);
      printf("==   GPS mode  bit : %c  [A:自主定位 D:差分定位]               \n", gps_data->mode);
      printf("==   Date : 20%02d-%02d-%02d                                  \n",gps_data->date%100,(gps_data->date%10000)/100,gps_data->date/10000);
      printf("==   Time : %02d:%02d:%02d                                   \n",(gps_data->time/10000+8)%24,(gps_data->time%10000)/100,gps_data->time%100);
      printf("==   纬度 : 北纬:%d度%d分%d秒                              \n", ((int)gps_data->latitude) / 100, (int)(gps_data->latitude - ((int)gps_data->latitude / 100 * 100)), (int)(((gps_data->latitude - ((int)gps_data->latitude / 100 * 100)) - ((int)gps_data->latitude - ((int)gps_data->latitude / 100 * 100))) * 60.0));
      printf("==   经度 : 东经:%d度%d分%d秒                              \n", ((int)gps_data->longitude) / 100, (int)(gps_data->longitude - ((int)gps_data->longitude / 100 * 100)), (int)(((gps_data->longitude - ((int)gps_data->longitude / 100 * 100)) - ((int)gps_data->longitude - ((int)gps_data->longitude / 100 * 100))) * 60.0));
      printf("==   速度 : %.3f  m/s                                      \n",gps_data->speed);
      printf("==                                                       \n");
      printf("============================================================\n");

}

void GetGpsDataNode::log( const LogLevel &level, const std::string &msg) {
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
