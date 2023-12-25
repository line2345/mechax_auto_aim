#include "new_tracker/new_tracker_node.hpp"

// STD 
#include <memory>
#include <vector>
#include <cmath>

using std::placeholders::_1;

namespace rm_auto_aim {

NewTrackerNode::NewTrackerNode(const rclcpp::NodeOptions & options) : Node("new_tracker", options)
{
  RCLCPP_INFO(this->get_logger(), "Starting NewTrackerNode!");

  //原甲板消息订阅
  armor_sub_ = this->create_subscription<auto_aim_interfaces::msg::Armors>(
    "/detector/armors", rclcpp::SensorDataQoS(), std::bind(&NewTrackerNode::ArmorsCallback, this, std::placeholders::_1));

  //中心坐标发布
  target_pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("simple_tracked_coordinates", 10);
  
}

void NewTrackerNode::ArmorsCallback(const auto_aim_interfaces::msg::Armors::SharedPtr armors_msg)
{
  FindNearestArmor(armors_msg);
  //TO DO
  FakeCalculateKalmanFilter(tracked_armor.pose.position.x , tracked_armor.pose.position.y , tracked_armor.pose.position.z);
  //to do
  CalculateAngles(prediction_center.x, prediction_center.y, prediction_center.z);
  
  forecast_msg_.x = prediction_center.x;
  forecast_msg_.y = prediction_center.y;
  forecast_msg_.z = prediction_center.x;

  target_pub_->publish(forecast_msg_);
}

void NewTrackerNode::FindNearestArmor(const Armors::SharedPtr & armors_msg) 
{
  if (armors_msg->armors.empty()) {
    return;
  }
  double min_distance = 9999999;
  tracked_armor = armors_msg->armors[0];
  for (const auto & armor : armors_msg->armors) {
    if (armor.distance_to_image_center < min_distance) {
      min_distance = armor.distance_to_image_center;
      tracked_armor = armor;
    }
  }
}

void NewTrackerNode::CalculateKalmanFilter(double center_x,double center_y,double center_z)
	{
    cv::Mat measurement;
    int stateNum=6;
    int measureNum=3;

    cv::KalmanFilter KF(stateNum,measureNum,0);
    
    measurement=cv::Mat::zeros(measureNum,1,CV_32F);
    KF.transitionMatrix = (cv::Mat_<float>(stateNum, stateNum));
    setIdentity(KF.measurementMatrix);
    setIdentity(KF.processNoiseCov , cv::Scalar::all(1e-5));
    setIdentity(KF.measurementNoiseCov,cv::Scalar::all(1e-1));
    setIdentity(KF.errorCovPost , cv::Scalar::all(1));
    randn(KF.statePost , cv::Scalar::all(0), cv::Scalar::all(0.1));
    cv::Mat prediction = KF.predict();
    // cv::Point3f predict_pt=cv::Point3f((int)prediction.at<float>(0),(int)prediction.at<float>(1),(int)prediction.at<float>(2));
    measurement.at<float>(0) = (float)center_x;
    measurement.at<float>(1) = (float)center_y;
    measurement.at<float>(2) = (float)center_z;
    KF.correct(measurement);
    center_x=(int)prediction.at<float>(0);
    center_y=(int)prediction.at<float>(1);
    center_z=(int)prediction.at<float>(2);

    prediction_center.x=center_x;
    prediction_center.y=center_y;
    prediction_center.z=center_z;
	}
void NewTrackerNode::FakeCalculateKalmanFilter(double center_x,double center_y,double center_z)
{
  prediction_center.x=center_x;
  prediction_center.y=center_y;
  prediction_center.z=center_z;
}

void NewTrackerNode::CalculateAngles(float x, float y, float z)
{
  // 对于给定的x, y, z, 计算yaw(偏航角), pitch(俯仰角) and roll(滚转角)
  double yaw_, pitch_, roll_;
  double distance = std::sqrt(x * x + y * y + z * z);
  // 偏航角：绕Y轴旋转
  yaw_ = std::atan2(x, z);
  // 俯仰角：绕X轴旋转
  pitch_ = std::asin(y / distance);
  // 滚转角：绕Z轴旋转
  roll_ = std::atan2(y, x);

  // 把角度转换成度数
  header_rotation_angle.r_yaw = yaw_ * 180 / M_PI;
  header_rotation_angle.r_pitch = pitch_ * 180 / M_PI;
  header_rotation_angle.r_roll = roll_ * 180 / M_PI;


}  // namespace rm_auto_aim
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rm_auto_aim::NewTrackerNode)