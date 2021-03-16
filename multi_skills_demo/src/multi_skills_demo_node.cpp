#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <manipulation_msgs/PickObjectsAction.h>
#include <manipulation_msgs/PlaceObjectsAction.h>
#include <manipulation_msgs/GoToAction.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <rosparam_utilities/rosparam_utilities.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "multi_skills");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ros::AsyncSpinner spinner(4);
  spinner.start();

  std::string group_name = "manipulator";
  if (!pnh.getParam("group_name",group_name))
  {
    ROS_ERROR("Node %s has not a parameter named group_name",pnh.getNamespace().c_str());
    return -1;
  }

  actionlib::SimpleActionClient<manipulation_msgs::PickObjectsAction> pick_ac("/inbound_pick_server/"+group_name+"/pick");
  actionlib::SimpleActionClient<manipulation_msgs::PlaceObjectsAction> place_ac("/outbound_place_server/"+group_name+"/place");
  actionlib::SimpleActionClient<manipulation_msgs::GoToAction> go_to_ac("/go_to_location_server/"+group_name+"/go_to");

  ROS_INFO("Waiting for pick server");
  pick_ac.waitForServer();
  ROS_INFO("Connection ok");
  ROS_INFO("Waiting for place server");
  place_ac.waitForServer();
  ROS_INFO("Connection ok");
  ROS_INFO("Waiting for goto server");
  go_to_ac.waitForServer();
  ROS_INFO("Connection ok");

  std::vector<std::pair<std::string,std::string>> recipe;
  XmlRpc::XmlRpcValue param;
  if (!pnh.getParam("recipe",param))
  {
    ROS_ERROR("Node %s has not a parameter named recipe",pnh.getNamespace().c_str());
    return -1;
  }


  if (param.getType() != XmlRpc::XmlRpcValue::TypeArray)
  {
    ROS_ERROR("recipe is not a list" );
    return 0;
  }

  for(size_t i=0; i < param.size(); i++)
  {
    XmlRpc::XmlRpcValue config = param[i];
    if( config.getType() != XmlRpc::XmlRpcValue::TypeStruct)
    {
      ROS_WARN("The element #%zu is not a struct", i);
      continue;
    }
    if( !config.hasMember("action") )
    {
      ROS_WARN("The element #%zu has not the field 'type'", i);
      continue;
    }
    std::string action = rosparam_utilities::toString(config["action"]);

    if( !config.hasMember("description") )
    {
      ROS_WARN("The element #%zu has not the field 'frame'", i);
      continue;
    }
    std::string description = rosparam_utilities::toString(config["description"]);
    ROS_INFO("Add skill -> %s:%s",action.c_str(),description.c_str());

    recipe.push_back(std::pair<std::string,std::string>(action,description));
  }


  manipulation_msgs::PlaceObjectsGoal place_goal;
  manipulation_msgs::PickObjectsGoal pick_goal;
  manipulation_msgs::GoToGoal go_to_goal;

  for (const std::pair<std::string,std::string>& skill: recipe)
  {
    ROS_INFO("skill -> %s:%s",skill.first.c_str(),skill.second.c_str());

    if (skill.first.compare("pick")==0)
    {
      ROS_INFO("[Group %s] Goal: pick object %s",pnh.getNamespace().c_str(),skill.second.c_str());

      pick_goal.object_types.push_back(skill.second);

      pick_ac.sendGoalAndWait(pick_goal);


      if (pick_ac.getResult()->result<0)
      {
        ROS_ERROR("[Group %s] unable to pick -> object type = %s",pnh.getNamespace().c_str(),skill.second.c_str());
        return 0;
      }
      ROS_INFO("[Group %s] well done! I picked it, name = %s",pnh.getNamespace().c_str(),pick_ac.getResult()->object_name.c_str());
      place_goal.object_name = pick_ac.getResult()->object_name;

    }
    else if (skill.first.compare("place")==0)
    {
      ROS_INFO("[Group %s] Goal: place object %s in %s",pnh.getNamespace().c_str(),place_goal.object_name.c_str(),skill.second.c_str());
      place_goal.object_name = skill.second;
      place_ac.sendGoalAndWait(place_goal);

      if (place_ac.getResult()->result<0)
      {
        ROS_ERROR("[Group %s] unable to place, stop it",pnh.getNamespace().c_str());
        return 0;
      }
      ROS_INFO("[Group %s] well done! ",pnh.getNamespace().c_str());

    }
    else if (skill.first.compare("goto")==0)
    {
      ROS_INFO("[Group %s] Goal: Go to %s",pnh.getNamespace().c_str(),skill.second.c_str());

      go_to_goal.location_name = skill.second;
      go_to_ac.sendGoalAndWait(go_to_goal);

      if (go_to_ac.getResult()->result<0)
      {
        ROS_ERROR("[Group %s] unable to place, stop it",pnh.getNamespace().c_str());
        return 0;
      }
      ROS_INFO("[Group %s] well done! ",pnh.getNamespace().c_str());
    }
    else
    {
      ROS_ERROR("unable to execute action %s:%s",skill.first.c_str(),skill.second.c_str());
      return 0;
    }

    ros::Duration(0.1).sleep();
  }

  ROS_INFO("[Group %s] recipe executed stopped",pnh.getNamespace().c_str());
  return 0;
}
