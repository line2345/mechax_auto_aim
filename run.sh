#!/bin/bash

# chmod +x run.sh
# ./run.sh

# 新打开一个终端，source install/setup.bash, ros2 run mypacket mtyonode
gnome-terminal -- bash -c "rm -rf build/; \
colcon build & wait;\
source install/setup.bash;\
ros2 run armor_detector armor_detector_node"
# 等待开启的终端执行完毕
sleep 1

# 新打开一个终端，source install/setup.bash
gnome-terminal -- bash -c "source install/setup.bash;\
ros2 run new_armor_tracker new_armor_tracker_node"

gnome-terminal -- bash -c "source install/setup.bash;\
ros2 run my_ros2_opencv_pkg my_video_publisher"

gnome-terminal -- bash -c "source install/setup.bash;\
timeout 15s ros2 bag record /simple_tracked_coordinates;\
sleep 2s;mv rosbag2* record"


