

==**This is just miscellaneous notes.**== 

# Catkin workspace structure 

![catkin_workspace](https://miro.medium.com/v2/resize:fit:1400/format:webp/0*vfNM1mbkhUpvK-nW.png)

In the above diagram, it can be seen that there are **four different *spaces***.

1. **Source Space**:
 The source space contains the **source code of catkin packages**. This is where you can extract/checkout/clone source code for the packages you want to build. Each folder within the **source space contains one or more catkin packages and each package has its set of ROS Computational Graph components**. The root of the source space contains a symbolic link to catkin’s boiler-plate ‘toplevel’ _CMakeLists.txt_ file. This file is invoked by CMake during the configuration of the catkin projects in the workspace. It can be created by calling **catkin_init_workspace** in the source space directory. [(Medium.com, n.d.)](https://medium.com/swlh/7-simple-steps-to-create-and-build-our-first-ros-package-7e3080d36faa)

3. **Build Space**: The build space is where CMake is invoked to build the _catkin_ packages in the source space. _CMake_ and _catkin_ keep their cache information and other intermediate files here.

4. **Development Space**: The development space (or _devel_ space) is where built targets are placed prior to being installed. The way targets are organized in the _devel_ space is the same as their layout when they are installed. This provides a useful testing and development environment which does not require invoking the installation step.

5. **Install Space**: Once the targets are built, they can be installed into the _install_ space by invoking the install target, usually with make install. The _install_ space does not have to be contained within the workspace.

 