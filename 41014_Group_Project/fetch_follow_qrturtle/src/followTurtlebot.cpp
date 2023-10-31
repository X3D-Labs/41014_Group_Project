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

#include "../include/followTurtlebot.h" // Include header file

followTurtlebot::followTurtlebot(ros::NodeHandle nh) // Constructor
    : nh_(nh)
{
    sub_marker_ = nh_.subscribe("/aruco_single/position", 1000, &followTurtlebot::CallBackMarker, this); // Subscribe to the marker topic
    sub_laser_= nh_.subscribe("/base_scan_raw", 100, &followTurtlebot::CallBackLaser, this); // Subscribe to the laser topic

    pub_vel_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1); // Publish to the velocity topic

    marker_.threshold_distance = 1.0 - marker_.head_2_base_offset; // Set the threshold distance
    ROS_INFO_STREAM("Init"); // Display init message

    duration_ = start_time_ - start_time_; // Set duration to 0

    sweep_complete_ = false; // Set sweep complete to false
    obstacle_reported_ = false; // Set obstacle reported to false
    search_reported_ = false; // Set search reported to false
}

followTurtlebot::~followTurtlebot() // Destructor
{
}

void followTurtlebot::CallBackMarker(const geometry_msgs::Vector3StampedPtr &msg) // Callback function for the marker
{
    if (!marker_.detected) // Disp if turtlebot is detected
    {
        marker_.detected = true;
        search_reported_ = false;
        ROS_INFO_STREAM("Turtlebot Guider is Detected");
        sweep_complete_ = false;
    }

    marker_.pose.vector.x = msg->vector.z; // 
    marker_.pose.vector.y = msg->vector.x; // Set the pose of the marker
    marker_.pose.vector.z = msg->vector.y; //

    marker_.shortest_dist = roundf64(sqrt(pow(marker_.pose.vector.x, 2) + pow(marker_.pose.vector.y, 2)) * 10) / 10; // Set dist between fetch and turtlebot to a value of 1 (0.01 = 1m)
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
    else // If the turtlebot is not at the threshold distance
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

    pub_vel_.publish(twistMsg_); // Publish the velocity message

    start_time_ = ros::Time::now(); // Set the start time
}

void followTurtlebot::CallBackLaser(const sensor_msgs::LaserScanConstPtr &msg) // Callback function for the laser
{
    obstacle_detected_ = laserScanning_.obstacleDetection(msg); // Check if there is an obstacle
    laser_readings_ = laserScanning_.readLaserValue(msg); // Read the laser value

    if (obstacle_detected_) // If there is an obstacle
    {
        if (marker_.detected)
        {
            if (!obstacle_reported_) // If the obstacle has not been reported
            {
                ROS_INFO_STREAM("Fetch has encountered obstacle and has stopped");
                obstacle_reported_ = true;
            }
            twistMsg_.angular.z = 0;
            twistMsg_.angular.x = 0;
        }
        else // If the turtlebot is not detected
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

    if (!obstacle_detected_) //
    {
        obstacle_reported_ = false;
    }
}

void followTurtlebot::stopFetch() // Stop the fetch robot
{
    while (ros::ok) // while ROS runs
    {
        if (duration_ > ros::Duration(25.0)) //
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