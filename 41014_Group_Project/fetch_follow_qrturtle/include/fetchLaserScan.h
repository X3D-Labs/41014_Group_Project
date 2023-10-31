/**
 * @file fetchLaserScan.h
 * @author Sohail Tariq (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * Code for laser scanning for the Fetch robot
 * 
 */

#ifndef FETCHLASERSCAN_H 
#define FETCHLASERSCAN_H 

#include <sensor_msgs/LaserScan.h> // Include laser scan message

class laserScanning // Class for laser scanning
{
private:
    double laserReading; // Stores data for laser values
public:

    laserScanning(); // Constructor

    bool obstacleDetection(sensor_msgs::LaserScan::ConstPtr fetchLaserScan); // Function to detect obstacles

    double readLaserValue(sensor_msgs::LaserScan::ConstPtr fetchLaserScan); // Function to read laser values
}  ;  

#endif //FETCHLASERSCAN_H