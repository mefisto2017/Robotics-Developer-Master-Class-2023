#include "ros/init.h"
#include "ros/publisher.h"
#include "ros/ros.h"
#include "ros/service.h"
#include "std_srvs/Empty.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bb8_service_client");
  ros::NodeHandle nh;

 

  ros::service::waitForService("/move_bb8_in_circle");
  ros::ServiceClient bb8 = nh.serviceClient<std_srvs::Empty>("/move_bb8_in_circle");
  std_srvs::Empty command; // Create an empty object
  
  if (bb8.call(command)) // 
  {
    ROS_INFO("GOOD"); // Print the result given by the service called
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }
                                                                                                                                                       
  return 0;
}