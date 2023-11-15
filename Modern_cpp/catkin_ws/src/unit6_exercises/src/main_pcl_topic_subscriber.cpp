#include "subscriber_basic.h"
#include <sensor_msgs/PointCloud2.h>

using sensor_msgs::PointCloud2;

int main(int argc, char **argv) {

  ros::init(argc, argv, "pcl_main_node");

  ros::NodeHandle _n("pcl_main_ns");
  string topic_name = "/camera/depth_registered/points";

  MagicSubscriber<PointCloud2> magic_subscriber_object(_n, topic_name);

  ros::spin();

  return 0;
}