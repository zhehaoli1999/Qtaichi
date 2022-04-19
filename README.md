# Qtaichi: Turn Drawing to Animation 

![](./images/qtaichi-all.png)

Qtaichi is a **real-time** simulator turning user drawing inputs to physics-based animations with Moving Least Squares Material Point Method based on ``taichi.h`` developed by [Yuanming Hu](https://github.com/yuanming-hu). 

> "Qtaichi" is the combination of "Qt & taichi".  

Written in C++ by Zhehao Li as a homework on computer graphics course taught by Prof. Ligang Liu at USTC. 


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

1. **Qtaichi** 

  Shown in the teaser. 

  | Drawing                           | Particle                                               | Animation                 |
  | --------------------------------- | ------------------------------------------------------ | ------------------------- |
  | <img src="./images/demo0.png"  /> | <img src="./images/demo0-1.png" style="zoom: 200%;" /> | ![](./images/demo0-2.png) |

  

2. **Shoot a bullet towards snowman**

  | Drawing                           | Particle                                              | Animation                           |
  | --------------------------------- | ----------------------------------------------------- | ----------------------------------- |
  | <img src="./images/demo1.png"  /> | <img src="./images/demo1-1.png" style="zoom: 67%;" /> | <img src="./images/demo1-2.png"  /> |



3. **Water Spike** 

  | Drawing                           | Particle                                              | Animation                           |
  | --------------------------------- | ----------------------------------------------------- | ----------------------------------- |
  | <img src="./images/demo2.png"  /> | <img src="./images/demo2-1.png" style="zoom:120%;" /> | <img src="./images/demo2-2.png"  /> |

  

4. **Jelly Spike**

  | Drawing                                             | Particle                                               | Animation                                             |
  | --------------------------------------------------- | ------------------------------------------------------ | ----------------------------------------------------- |
  | <img src="./images/demo3.png" style="zoom:130%;" /> | <img src="./images/demo3-1.png" style="zoom: 130%;" /> | <img src="./images/demo3-2.png" style="zoom: 80%;" /> |

    

5. **Snowball fight** 

  | Particle                                              | Drawing                                            | Animation                                             |
  | ----------------------------------------------------- | -------------------------------------------------- | ----------------------------------------------------- |
  | <img src="./images/demo4-1.png" style="zoom:150%;" /> | <img src="./images/demo4.png" style="zoom:80%;" /> | <img src="./images/demo4-2.png" style="zoom:130%;" /> |



6. **We also try to reproduce one result in SIGGRAPH13 MPM paper:**

  | SIGGRAPH13 MPM                                      | Our Corresponding Results                          |
  | --------------------------------------------------- | -------------------------------------------------- |
  | <img src="./images/sig0.jpg" style="zoom: 120%;" /> | <img src="./images/sig.jpg" style="zoom: 110%;" /> |

  

7. **Other user drawings** 

  | <img src="./images/demo6-0.png" style="zoom: 33%;" /> | <img src="./images/demo6-1.png" style="zoom: 33%;" /> |
  | ----------------------------------------------------- | ----------------------------------------------------- |
  | <img src="./images/demo7-0.png" style="zoom: 33%;" /> | <img src="./images/demo7-1.png" style="zoom: 33%;" /> |

  

### Update

+ 5/11/2020: Support saving scene to image

### Future work 

1. Add rigid body support 
2. Rewrite Qtaichi with taichi.py!
