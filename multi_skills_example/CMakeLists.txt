cmake_minimum_required(VERSION 3.10.0)
project(multi_skills_example)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(catkin REQUIRED COMPONENTS
              moveit_planning_helper
              manipulation_msgs
              manipulation_utils
              roscpp
              rosdyn_core
              std_srvs
              rosparam_utilities
              object_loader_msgs
              tf_conversions
)

catkin_package(
  INCLUDE_DIRS
  LIBRARIES outbound_place
  CATKIN_DEPENDS  moveit_planning_helper
                  manipulation_msgs 
                  manipulation_utils 
                  roscpp 
                  rosdyn_core 
                  rosparam_utilities 
                  std_srvs 
                  object_loader_msgs 
                  tf_conversions 
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} src/multi_skills_test_node.cpp)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
