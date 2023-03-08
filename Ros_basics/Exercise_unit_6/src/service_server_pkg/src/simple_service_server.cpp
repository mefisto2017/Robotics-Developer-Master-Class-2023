#include "ros/publisher.h"
#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "geometry_msgs/Twist.h"
// Import the service message header file generated from the Empty.srv message

ros::Publisher command;
geometry_msgs::Twist msg;

// We define the callback function of the service
bool my_callback(std_srvs::Empty::Request  &req,
                 std_srvs::Empty::Response &res)
{  
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("BB* is moving"); // We print an string whenever the Service gets called
  //cmd_vel msg
  msg.linear.x = 0.2;
  msg.angular.z = 0.2;
  command.publish(msg);

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_service");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService("/move_bb8_in_circle", my_callback); // create the Service called
  command = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

                                                                                            // my_service with the defined                                                                                        // callback
  ros::spin(); // mantain the service open.

  return 0;
}