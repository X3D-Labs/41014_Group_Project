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

#include <sensor_msgs/LaserScan.h>

class laserScanning
{
private:
    double laserReading; /*Stores data for laser values*/
public:

    laserScanning();

    bool obstacleDetection(sensor_msgs::LaserScan::ConstPtr fetchLaserScan);

    double readLaserValue(sensor_msgs::LaserScan::ConstPtr fetchLaserScan);
}  ;  

#endif //FETCHLASERSCAN_H