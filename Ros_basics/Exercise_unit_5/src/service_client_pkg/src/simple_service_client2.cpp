#include "ros/ros.h"
#include <ros/package.h>
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  // Create the connection to the service /execute_trajectory
  ros::service::waitForService("/execute_trajectory");  // wait for service to be running
  ros::ServiceClient exec_tra_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj trajectory; // Create an object of type TrajByName
  trajectory.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") + "/config/get_food.txt";
  
  if (exec_tra_service.call(trajectory)) // Send through the connection the name of the trajectory to execute
  {
    ROS_INFO("GOOD"); // Print the result given by the service called
  }
  else
  {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }

  return 0;
}