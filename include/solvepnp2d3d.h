#ifndef _SOLVEPNP2D3D_H
#define _SOLVEPNP2D3D_H
#define HALF_LENGTH 65
#include <ros/ros.h>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
#include <algorithm>
using namespace std;
using namespace cv;

class SubPuber
{
private:
    ros::NodeHandle nodeHandle;
    ros::Subscriber imgSub;
    ros::Publisher solvepnp2d3d;
    vector<Point2f> processImg(Mat rawImage);
    void solvePnP2_3(vector<Point2f> pnt2d, vector<Point3f> obj3d, Mat rVec, Mat tVec);
public:
    SubPuber()
    {
        imgSub = nodeHandle.subscribe("/camera/color/image_raw", 1, &SubPuber::solveTransform, this);
        solvepnp2d3d = nodeHandle.advertise<sensor_msgs::Image>("/solvepnp2d3d", 1);
    }
    void solveTransform(const sensor_msgs::ImageConstPtr &frontRGBImg)
    {
        Mat image;
        try
        {
            image = cv_bridge::toCvShare(frontRGBImg, "bgr8")->image;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert to image!");
            return;
        }
        vector<Point2f> point_in_2d = processImg(image);
        vector<Point3f> point_in_3d = vector<Point3f>{
            Point3f(-HALF_LENGTH, HALF_LENGTH, 0),
            Point3f(HALF_LENGTH, HALF_LENGTH, 0),
            Point3f(HALF_LENGTH, -HALF_LENGTH, 0),
            Point3f(-HALF_LENGTH, -HALF_LENGTH, 0)
        };
        Mat rVec = cv::Mat::zeros(3, 1, CV_64FC1);
        Mat tVec = cv::Mat::zeros(3, 1, CV_64FC1);
        if(!point_in_2d.empty()){
            solvePnP2_3(point_in_2d, point_in_3d, rVec, tVec);
        }
        //sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", image).toImageMsg();
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        solvepnp2d3d.publish(*msg);
    }
};

#endif