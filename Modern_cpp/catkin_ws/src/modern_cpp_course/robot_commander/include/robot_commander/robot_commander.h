#ifndef ROBOT_COMMANDER_H
#define ROBOT_COMMANDER_H
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <ros/ros.h>
#include <string>
#include <tf/tf.h>

class RobotCommander {
private:
  ros::NodeHandle n;
  ros::Publisher vel_pub;
  geometry_msgs::Twist vel_msg;
  std::string vel_topic;
  ros::Subscriber odom_sub;
  std::string odom_topic;
  float x_pos;
  float y_pos;
  float z_pos;
  float heading_angle;

  void odom_callback(const nav_msgs::Odometry::ConstPtr &odom_msg);

public:
  RobotCommander();
  void move_in_circles();
  void move_forward(int n_secs);
  void move_backwards(int n_secs);
  void turn(float velocity_value, int n_secs);
  void stop_moving();
  float get_x_position();
  float get_y_position();
  float get_z_position();
  float get_heading();
};

#endif
