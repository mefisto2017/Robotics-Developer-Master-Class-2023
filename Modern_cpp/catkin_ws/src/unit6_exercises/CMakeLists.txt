cmake_minimum_required(VERSION 3.0.2)
project(unit6_exercises)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  cv_bridge
  pcl_conversions
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(magic_printer_library
  src/magic_printer.cpp
)

add_library(subscriber_basic_library
  src/subscriber_basic.cpp
)

add_library(magic_subscriber_function_library
  src/magic_subscriber_function.cpp
)

add_library(specialised_example_library
  src/specialised_example.cpp
)

add_library(magic_subscriber_image_edgedetector_library
  src/magic_subscriber_image_edgedetector.cpp
)

add_library(magic_subscriber_pcl2image_library
  src/magic_subscriber_pcl2image.cpp
)

add_library(specialised_complete_library
  src/specialised_complete.cpp
)

## Create executables
add_executable(main_magic_printer_node src/main_magic_printer.cpp)
add_executable(main_subscriber_basic_node src/main_subscriber_basic.cpp)
add_executable(main_pcl_topic_node src/main_pcl_topic_subscriber.cpp)
add_executable(magic_subscriber_function_node src/main_magic_subscriber_function.cpp)
add_executable(main_specialised_example_node src/main_specialised_example.cpp)
add_executable(main_edge_detector_node src/main_edge_detector.cpp)
add_executable(main_pcl2image_node src/main_pcl2image.cpp)
add_executable(main_specialised_complete_node src/main_specialised_complete.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(main_magic_printer_node
    magic_printer_library
    ${catkin_LIBRARIES}
)

target_link_libraries(main_subscriber_basic_node
	subscriber_basic_library
	${catkin_LIBRARIES}
)

target_link_libraries(magic_subscriber_function_node
	magic_subscriber_function_library
	${catkin_LIBRARIES}
)

target_link_libraries(main_specialised_example_node
	specialised_example_library
	${catkin_LIBRARIES}
)

target_link_libraries(main_pcl_topic_node
	subscriber_basic_library
	${catkin_LIBRARIES}
)

target_link_libraries(main_edge_detector_node
	magic_subscriber_image_edgedetector_library
	${catkin_LIBRARIES}
)

target_link_libraries(main_pcl2image_node
	magic_subscriber_pcl2image_library
	${catkin_LIBRARIES}
)

target_link_libraries(main_specialised_complete_node
	specialised_complete_library
	${catkin_LIBRARIES}
)