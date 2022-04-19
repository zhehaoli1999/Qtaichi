# Qtaichi: Turn Drawing to Animation 

![](./images/qtaichi-all.png)

Qtaichi is a **real-time** simulator turning user drawing inputs to physics-based animations with moving least squares material point method based on ``taichi.h`` developed by @[Yuanming Hu](https://github.com/yuanming-hu). 
### Introduction Article (In Chinese) 中文介绍
[Taichi编程语言初探：太极之趣——自由绘制的2D冰雪仿真世界](https://zhuanlan.zhihu.com/p/139165414)



### Dependencies 

+ Qt5 libs (Qt5Core, Qt5GUI, Qt5Widgets)


### How to install 

+ **Method 1**(Recommand on Winx64)：

  Directly run ``./Qtaichi_installer/Release/setup.exe``. 

  If Chinese users meet problems with pulling this repo from github , you can try gitee：https://gitee.com/zhehaoli/Qtaichi

+ **Method 2**(Compile from source)：

  Use CMake to configure, generate, then open the project and finally build it. (Here I have used [UCMake](https://github.com/Ubpa/UCMake) From @[Ubpa](https://github.com/Ubpa), which is a extended wrapper of CMake.) You can also try directly using CMake by rewriting CMakeLists.txt. 



### How to play 

You can use the toolbar on GUI to: 
+ Draw basic geometries, like free curve, ecllipse, polygons.  
+ Select physical properties like fluid, solid, snow and jelly
+ Draw "velocity line" to give objects initial velocities 
+ Start, pause or reset animation 

![](./images/GUI.jpg)

### Demos 
1. Qtaichi 

    Shown in the teaser. 

2. Shoot a bullet towards snowman
  ![](./images/demo1.png)
  ![](./images/1.gif)

3. Water Spike 
  ![](./images/demo2.png)

4. Jelly Spike
  ![](./images/demo3.png)

5. Snowball fight 
  ![](./images/demo4.png)

### Update

+ 5/11/2020: Support saving scene to image

### Future work 

1. Add rigid body support 
2. Rewrite Qtaichi with taichi.py!