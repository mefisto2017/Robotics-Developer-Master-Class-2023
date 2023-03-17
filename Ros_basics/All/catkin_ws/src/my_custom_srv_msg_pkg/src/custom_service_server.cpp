#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

ros::Publisher command;
geometry_msgs::Twist msg;

bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) {
    
  msg.linear.x = -0.2;
  msg.angular.z = -0.2;
  command.publish(msg);
  ros::Duration (req.duration).sleep();

  msg.linear.x = 0.0;
  msg.angular.z = 0.0;
  command.publish(msg);
  res.success = true;

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService("/my_service", my_callback);
  command = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::spin();

  return 0;
}