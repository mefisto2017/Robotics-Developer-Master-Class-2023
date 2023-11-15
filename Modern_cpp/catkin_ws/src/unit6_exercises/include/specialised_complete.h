#ifndef MAGIC_SUBSCRIBER_H
#define MAGIC_SUBSCRIBER_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>

// pcl::toROSMsg
#include <pcl_conversions/pcl_conversions.h>
// stl stuff
#include </opt/ros/noetic/include/cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sensor_msgs/image_encodings.h>

static const std::string OPENCV_WINDOW = "Image window";

using namespace std;
using namespace cv;
using sensor_msgs::Image;
using sensor_msgs::PointCloud2;

template <typename ROSMessageType> class MagicSubscriber {
public:
  MagicSubscriber(ros::NodeHandle &ros_node, const string subscriber_topic,
                  const string publish_topic = "/default");
  ~MagicSubscriber();
  void CallbackToTopic(const typename ROSMessageType::ConstPtr &msg);

private:
  ros::NodeHandle *m_ros_node_object;
  string m_subscriber_topic;
  ros::Subscriber sub_;
  ros::Publisher pub_;
};

// function Definition
template <typename ROSMessageType>
MagicSubscriber<ROSMessageType>::MagicSubscriber(ros::NodeHandle &ros_node,
                                                 const string subscriber_topic,
                                                 const string publish_topic) {
  // We used an initialiser list
  this->m_subscriber_topic = subscriber_topic;
  this->m_ros_node_object = &ros_node;

  if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                     ros::console::levels::Info)) {
    ros::console::notifyLoggerLevelsChanged();
  }

  sub_ = this->m_ros_node_object->subscribe(
      this->m_subscriber_topic, 1,
      &MagicSubscriber<ROSMessageType>::CallbackToTopic, this);

  pub_ = this->m_ros_node_object->template advertise<Image>(publish_topic,
                                                                1000);
};



// Destructor
template <typename ROSMessageType>
MagicSubscriber<ROSMessageType>::~MagicSubscriber() {
  cout << "MagicSubscriber Destructor is called" << endl;
};

// Generic callback
template <typename ROSMessageType>
void MagicSubscriber<ROSMessageType>::CallbackToTopic(
    const typename ROSMessageType::ConstPtr &msg) {
  // the uint8 is an alias of unsigned char, therefore needs casting to int
  ROS_INFO_STREAM("GENERIC Template Callback message =" << msg);
};

// Specialized template callback for image edge detector
template <>
inline void
MagicSubscriber<Image>::CallbackToTopic(const sensor_msgs::Image::ConstPtr &msg) {
  // the uint8 is an alias of unsigned char, therefore needs casting to int
  ROS_INFO_STREAM(
      "Call Back Topic Image Data[0]=" << static_cast<int>(msg->data[0]));

  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  } catch (cv_bridge::Exception &e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  // The Edge detection
  // Convert to graycsale
  cvtColor(cv_ptr->image, cv_ptr->image, COLOR_BGR2GRAY);

  // Blur the image for better edge detection
  GaussianBlur(cv_ptr->image, cv_ptr->image, Size(3, 3), 0);

  // Canny edge detection
  Canny(cv_ptr->image, cv_ptr->image, 100, 200, 3, false);

  putText(cv_ptr->image, "EDGE DETECTION CAM", cvPoint(30, 30),
          FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_MSA);

  // Display canny edge detected image
  // imshow(OPENCV_WINDOW, cv_ptr->image);
  // waitKey(3);

  // Update GUI Window
  // imshow(OPENCV_WINDOW, cv_ptr->image);
  // waitKey(3);

  // Output modified video stream
  cvtColor(cv_ptr->image, cv_ptr->image, COLOR_GRAY2BGR);
  pub_.publish(cv_ptr->toImageMsg());
};

// Specialized template callback for point cloud
template <>
inline void MagicSubscriber<PointCloud2>::CallbackToTopic(
    const PointCloud2::ConstPtr &msg) {
  // the uint8 is an alias of unsigned char, therefore needs casting to int
  ROS_INFO_STREAM("Call Back Topic Image To Depth Data[0]="
                  << static_cast<int>(msg->data[0]));

  sensor_msgs::PointCloud point_cloud;

  sensor_msgs::convertPointCloud2ToPointCloud(*msg, point_cloud);

  // These are value sextracted form the rgb camera caminfo
  float K[9] = {343.49636753580074,
                0.0,
                320.5,
                0.0,
                343.49636753580074,
                240.5,
                0.0,
                0.0,
                1.0};
  float centre_x = K[2];
  float centre_y = K[5];
  float focal_x = K[0];
  float focal_y = K[4];
  int cam_info_height = 480;
  int cam_info_width = 640;

  Mat cv_image = Mat(cam_info_height, cam_info_width, CV_32FC1,
                     Scalar(std::numeric_limits<float>::max()));

  for (int i = 0; i < point_cloud.points.size(); i++) {
    if (point_cloud.points[i].z == point_cloud.points[i].z) {
      float z = point_cloud.points[i].z * 1000.0;
      float u = (point_cloud.points[i].x * 1000.0 * focal_x) / z;
      float v = (point_cloud.points[i].y * 1000.0 * focal_y) / z;
      int pixel_pos_x = (int)(u + centre_x);
      int pixel_pos_y = (int)(v + centre_y);

      if (pixel_pos_x > (cam_info_width - 1)) {
        pixel_pos_x = cam_info_width - 1;
      }
      if (pixel_pos_y > (cam_info_height - 1)) {
        pixel_pos_y = cam_info_height - 1;
      }
      cv_image.at<float>(pixel_pos_y, pixel_pos_x) = z;
    }
  }

  putText(cv_image, "Depth CAM", Point(50, 50), FONT_HERSHEY_DUPLEX, 1,
          Scalar(0, 255, 0), 2, false);

  cv_image.convertTo(cv_image, CV_16UC1);

  sensor_msgs::ImagePtr output_image =
      cv_bridge::CvImage(std_msgs::Header(), "16UC1", cv_image).toImageMsg();
  output_image->header.stamp = ros::Time::now();
  pub_.publish(output_image);
};

#endif
