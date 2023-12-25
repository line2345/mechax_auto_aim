from launch import LaunchDescription
from launch_ros.actions import Node
 
def generate_launch_description():
    return LaunchDescription([
        Node(
            package='armor_detector',
            executable='armor_detector_node',
            name='armor_detector'
        ),
        Node(
            package='new_armor_tracker',
            executable='new_armor_tracker_node',
            name='new_armor_tracker'
        ),
        Node(
            package='my_ros2_opencv_pkg',
            executable='my_video_publisher',
            name='my_video_publisher'
        )
    ])