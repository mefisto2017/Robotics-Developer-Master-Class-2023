#include "robot_commander/robot_commander.h"

#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "position_array");

  RobotCommander my_robot;

  float my_array[3];
  my_array[0] = my_robot.get_x_position();
  my_array[1] = my_robot.get_y_position();
  my_array[2] = my_robot.get_z_position();

  for (int i = 0; i < 3; i++)
    std::cout << my_array[i] << " ";
    std::cout << std::endl;
  return 0;
}