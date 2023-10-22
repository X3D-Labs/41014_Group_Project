/**
 * @file turtlebotControl.h
 * @author Sohail T. (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INCLUDE_TURTLEBOTCONTROL_H_
#define INCLUDE_TURTLEBOTCONTROL_H_

#include "ros/ros.h"
#include <thread>
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float64.h"

class TurtlebotControl
{
    public:

        TurtlebotControl(ros::NodeHandle nh);
        ~TurtlebotControl();

        void CallBackJoy(const sensor_msgs::JoyPtr &msg);
        void publishVelocity();

    private:

    ros::NodeHandle nh_;

    ros::Subscriber sub_joy_;
    ros::Publisher pub_vel_;
    geometry_msgs::Twist twistMsg_;

}



#endif //INCLUDE_TURTLEBOTCONTROL_H_ 