# mechax_auto_aim
零.5成品
## Version 2.0 \ 2023.12.25 22:37
第一版正常**框架**
以下说明：
#### 1.关于预测
预测```NewTrackerNode::CalculateKalmanFilter```存在问题，待修改。

检测代替使用的```NewTrackerNode::FakeCalculateKalmanFilter```就是直接传出参数，不做任何改变。
#### 2.运行启动
新增加启动三节点的launch.py，在bringup文件夹下。
```
source install/setup.bash
ros2 launch bringup Three.launch.py
```
#### 3.foxglove 可视化
```
foxglove-studio
source install/setup.bash
ros2 launch foxglove_bridge foxglove_bridge_launch.xml port:=8765
```
foxglove中open connection,为ws://localhost:8765。
wsl直接整，不需要```ip addr```
