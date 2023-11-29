#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"

#include <sensor_msgs/msg/camera_info.hpp>

using namespace cv;


class VideoPublisher : public rclcpp::Node
{
public:

    VideoPublisher() : Node("my_video_publisher")
    {
        image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/video_image_raw", rclcpp::SensorDataQoS().keep_last(10));

        cam_info_pub_ = this->create_publisher<sensor_msgs::msg::CameraInfo>("/camera_info", rclcpp::SensorDataQoS());

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(40),  // 25 frames per second
            std::bind(&VideoPublisher::publishVideoFrame, this));

        video_path_ = "/home/ghlins/test_video/红方前哨站公路视角半速.mp4";  // Replace with your video file path
        cap_.open(video_path_);


    }

private:
    void publishCameraInfo()
    {
        // 创建CameraInfo消息
        auto cam_info_msg = std::make_shared<sensor_msgs::msg::CameraInfo>();
        cam_info_msg->header.stamp = rclcpp::Clock().now();
        cam_info_msg->header.frame_id = "nocamera_frame";
        cam_info_msg->height = 1080;
        cam_info_msg->width = 1980;
        cam_info_msg->k = {1, 0, 990, 0, 1, 540, 0, 0, 1};  // 假设主点在图像中心，焦距为1
        cam_info_msg->d = {0 , 0 , 0 , 0 , 0};  // 假设没有畸变

        // 发布CameraInfo消息
        cam_info_pub_->publish(*cam_info_msg);
    }

    void publishVideoFrame()
    {
        cv::Mat frame;
        cap_ >> frame;

        std_msgs::msg::Header header;
        header.stamp = rclcpp::Clock().now();
        header.frame_id = "video_frame";

        publishCameraInfo();

        if (!frame.empty())
        {
            sensor_msgs::msg::Image msg = *cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
            image_pub_->publish(msg);
        }
    }
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr cam_info_pub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    std::string video_path_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto video_publisher = std::make_shared<VideoPublisher>();
    rclcpp::spin(video_publisher);
    rclcpp::shutdown();
    return 0;
}
