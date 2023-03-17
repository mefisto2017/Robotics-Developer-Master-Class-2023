#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

class MoveBB8 {

public:
  // ROS Objects
  ros::NodeHandle nh_;

  // ROS Services
  ros::ServiceServer my_service;

  // ROS Publishers
  ros::Publisher vel_pub;

  // ROS Messages
  geometry_msgs::Twist vel_msg;

  MoveBB8() {
    my_service = nh_.advertiseService("/move_bb8_in_circle",
                                      &MoveBB8::my_callback, this);
    ROS_INFO("The Service /move_bb8_in_circle is READY");
    vel_pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  }

  void move_in_circle(void) {
    vel_msg.linear.x = 0.2;
    vel_msg.angular.z = 0.2;
    vel_pub.publish(vel_msg);
  }

  void stop(void) {
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
  }

  bool
  my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request &req,
              my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) {
    ROS_INFO("The Service /move_bb8_in_circle has been called");
    move_in_circle();
    ros::Duration(req.duration).sleep();
    stop();
    res.success = true;
    ROS_INFO("Finished service /move_bb8_in_circle");
    return true;
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "move_bb8_node");

  MoveBB8 moveBB8;

  ros::spin();

  return 0;
}