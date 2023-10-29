/**
 * @file followTurtlebot.h
 * @author Sohail T. (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 *
 * @copyright Copyright (c) 2023
 *
 * Logic for fetch to follow the Turtlebot
 *
 */

#ifndef TURTLEBOT_FOLLOW_H
#define TURTLEBOT_FOLLOW_H

#include <chrono>
#include <vector>
#include <cmath>
#include "ros/ros.h"
#include "fetchLaserScan.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "tf2_msgs/TFMessage.h"

class followTurtlebot
{
private:
    ros::NodeHandle nh_;

    ros::Publisher pub_vel_;
    ros::Subscriber sub_marker_;
    ros::Subscriber sub_laser_;
    geometry_msgs::Twist twistMsg_;
    ros::Subscriber pose_tracker_;
    ros::Time start_time_;
    ros::Duration duration_;

    laserScanning laserScanning_;

    double laser_readings_;
    bool obstacle_detected_;
    bool obstacle_reported_;
    bool search_reported_;
    bool sweep_complete_;
    tf2_msgs::TFMessageConstPtr pose_fetch_;

    struct Marker
    {
        geometry_msgs::Vector3Stamped pose;
        double threshold_distance;
        const double head_2_base_offset = 0.1088;
        double shortest_dist;
        bool detected;
        bool reached;
    };

    Marker marker_;

    public : 
    
    followTurtlebot(ros::NodeHandle nh);
    ~followTurtlebot();
    void stopFetch();
    void CallBackLaser(const sensor_msgs::LaserScanConstPtr &msg);
    void CallBackMarker(const geometry_msgs::Vector3StampedPtr &msg);
};

#endif //TURTLEBOT_FOLLOW_H