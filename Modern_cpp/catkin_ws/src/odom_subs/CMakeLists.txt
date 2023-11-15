cmake_minimum_required(VERSION 3.0.2)
project(odom_subs)


find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  rospy
  test_library
)

catkin_package()

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(odom_listener src/odom_listener.cpp)
add_dependencies(odom_listener nav_msgs_generate_messages_cpp)
 target_link_libraries(odom_listener
   ${catkin_LIBRARIES}
)