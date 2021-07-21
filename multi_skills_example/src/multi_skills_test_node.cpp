#include <tuple>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <manipulation_msgs/PickObjectsAction.h>
#include <manipulation_msgs/PlaceObjectsAction.h>
#include <manipulation_msgs/GoToAction.h>
#include <manipulation_msgs/RemoveObjectFromSlot.h>

#include <moveit/move_group_interface/move_group_interface.h>

#include <rosparam_utilities/rosparam_utilities.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "multi_skills");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ros::AsyncSpinner spinner(4);
  spinner.start();

  std::string group_name = "ur5";
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

  ros::ServiceClient remove_object_from_slot_clnt = nh.serviceClient<manipulation_msgs::RemoveObjectFromSlot>("/outbound_place_server/remove_obj_from_slot");
  remove_object_from_slot_clnt.waitForExistence();

  std::vector<std::tuple<std::string, // action 
              std::vector<std::string>, // description
              std::string, // approach_loc_ctrl_id
              std::string, // to_loc_ctrl_id
              std::string, // leave_loc_ctrl_id
              std::string, // tool_id
              std::string, // job_exec_name
              std::string, // property_pre_exec_id
              std::string, // property_exec_id
              std::string>> // property_post_exec_id
              recipe;

  XmlRpc::XmlRpcValue param;
  if (!pnh.getParam("recipe",param))
  {
    ROS_ERROR("Node %s has not a parameter named recipe",pnh.getNamespace().c_str());
    return -1;
  }

  if (param.getType() != XmlRpc::XmlRpcValue::TypeArray)
  {
    ROS_ERROR("Recipe is not a list" );
    return -1;
  }

  for(int i=0; i<param.size(); i++)
  {
    std::tuple< std::string, // action 
                std::vector<std::string>, // description
                std::string, // approach_loc_ctrl_id
                std::string, // to_loc_ctrl_id
                std::string, // leave_loc_ctrl_id
                std::string, // job_exec_name
                std::string, // tool_id
                std::string, // property_pre_exec_id
                std::string, // property_exec_id
                std::string> // property_post_exec_id
                sigle_skill; 
    XmlRpc::XmlRpcValue config = param[i];
    if( config.getType() != XmlRpc::XmlRpcValue::TypeStruct)
    {
      ROS_WARN("The element #%zu is not a struct", i);
      continue;
    }

    if( !config.hasMember("action") )
    {
      ROS_WARN("The element #%zu has not the field 'action'", i);
      continue;
    }
    std::string action = rosparam_utilities::toString(config["action"]);  
    
    if( !config.hasMember("description") )
    {
      ROS_WARN("The element #%zu has not the field 'description'", i);
      continue;
    }

    std::string what;
    std::vector<std::string> description;
    if( !rosparam_utilities::getParam(config,"description",description,what) )
    {
      ROS_WARN("The element #%zu has not the field 'description'", i);
      continue;
    }

    std::string approach_loc_ctrl_id;
    if( !config.hasMember("approach_loc_ctrl_id") )
    {
      ROS_WARN("The element #%zu has not the field 'approach_loc_ctrl_id'", i);
      approach_loc_ctrl_id = "";
    }
    else
    {
      approach_loc_ctrl_id = rosparam_utilities::toString(config["approach_loc_ctrl_id"]);  
    }

    std::string to_loc_ctrl_id;
    if( !config.hasMember("to_loc_ctrl_id") )
    {
      ROS_WARN("The element #%zu has not the field 'to_loc_ctrl_id'", i);
      to_loc_ctrl_id = "";
    }
    else
    {
      to_loc_ctrl_id = rosparam_utilities::toString(config["to_loc_ctrl_id"]);  
    }

    std::string leave_loc_ctrl_id;
    if( !config.hasMember("leave_loc_ctrl_id") )
    {
      ROS_WARN("The element #%zu has not the field 'leave_loc_ctrl_id'", i);
      leave_loc_ctrl_id = "";
    }
    else
    {
      leave_loc_ctrl_id = rosparam_utilities::toString(config["leave_loc_ctrl_id"]);  
    }

    std::string job_exec_name;
    if( !config.hasMember("job_exec_name") )
    {
      ROS_WARN("The element #%zu has not the field 'job_exec_name'", i);
      job_exec_name = "";
    }
    else
    {
      job_exec_name = rosparam_utilities::toString(config["job_exec_name"]);  
    }

    std::string tool_id;
    if( !config.hasMember("tool_id") )
    {
      ROS_WARN("The element #%zu has not the field 'tool_id'", i);
      tool_id = "";
    }
    else
    {
      tool_id = rosparam_utilities::toString(config["tool_id"]);  
    }

    std::string property_pre_exec_id;
    if( !config.hasMember("property_pre_exec_id") )
    {
      ROS_WARN("The element #%zu has not the field 'property_pre_exec_id'", i);
      property_pre_exec_id = "";
    }
    else
    {
      property_pre_exec_id = rosparam_utilities::toString(config["property_pre_exec_id"]);  
    }

    std::string property_exec_id;  
    if( !config.hasMember("property_exec_id") )
    {
      ROS_WARN("The element #%zu has not the field 'property_exec_id'", i);
      property_exec_id = "";
    }
    else
    {
      property_exec_id = rosparam_utilities::toString(config["property_exec_id"]);  
    }

    std::string property_post_exec_id;
    if( !config.hasMember("property_post_exec_id") )
    {
      ROS_WARN("The element #%zu has not the field 'property_post_exec_id'", i);
      property_post_exec_id = "";
    }
    else
    {
      property_post_exec_id = rosparam_utilities::toString(config["property_post_exec_id"]);  
    }

    sigle_skill = make_tuple( action, 
                              description,
                              approach_loc_ctrl_id,
                              to_loc_ctrl_id,
                              leave_loc_ctrl_id, 
                              job_exec_name,
                              tool_id, 
                              property_pre_exec_id, 
                              property_exec_id, 
                              property_post_exec_id);  

    recipe.push_back(sigle_skill);
  }

  manipulation_msgs::RemoveObjectFromSlot remove_object_from_slot;

  for (const std::tuple<std::string, 
                        std::vector<std::string>, 
                        std::string, 
                        std::string, 
                        std::string,
                        std::string, 
                        std::string,
                        std::string, 
                        std::string, 
                        std::string>& skill: recipe)
  {
    ROS_INFO("skill -> %s",std::get<0>(skill).c_str());

    if (std::get<0>(skill).compare("pick")==0)
    {
      manipulation_msgs::PickObjectsGoal pick_goal;

      for (const std::string& object_type: std::get<1>(skill))
      {
        ROS_INFO("[Group %s] Goal: pick object %s",pnh.getNamespace().c_str(),object_type.c_str());
        pick_goal.object_types.push_back(object_type);
      }

      pick_goal.approach_loc_ctrl_id = std::get<2>(skill);
      pick_goal.to_loc_ctrl_id = std::get<3>(skill);
      pick_goal.leave_loc_ctrl_id = std::get<4>(skill);

      pick_goal.job_exec_name = std::get<5>(skill);;
      pick_goal.tool_id = std::get<6>(skill);
      pick_goal.property_pre_exec_id = std::get<7>(skill);
      pick_goal.property_exec_id = std::get<8>(skill);
      pick_goal.property_post_exec_id = std::get<9>(skill);

      pick_ac.sendGoalAndWait(pick_goal);

      if (pick_ac.getResult()->result < 0)
      {
        ROS_ERROR("[Group %s] unable to pick -> object type = %s",pnh.getNamespace().c_str(),pick_ac.getResult()->object_name.c_str());
        return 0;
      }
      ROS_INFO("[Group %s] well done! I picked it, name = %s",pnh.getNamespace().c_str(),pick_ac.getResult()->object_name.c_str());
    }
    else if (std::get<0>(skill).compare("place")==0)
    {
      manipulation_msgs::PlaceObjectsGoal place_goal;

      for (const std::string& slot: std::get<1>(skill))
      {
        ROS_INFO("[Group %s] Goal: place object %s in slot %s",pnh.getNamespace().c_str(),place_goal.object_name.c_str(), slot.c_str());
        place_goal.slots_group_names.push_back(slot);  
      }

      if (!pick_ac.getResult()->object_name.empty())
        place_goal.object_name = pick_ac.getResult()->object_name;
      else
      {
        ROS_ERROR("[Group %s] no object name = %s",pnh.getNamespace().c_str(),pick_ac.getResult()->object_name.c_str());
        return 0;
      }

      place_goal.approach_loc_ctrl_id = std::get<2>(skill);
      place_goal.to_loc_ctrl_id = std::get<3>(skill);
      place_goal.leave_loc_ctrl_id = std::get<4>(skill);

      place_goal.job_exec_name = std::get<5>(skill);;
      place_goal.tool_id = std::get<6>(skill);
      place_goal.property_pre_exec_id = std::get<7>(skill);
      place_goal.property_exec_id = std::get<8>(skill);
      place_goal.property_post_exec_id = std::get<9>(skill);

      place_ac.sendGoalAndWait(place_goal);

      if (place_ac.getResult()->result < 0)
      {
        ROS_ERROR("[Group %s] unable to place -> object name = %s",pnh.getNamespace().c_str(), place_goal.object_name.c_str());
        return 0;
      }

      // Simulate slot cleaning
      remove_object_from_slot.request.object_to_remove_name = pick_ac.getResult()->object_name;
      remove_object_from_slot.request.slot_name = place_ac.getResult()->slot_name;

      if (!remove_object_from_slot_clnt.call(remove_object_from_slot))
      {
        ROS_ERROR("Unespected error calling %s service",remove_object_from_slot_clnt.getService().c_str());
        return 0;
      }

      ROS_INFO("[Group %s] well done! ",pnh.getNamespace().c_str());

    }
    else if (std::get<0>(skill).compare("goto")==0)
    {
      manipulation_msgs::GoToGoal go_to_goal;

      if (std::get<1>(skill).size() > 0)
        ROS_INFO("[Group %s] Goal: Go to %s",pnh.getNamespace().c_str(),std::get<1>(skill).at(0).c_str());
      
      go_to_goal.location_names.push_back( std::get<1>(skill).at(0) );

      go_to_goal.to_loc_ctrl_id = std::get<3>(skill);

      go_to_goal.job_exec_name = std::get<5>(skill);
      go_to_goal.tool_id = std::get<6>(skill);
      go_to_goal.property_exec_id = std::get<8>(skill);

      go_to_ac.sendGoalAndWait(go_to_goal);

      if (go_to_ac.getResult()->result < 0)
      {
        ROS_ERROR("[Group %s] unable to go to -> location name = %s",pnh.getNamespace().c_str(), go_to_goal.location_names.at(0).c_str());
        return 0;
      }
      ROS_INFO("[Group %s] well done! ",pnh.getNamespace().c_str());
    }
    else
    {
      ROS_ERROR("unable to execute action %s",std::get<0>(skill).c_str());
      return 0;
    }

    ros::Duration(0.1).sleep();
  }

  ROS_INFO("[Group %s] recipe executed stopped",pnh.getNamespace().c_str());
  return 0;
}
