/*
Copyright (c) 2019, Manuel Beschi CNR-STIIMA manuel.beschi@stiima.cnr.it
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ros/ros.h>

#include <manipulation_msgs/JobExecution.h>

bool callback(manipulation_msgs::JobExecution::Request& request, 
              manipulation_msgs::JobExecution::Response& response)
{
  ROS_INFO("Fake JobExecution callback received: skill name %s, tool_id %s, property_id %d",  request.skill_name.c_str(), 
                                                                                              request.tool_id.c_str(),
                                                                                              request.property_id);

  response.results = manipulation_msgs::JobExecution::Response::Success;
  return true;
}

int main(int argc, char **argv)
{ 
  std::string service_name;
  if( argc >= 2 && argc <= 4) 
  {
    service_name = argv[1];    
  }
  else
  {
    ROS_ERROR("Wrong number of input, the input needed are: service_name.");
    return -1;
  }

  ros::init(argc, argv,"manipulation_fake_tool_server");
  ros::NodeHandle nh;

  ros::AsyncSpinner spinner(4);
  spinner.start();

  ROS_INFO("Creating fake tool server...");
  ros::ServiceServer fake_tool_srv = nh.advertiseService(service_name,callback);

  ros::Rate lp(0.1);
  while (ros::ok())
  {
    lp.sleep();
  }

  return 0;
}
