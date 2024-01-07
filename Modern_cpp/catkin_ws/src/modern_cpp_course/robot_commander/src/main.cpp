#include "robot_commander/robot_commander.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_commander_node");

  RobotCommander my_robot;

  ROS_INFO("Moving forward 4 seconds");
  my_robot.move_forward(4);

  return 0;
}