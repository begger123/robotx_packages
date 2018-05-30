#ifndef HSV_BUOY_DETECTOR_H_INCLUDED
#define HSV_BUOY_DETECTOR_H_INCLUDED

//headers in this package
#include <hsv_threshold.h>
#include <robotx_msgs/Objects2D.h>

//headers in ROS
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

//headers in STL
#include <vector>

class hsv_buoy_detector
{
public:
  hsv_buoy_detector();
  ~hsv_buoy_detector();
private:
  void image_callback(const sensor_msgs::ImageConstPtr& msg);
  std::vector<cv::Mat> masked_images_;
  ros::NodeHandle nh_;
  std::vector<hsv_threshold> threashold_params;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  ros::Publisher objects2d_pub_;
};
#endif