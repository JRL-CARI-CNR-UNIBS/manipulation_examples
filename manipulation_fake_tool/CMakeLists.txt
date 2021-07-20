cmake_minimum_required(VERSION 3.10.0)
project(manipulation_fake_tool)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(catkin REQUIRED COMPONENTS
  manipulation_msgs
  roscpp
)

catkin_package(
  INCLUDE_DIRS
  LIBRARIES outbound_place
  CATKIN_DEPENDS  manipulation_msgs 
                  roscpp 
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME}_server src/manipulation_fake_tool_server_node.cpp)
add_dependencies(${PROJECT_NAME}_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_server
  ${catkin_LIBRARIES}
)
