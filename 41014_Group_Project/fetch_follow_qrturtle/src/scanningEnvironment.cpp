/**
 * @file scanningEnvironment.cpp
 * @author Sohail T. (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/scanEnvironment.h"

scanningEnvironment::scanningEnvironment(ros::NodeHandle nh) : nh_(nh)
{
    sub1_ = nh_.subscribe("/base_scan_raw", 10, &scanningEnvironment::CallBackLaser, this);
}

void scanningEnvironment::programStatus()
{
    while(ros::ok())
    {
        if (obstacle_detected_ == false)
        {
            ROS_INFO_STREAM("Wall Detected");
        }
        else
        {
            ROS_INFO_STREAM("Robot is Moving");
        }
    }

}

void scanningEnvironment::CallBackLaser(const sensor_msgs::LaserScanConstPtr &msg)
{
    obstacle_detected_ = laserDetecion_.obstacleDetetcion(msg);
    laser_readings_ = laserDetection_.readLaserValue(msg);

}