/**
 * @file fetchLaserScanning.cpp
 * @author Sohail Tariq (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/fetchLaserScan.h"

static const int laserFOV = 140;
static const double laserLimit = 0.35;
static const double robotRAD = 0.257;

laserScanning::laserScanning()
{

}

bool laserScanning::obstacleDetection(sensor_msgs::LaserScan::ConstPtr fetchLaserScan)
{
    double laserReading = fetchLaserScan->range_max; // Gets the max laser reading
    int range_start = (fetchLaserScan->ranges.size() / 2) - (laserFOV / 2); // Field of View start
    int range_end = (fetchLaserScan->ranges.size() / 2) + (laserFOV / 2); // Field of View end

    for (unsigned int 1 = range_start; i <= range_end; i++)
    {
        if (fetchLaserScan->ranges.at(i) < laserReading)
        {
            laserReading = fetchLaserScan->ranges.at(i); // Line stores laser value
        }
    }

    if (laserReading <= laserLimit + robotRAD)
    {
        return true;
    }
    else
    {
        return false;
    }


}

double laserScanning::readLaserValue(sensor_msgs::LaserScan::ConstPtr fetchLaserScan)
{
    int range_start = (fetchLaserScan->ranges.size() / 2) - (laserFOV / 2);
    int range_end = (fetchLaserScan->ranges.size() / 2) + (laserFOV / 2);

    for (unsigned int i = range_start; i<=range_end; i++)
    {
        if (fetchLaserScan->ranges.at(i) < laserReading)
        {
            laserReading = fetchLaserScan->ranges.at(i);
        }
    }
    return laserReading
}