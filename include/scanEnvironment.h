/**
 * @file scanEnvironment.h
 * @author Sohail T. (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SCAN_ENVIRONMENT_H
#define SCAN_ENVIRONMENT_H

#include <chrono>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <atomic>
#include <random>
#include <mutex>
#include <deque>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include "fetchLaserScan.h"

class scanningEnvironment
{
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub1_;
    double laser_readings_;
    bool obstacle_detected_;
    void CallBackLaser(const sensor_msgs::LaserScanConstPtr &);
public:
    
    laserScanning laserScanning_;
    scanningEnvironment(ros::NodeHandle);
    void programStatus();

};


#endif //SCAN_ENVIRONMENT_H
