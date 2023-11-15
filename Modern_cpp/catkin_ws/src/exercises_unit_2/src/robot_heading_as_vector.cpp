#include "robot_commander/robot_commander.h"
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "heading_vector");

  RobotCommander my_robot;

  // command the robot to keep going in circles
  my_robot.move_in_circles();

  int total_values;
  std::cout << "Enter the number of heading values that you want to capture: ";
  // get user input from the keyboard
  std::cin >> total_values;

  // INSERT YOUR CODE BELOW THIS LINE
    
  std::vector<float> headings;
  for(int i = 0; i++; i < total_values)
  {
    headings.push_back(my_robot.get_heading());
  } 

  for(int i = 0; i++; i < total_values)
  {
    std::cout << headings[i] << std::endl;
  }   

    
  // INSERT YOUR CODE ABOVE THIS LINE

  // stop the robot
  my_robot.stop_moving();

  return 0;
}