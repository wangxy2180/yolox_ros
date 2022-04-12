cmake_minimum_required(VERSION 3.0.2)
project(yolox_ros)
set(CMAKE_CXX_STANDARD 14)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

# 他居然自动去找openvino的opencv了
find_package(OpenCV 3.4.10 REQUIRED)
find_package(InferenceEngine REQUIRED)
find_package(ngraph REQUIRED)


catkin_package(
  #  INCLUDE_DIRS include
  #  LIBRARIES yolox_ros
  #  CATKIN_DEPENDS cv_bridge image_transport roscpp rospy sensor_images std_msgs
  #  DEPENDS system_lib
  )
  # 
message("111111111111111111,${include}")
message("222222222222222222,${catkin_INCLUDE_DIRS}")
message("333333333333333333,${OpenCV_INCLUDE_DIRS}")
  
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

# include_directories(
#     ${OpenCV_INCLUDE_DIRS}
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_BINARY_DIR}
# )
    
add_executable(${PROJECT_NAME}_openvino src/yolox_ros_openvino.cpp)

target_link_libraries( ${PROJECT_NAME}_openvino
    ${InferenceEngine_LIBRARIES}
    ${NGRAPH_LIBRARIES}
  ${catkin_LIBRARIES}
    ${OpenCV_LIBS} 
)



add_executable(default_cam src/default_camera_img.cpp)
target_link_libraries(
  default_cam 
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES})