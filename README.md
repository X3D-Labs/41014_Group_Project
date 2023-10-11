# 41014 Group Project: Fetch Robot Following the Path


| Student | Student ID|
|-------|-------|
|Sohail Tariq |13206901|
|Lachlan Torres |13454881|
|Doug Griffith| 13557121|

## Introduction

The objective of this project is to design and implement a functioning robot operating system that uses the learnt state of control algorithms, RGB images, and depth imaging data, to command our fetch robot to follow a path. Our vision of success entails having a robot that is able to navigate a path in an office/corridor environment that can take inputs from artificial markers or patterns on the guider to ensure our fetchbot a swift and efficient traversal.

## Scope

The project proposes a multitude of tasks and presentation processes. That the team will deliver on to, design and create function code to, command a fetch robot to follow a path. Therefore, the scope of the project is as follows.


1. Calibrate the Fetch Robots cameras to gain the robots perspective from the guider 
2. Use Data from the Robots RGB, and depth images for feedback 
3. Develop and implement code that utilises the Robots Hardware to follow a path 
4. Create a video demonstration, outlining what the project has achieved  
5. Project teaser demo outlining the successes/mistakes observed when operating the robot 
6. Q and A video

## Deliverables

[For README brevity, the deliverables and deadlines can be found here](<Group Project Deliverables>)


## MATLAB, Python and ROS

This project will primarily use Python and MATLAB for computing, and ROS for all simulations. 

[Follow the ROS installation guide here](<>)
[Follow the Python Install Guide here](<>)


### ROS Launch Files

Once ROS has been installed, the user can run the launch files by inputting 

`roslaunch 41014_Group_Project basic.launch
for the low-intensity simulation environment
**or**

`roslaunch 41014_Group_Project detailed.launch`

for a more detailed and realistic simulation environment

This will launch our group's Fetch Simulation. 