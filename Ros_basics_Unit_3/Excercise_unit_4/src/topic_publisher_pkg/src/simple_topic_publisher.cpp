#include "topic_publisher_pkg/Age.h"
#include <ros/ros.h>

int main(int argc, char **argv) {

  ros::init(argc, argv,
            "topic_publisher"); // Initiate a Node named 'topic_publisher'
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<topic_publisher_pkg::Age>("/age", 1000);
  ros::Rate loop_rate(2); // Set a publish rate of 2 Hz

  topic_publisher_pkg::Age robot_age;
  robot_age.days = 10.0;

  while (ros::ok()) // Create a loop that will go until someone stops the
                    // program execution
  {
    pub.publish(robot_age);
    robot_age.days += 1;
    ros::spinOnce();
    loop_rate.sleep(); // Make sure the publish rate maintains at 2 Hz
  }

  return 0;
}