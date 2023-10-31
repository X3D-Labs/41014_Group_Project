# 41014 Group Project: Fetch Robot Following the Path


| Student | Student ID|
|-------|-------|
|Sohail Tariq |13206901|
|Lachlan Torres |13454881|
|Doug Griffith| 13557121|

## Introduction

The objective of this project is to design and implement a functioning robot operating system that uses the learnt state of control algorithms, RGB images, and depth imaging data, to command our fetch robot to follow a path. Our vision of success entails having a robot that is able to navigate a path in an office/corridor environment that can take inputs from artificial markers or patterns on the guider to ensure our fetchbot a swift and efficient traversal.


## Install and use

### Dependencies


#### Fetch & Turtlebot packages

This package relies on the use of the fetch and turtle bot robots. to install their packages, input the below:

```
cd ~/catkin_ws/src/  
git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git  
git clone https://github.com/ROBOTIS-GIT/turtlebot3.git  
git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git  
cd ~/catkin_ws  
catkin_make  
source devel/setup.bash
```
  for the turtlebot, and 

```
cd ~/catkin_ws/src/  
git clone https://github.com/fetchrobotics/fetch_gazebo.git  
cd ~/catkin_ws  
catkin_make  
source devel/setup.bash
```

for the fetch.
#### Aruco package

As this package uses Aruco markers, you must install the aruco_ros package.
to do this, input the below commands into a terminal.

``` 
	cd ~/catkin_ws/src
	git clone -b melodic-devel https://github.com/pal-robotics/aruco_ros.git
	catkin_make
	source devel/setup.bash
```


#### other dependencies

During initialisation, you may find that the fetch teleoperation does not work. in that case, it may be a good idea to download the fetch gazebo package:

`sudo apt-get install ros-melodic-fetch-gazebo-demo

It may also be a good idea to download the vision packages so that you can visualise the collision detection system in action:

`sudo apt-get install ros-melodic-rviz`


#### This Package

To install the package, just download this straight from github and slap it into your src file. once that is done, you can run:

```
	cd ~/catkin_ws/src
	catkin_make
	source devel/setup.bash
```
### Operation

Once the package has been installed, the user can run the launch files by inputting 

`roslaunch fetch_follow_qrturtle basic.launch

to run the follower code, you must run the follow_tbot launch file in a separate window. 
`roslaunch fetch_follow_qrturtle follow_tbot.launch`

This will launch our group's Fetch Simulation. You can also input
```
	cd ~/catkin_ws/src
	rosrun rviz rviz -d fetch_follow_qrturtle/rviz/rviz_fetch.rviz
```


#