![](./images/qtaichi.png)

### Qtaichi 是一个基于Taichi MLS-MPM方法与Qt GUI前端的自由绘图仿真系(玩)统(具)。

### 项目介绍请见知乎：[Taichi编程语言初探：太极之趣——自由绘制的2D冰雪仿真世界](https://zhuanlan.zhihu.com/p/139165414)

---

### 项目依赖

+ Qt5 相关lib (Qt5Core, Qt5GUI, Qt5Widgets)

---

### 安装方法

+ **方法一**（使用Qtaichi_installer一键安装，win x64系统推荐）：运行``./Qtaichi_installer/Release/setup.exe``即可！

+ **方法二**（从源码编译）：使用cmake三连：configure，generate，open project然后build（使用了@[Ubpa](https://github.com/Ubpa)的[UCMake](https://github.com/Ubpa/UCMake)工具）

---

### 使用介绍

+ 请见知乎文章。欢迎star或提任何issue！

---

### Update

+ 5/11/2020
  1. 修复了一些bug
  2. 增加了保存场景为图片的功能

---

### TODO

1. 对“固体”类型的材质的物理参数进行优化，使其在仿真中表现得更像固体。目前其仿真行为是具有一定弹性的硬度系数较大的材料。
2. 使用python重写Qtaichi并发布为python package（暑假）