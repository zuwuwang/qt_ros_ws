/**
 * @file /include/guitest/ImageSaveNode.hpp
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
#ifndef guitest_IMGSAVE_NODE_HPP_
#define guitest_IMGSAVE_NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <image_transport/image_transport.h>

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace guitest {

/*****************************************************************************
** Class
*****************************************************************************/

class ImageSaveNode : public QThread {
    Q_OBJECT
public:
  ImageSaveNode(int argc, char** argv );
  virtual ~ImageSaveNode();
  bool init();
  void run();
  void captureTimerCallback(const ros::TimerEvent& e);
  void imageTransCallback(const sensor_msgs::ImageConstPtr& msg);
  bool saveImageFlag = true;
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
    cv::Mat cameraImage;

Q_SIGNALS:
  void displayCameraImage();
  void loggingUpdated();
  void socketSend();
    void rosShutdown();

private:
  int init_argc;
  char** init_argv;
  image_transport::Subscriber cameraImage_subscriber;
    QStringListModel logging_model;
};

}  // namespace guitest

#endif // guitest_IMGSAVE_NODE_HPP_
