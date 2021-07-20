cmake_minimum_required(VERSION 2.8.3)
project(manipulation_ur5_cell_descriptions)

find_package(catkin REQUIRED COMPONENTS
  ur_description
  robotiq_2f_85_gripper_visualization
)

catkin_package(
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
