## SolvePnP

### 项目描述

本项目是对PnP算法的实际运用。通过识别二维码，
求出相机与二维码的相对位置
详细请参考我的个人博客：

http://www.phzd39jk.online/2023/01/14/solvePnP/

### 使用方法
此项目为ROS软件包形式，如需使用，请复制到工作空间下的
src文件夹中，运行以下代码完成编译，并且添加环境变量：

```commandline
cd ~/{workspace_name}
catkin_make
```


使用时需要配合realsense的ROS包：
```commandline
roslaunch realsense2_camera rs_camera.launch
rosrun object-camera-transform solvepnp2d3d
rviz
```


识别到的二维码轮廓将在rviz中出现，终端输出相机相对二维码位姿（旋转与平移向量）
