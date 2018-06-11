/**
 * @file /include/guitest/getgpsdata.hpp
 *
 * @brief Communications central!
 *
 * @date june 2018
 *
 * @auth  wangZuWu
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef GETGPSDATA_HPP_
#define GETGPSDATA_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

/*****************************************************************************
** Class
*****************************************************************************/

class GetGpsData : public QThread {
    Q_OBJECT
public:
  GetGpsData(int argc, char** argv );
  virtual ~GetGpsData();
  bool init();
  void run();
  /**************
   *  GPRMC
   * ***********/
  typedef unsigned int UINT;
  typedef int BYTE;

  typedef struct __gprmc__
  {
     UINT time;/* gps定位时间 */
     char pos_state;/*gps状态位*/
     float latitude;/*纬度 */
     float longitude;/* 经度 */
     float speed; /* 速度 */
     float direction;/*航向 */
     UINT date;  /*日期  */
     float declination; /* 磁偏角 */
     char dd;
     char mode;/* GPS模式位 */

  }GPRMC;

  int fd=0;
  int n=0;
  int i;
  GPRMC gprmc;
  char buff[GPS_LEN];
  char *dev_name="/dev/ttyUSB0";
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

  /*************
   *  extern c
   * ****************/
  extern int set_serial(int fd,int nSpeed, int nBits, char nEvent, int nStop);
  extern int print_gps(GPRMC *gps_date);
  extern int gps_analyse(char *buff,GPRMC *gps_data);

Q_SIGNALS:
  void loggingUpdated();
    void rosShutdown();

private:
  int init_argc;
  char** init_argv;
  ros::Publisher chatter_publisher;
    QStringListModel logging_model;
};


}  // namespace guitest

#endif // GETGPSDATA_H
