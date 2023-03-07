#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
// Import all the necessary ROS libraries and import the Int32 message from the
// std_msgs package

int main(int argc, char **argv) {

  ros::init(argc, argv,
            "topic_publisher"); // Initiate a Node named 'topic_publisher'
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Rate loop_rate(2); // Set a publish rate of 2 Hz

  geometry_msgs::Twist movement;
  movement.linear.x = -0.2;

  while (ros::ok()) // Create a loop that will go until someone stops the
                    // program execution
  {
    pub.publish(movement);
    movement.linear.x -= 0.1;
    ros::spinOnce();
    loop_rate.sleep(); // Make sure the publish rate maintains at 2 Hz
  }

  return 0;
}