#include "robot_commander/robot_commander.h"
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "heading_deque");

  RobotCommander my_robot;

  // command the robot to keep going in circles
  my_robot.move_in_circles();

  int total_values;
  std::cout << "Enter the number of heading values that you want to capture: ";
  // get user input from the keyboard
  std::cin >> total_values;

  // INSERT YOUR CODE BELOW THIS LINE

  // declare a deque of floats
  std::deque<float> headings;

  int i = 0;
  while (i < total_values) {
    headings.push_front(my_robot.get_heading());
    std::cout << "Collecting heading value: " << headings[0] << std::endl;
    i++;
    usleep(1000000);
  }

  // new line
  std::cout << std::endl;
  std::cout << "Displaying saved data" << std::endl;
  for (int i = 0; i < headings.size(); i++) {
    std::cout << "Heading value " << i << ": " << headings[i] << std::endl;
  }

  // INSERT YOUR CODE ABOVE THIS LINE

  // stop the robot
  my_robot.stop_moving();

  return 0;
}