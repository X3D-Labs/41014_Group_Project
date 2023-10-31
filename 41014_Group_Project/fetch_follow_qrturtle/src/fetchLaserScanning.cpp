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

#include "../include/fetchLaserScan.h" //Includes the header file

static const int laserFOV = 140; //Sets the field of view of the laser
static const double laserLimit = 0.35; //Sets the limit of the laser
static const double robotRAD = 0.257; //Sets the radius of the robot

laserScanning::laserScanning() //Constructor
{

}

bool laserScanning::obstacleDetection(sensor_msgs::LaserScan::ConstPtr fetchLaserScan) //Checks if there is an obstacle in front of the robot
{
    double laserReading = fetchLaserScan->range_max; // Gets the max laser reading
    int range_start = (fetchLaserScan->ranges.size() / 2) - (laserFOV / 2); // Field of View start
    int range_end = (fetchLaserScan->ranges.size() / 2) + (laserFOV / 2); // Field of View end

    for (unsigned int i = range_start; i <= range_end; i++) // Loops through the field of view
    {
        if (fetchLaserScan->ranges.at(i) < laserReading) // Checks if the laser reading is less than the current laser reading
        {
            laserReading = fetchLaserScan->ranges.at(i); // Line stores laser value
        }
    }

    if (laserReading <= laserLimit + robotRAD) // Checks if the laser reading is less than the limit + radius of the robot
    {
        return true;
    }
    else
    {
        return false;
    }


}

double laserScanning::readLaserValue(sensor_msgs::LaserScan::ConstPtr fetchLaserScan) // Reads the laser value
{
    int range_start = (fetchLaserScan->ranges.size() / 2) - (laserFOV / 2); // Field of View start
    int range_end = (fetchLaserScan->ranges.size() / 2) + (laserFOV / 2); // Field of View end

    for (unsigned int i = range_start; i<=range_end; i++) // Loops through the field of view
    {
        if (fetchLaserScan->ranges.at(i) < laserReading) // Checks if the laser reading is less than the current laser reading
        {
            laserReading = fetchLaserScan->ranges.at(i);
        }
    }
    return laserReading;
}