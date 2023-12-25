#ifndef ARMOR_PROCESSOR__PROCESSOR_NODE_HPP_
#define ARMOR_PROCESSOR__PROCESSOR_NODE_HPP_

// new_tracker.hpp
#include "rclcpp/rclcpp.hpp"
#include "auto_aim_interfaces/msg/armor.hpp"
#include "auto_aim_interfaces/msg/armors.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

//cv
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/video/tracking.hpp>


namespace rm_auto_aim {

class NewTrackerNode : public rclcpp::Node
{
public:
  explicit NewTrackerNode(const rclcpp::NodeOptions & options);

  using Armors = auto_aim_interfaces::msg::Armors;
  using Armor = auto_aim_interfaces::msg::Armor;
  
  struct CenterCoordinates {
  double x;
  double y;
  double z;
  } prediction_center;

  struct DeflectionAngle{
  double r_yaw;
  double r_pitch;
  double r_roll;
  } header_rotation_angle;

  Armor tracked_armor;

private:
  
  //函数
  void ArmorsCallback(const auto_aim_interfaces::msg::Armors::SharedPtr armors_msg);
  void FindNearestArmor(const Armors::SharedPtr & armors_msg);
  void CalculateKalmanFilter(double center_x,double center_y,double center_z);
  void FakeCalculateKalmanFilter(double center_x,double center_y,double center_z);
  void CalculateAngles(float x, float y, float z);
  //rcl变量
  rclcpp::Subscription<auto_aim_interfaces::msg::Armors>::SharedPtr armor_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr target_pub_;
  //甲板消息直接bind传递，不设置实变
  geometry_msgs::msg::Vector3 forecast_msg_;

  //一般变量
  
  //结构体变量
  
};

}  // namespace rm_auto_aim


#endif