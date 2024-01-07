#include "robot_commander/robot_commander.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <ros/ros.h>

RobotCommander::RobotCommander() {
  n = ros::NodeHandle("~");
  vel_topic = "/cmd_vel";
  vel_pub = n.advertise<geometry_msgs::Twist>(n.resolveName(vel_topic), 1);
  odom_topic = "/odom";
  odom_sub = n.subscribe(odom_topic, 10, &RobotCommander::odom_callback, this);
  ROS_INFO("Initializing node");
  usleep(2000000);
}

void RobotCommander::odom_callback(
    const nav_msgs::Odometry::ConstPtr &odom_msg) {
  x_pos = odom_msg->pose.pose.position.x;
  y_pos = odom_msg->pose.pose.position.y;
  z_pos = odom_msg->pose.pose.position.z;

  tf::Quaternion q(
      odom_msg->pose.pose.orientation.x, odom_msg->pose.pose.orientation.y,
      odom_msg->pose.pose.orientation.z, odom_msg->pose.pose.orientation.w);
  tf::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);

  heading_angle = yaw;
}

void RobotCommander::move_in_circles() {
  ROS_INFO("Moving in circles");
  vel_msg.linear.x = 0.2;
  vel_msg.angular.z = 0.2;
  vel_pub.publish(vel_msg);
}

void RobotCommander::move_forward(int time) {

  ros::Rate rate(10);

  ros::Time start_time = ros::Time::now();
  ros::Duration timeout(time);
  while (ros::Time::now() - start_time < timeout) {
    ROS_INFO("Moving forward");
    ros::spinOnce();
    vel_msg.linear.x = 0.4;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
    rate.sleep();
  }
  ROS_INFO("Stopping the robot");
  vel_msg.linear.x = 0.0;
  vel_msg.angular.z = 0.0;
  vel_pub.publish(vel_msg);
}

void RobotCommander::move_backwards(int time) {

  ros::Rate rate(10);

  ros::Time start_time = ros::Time::now();
  ros::Duration timeout(time);
  while (ros::Time::now() - start_time < timeout) {
    ROS_INFO("Moving backwards");
    ros::spinOnce();
    vel_msg.linear.x = -0.4;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
    rate.sleep();
  }
  ROS_INFO("Stopping the robot");
  vel_msg.linear.x = 0.0;
  vel_msg.angular.z = 0.0;
  vel_pub.publish(vel_msg);
}

void RobotCommander::turn(float velocity_value, int n_secs) {
  ros::Rate rate(10);
  ros::Time start_time = ros::Time::now();
  ros::Duration timeout(n_secs);

  double WZ = 0.0;
  if (velocity_value < 0.0) {
    ROS_INFO("Turning clockwise");
    WZ = velocity_value;
  } else if (velocity_value > 0.0) {
    ROS_INFO("Turning counterclockwise");
    WZ = velocity_value;
  } else {
    ROS_INFO("Not turning");
    WZ = 0.0;
  }

  while (ros::Time::now() - start_time < timeout) {
    ros::spinOnce();
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = WZ;
    vel_pub.publish(vel_msg);
    rate.sleep();
  }
  ROS_INFO("Stopping the robot");
  vel_msg.linear.x = 0.0;
  vel_msg.angular.z = 0.0;
  vel_pub.publish(vel_msg);
}

void RobotCommander::stop_moving() {
  ROS_INFO("Stopping the robot");
  vel_msg.linear.x = 0.0;
  vel_msg.angular.z = 0.0;
  vel_pub.publish(vel_msg);
}

float RobotCommander::get_x_position() {
  ros::spinOnce();
  return this->x_pos;
}

float RobotCommander::get_y_position() {
  ros::spinOnce();
  return this->y_pos;
}

float RobotCommander::get_z_position() {
  ros::spinOnce();
  return this->z_pos;
}

float RobotCommander::get_heading() {
  ros::spinOnce();
  return this->heading_angle;
}
