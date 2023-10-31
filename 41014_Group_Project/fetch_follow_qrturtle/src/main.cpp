/**
 * @file main.cpp
 * @author Sohail T. (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// Include header files
#include "ros/ros.h"
#include "../include/followTurtlebot.h"

#include <thread>

int main(int argc, char **argv) // Main function
{
    ros::init(argc, argv, "followTurtlebot");
    ros::NodeHandle nh;
    std::shared_ptr<followTurtlebot> robot(new followTurtlebot(nh));
    std::thread vel(&followTurtlebot::stopFetch, robot);
    ros::spin();

    ros::shutdown();

    vel.join();

    return 0;
}