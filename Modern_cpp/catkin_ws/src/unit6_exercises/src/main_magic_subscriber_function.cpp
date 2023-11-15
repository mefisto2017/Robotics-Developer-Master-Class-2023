#include "magic_subscriber_function.h"
#include <sensor_msgs/Image.h>

int main(int argc, char **argv) {

  ros::init(argc, argv, "magic_susbcriber_main_node");

  ros::NodeHandle _n("magic_susbcriber_main_ns");
  string topic_name = "/camera/rgb/image_raw";

  MagicSubscriber magic_subscriber_object;

  magic_subscriber_object.init<sensor_msgs::Image>(_n, topic_name);

  ros::spin();

  return 0;
}