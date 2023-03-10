#include "ros/node_handle.h"
#include "ros/publisher.h"
#include <ros/ros.h>
#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Twist.h>

int nImage = 0; //Initialization of a global variable

geometry_msgs::Twist cmd;

// Definition of the done calback. It is called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
  ROS_INFO("The Action has been completed");
  
}

// Definition of the active callback. It is called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

// Definition of the feedback callback. This will be called when feedback is received from the action server. It just // prints a message indicating a new message has been received
void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback)
{
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "drone_action_client"); // Initializes the action client node
  // Create the connection to the action server
  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
  client.waitForServer(); // Waits until the action server is up and running 

  ardrone_as::ArdroneGoal goal; // Creates a goal to send to the action server
  goal.nseconds = 10; // Fills the goal. Indicates, take pictures along 10 seconds
  client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb); // sends the goal to the action server, specifying which                                                               // functions to call when the goal completes, when the                                                                 // goal becames active, and when feedback is received
  
  ros::Rate loop_rate(2);
  actionlib::SimpleClientGoalState state_result = client.getState();

  ros::NodeHandle n;
  ros::Publisher drone_commands = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  cmd.angular.z = -1.1;
  cmd.linear.x = 1.1;
  int last_nImage = nImage;

  while (state_result == actionlib::SimpleClientGoalState::ACTIVE || state_result == actionlib::SimpleClientGoalState::PENDING)
  {  
    if (nImage != last_nImage)
    {
      cmd.angular.z -= 0.5;
      cmd.linear.x += 0.1;
      drone_commands.publish(cmd);
      ROS_INFO("Flying!");
      last_nImage = nImage; 
    }
    state_result = client.getState();
  }

  cmd.angular.z = 0.0;
  cmd.linear.x = 0.0;
  drone_commands.publish(cmd);
  ROS_INFO("STOP!");
  ros::shutdown();

  
  return 0;
}