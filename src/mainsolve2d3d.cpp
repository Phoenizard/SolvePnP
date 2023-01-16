#include <solvepnp2d3d.h>

// roslaunch realsense2_camera rs_camera.launch

int main(int argc, char **argv)
{
    ros::init(argc, argv, "solvepnp2d3d");
    ROS_INFO("Build Successfully");
    SubPuber solvepnp2d3d;
    ros::spin();
    return 0;
}
