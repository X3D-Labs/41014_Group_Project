/**
 * @file followTurtlebot.cpp
 * @author Sohail T. (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/followTurtlebot.h"

followTurtlebot::followTurtlebot(ros::NodeHandle nh) 
    : nh_(nh)
{
    sub_marker_ = nh_.subscribe("/aruco_single/position", 1000, &followTurtlebot::CallBackMarker, this);
    sub_laser_= nh_.subscribe("/base_scan_raw", 100, &followTurtlebot::CallBackLaser, this);

    pub_vel_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    marker_.threshold_distance = 1.0 - marker_.head_2_base_offset;
    ROS_INFO_STREAM("Init");

    duration_ = start_time_ - start_time_; 

    sweep_complete_ = false;
    obstacle_reported_ = false;
    search_reported_ = false;
}

followTurtlebot::~followTurtlebot()
{
}

void followTurtlebot::CallBackMarker(const geometry_msgs::Vector3StampedPtr &msg)
{
    if (!marker_.detected) // Disp if turtlebot is detected
    {
        marker_.detected = true;
        search_reported_ = false;
        ROS_INFO_STREAM("Turtlebot Guider is Detected");
        sweep_complete_ = false;
    }

    marker_.pose.vector.x = msg->vector.z;
    marker_.pose.vector.y = msg->vector.x;
    marker_.pose.vector.z = msg->vector.y;

    marker_.shortest_dist = roundf64(sqrt(pow(marker_.pose.vector.x, 2) + pow(marker_.pose.vector.y, 2)) * 10) / 10;
    // Set dist between fetch and turtlebot to a value of 1 (0.01 = 1m)
    if (marker_.shortest_dist <= (marker_.threshold_distance + 0.01) && marker_.shortest_dist >= (marker_.threshold_distance - 0.01))
    {
        twistMsg_.linear.x = 0;
        twistMsg_.linear.z = 0;

        if (!marker_.reached)
        {
            ROS_INFO_STREAM("Turtlebot is stationary");
            marker_.reached = true;
        }
    }
    else
    {
        marker_.reached = false;
        if (!obstacle_detected_)
        {

            double error = marker_.shortest_dist - marker_.threshold_distance; // control logic for linear velocity
            // Move back or forward
            if (marker_.shortest_dist < marker_.threshold_distance * 1.5)
            {
                twistMsg_.linear.x = error;
            }
            else if (marker_.shortest_dist < marker_.threshold_distance * 0.95)
            {
                twistMsg_.linear.x = -0.3;
            }
            else
            {
                twistMsg_.linear.x = error / 2;
            }
            // left or right movements
            if (marker_.pose.vector.y == 0)
            {
                twistMsg_.angular.z = 0;
            }
            else
            {
                twistMsg_.angular.z = -marker_.pose.vector.y;
            }

            obstacle_reported_ = false;
        }
    }

    pub_vel_.publish(twistMsg_);

    start_time_ = ros::Time::now();
}

void followTurtlebot::CallBackLaser(const sensor_msgs::LaserScanConstPtr &msg)
{
    obstacle_detected_ = laserScanning_.obstacleDetection(msg);
    laser_readings_ = laserScanning_.readLaserValue(msg);

    if (obstacle_detected_)
    {
        if (marker_.detected)
        {
            if (!obstacle_reported_)
            {
                ROS_INFO_STREAM("Fetch has encountered obstacle and has stopped");
                obstacle_reported_ = true;
            }
            twistMsg_.angular.z = 0;
            twistMsg_.angular.x = 0;
        }
        else
        {
            if (!obstacle_reported_)
            {
                ROS_INFO_STREAM("Fetch has encountered obstacle");
                obstacle_reported_ = true;
            }
            twistMsg_.angular.z = 0;
            twistMsg_.angular.x = -2.0;
        }

        pub_vel_.publish(twistMsg_);
    }

    if (!obstacle_detected_)
    {
        obstacle_reported_ = false;
    }
}

void followTurtlebot::stopFetch()
{
    while (ros::ok)
    {
        if (duration_ > ros::Duration(25.0))
        {
            start_time_ = ros::Time::now();
        }
        duration_ = ros::Time::now() - start_time_;

        if (duration_ >= ros::Duration(2.0) && duration_ <= ros::Duration(8.0) && !marker_.detected && !sweep_complete_)
        {
            twistMsg_.angular.z = -1.50;
            twistMsg_.linear.x = 0.0;
            pub_vel_.publish(twistMsg_);
            if (!search_reported_)
            {
                ROS_INFO_STREAM("Searching for Turtlebot");
                search_reported_ = true;
            }
        }

        if (duration_ >= ros::Duration(8.0) && duration_ <= ros::Duration(14.0) && !marker_.detected && !sweep_complete_)
        {
            twistMsg_.angular.z = 1.50;
            twistMsg_.linear.x = 0.0;
            pub_vel_.publish(twistMsg_);
            
        }

        if (duration_ >= ros::Duration(2.5) && marker_.detected)
        {
            ROS_INFO_STREAM("Turtlebot is cannot be detected, Operation ceased");
            marker_.detected = false;
            sweep_complete_ = false;
            start_time_ = ros::Time::now();
        }
    }
}