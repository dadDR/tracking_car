# tracking_car
tracking_car is a program that simulates a camera car's line-tracking, developed using QT C++ ||  tracking_car 是一个模拟摄像头小车巡线的程序，使用QT C++ 编程


### 说明
- tracking_car 是一个模拟摄像头小车巡线的程序，使用QT C++ 编程
- 本项目在 RK3588 的 Ubuntu Debin11 上编译运行通过
- 项目的演示效果也将置入项目文件中(Update at 2024.9.14)
- 目前的代码有增加命令行打印调试信息的措施，用于检查摄像头输出的信息是否正确
- 项目演示增加了演示视频（在video文件夹中）

### 问题纠正（错误报告）（Updated at 2024.9.20）
- 目前把车的类单独拆分出来，参考了Qt例程remotecontroller，命名为car
- 摄像头的类目前为了方便调试，还是和车的放在一起，目前摄像头的视角已经调整的差不多了，它可以把视角锁定在车的位置，接下来要做的就是让它锁定在车的前方（已实现（2024.9.20））
- 问题报告：想绘制摄像头的拍摄范围，使用红色边框，但是发现在移动车的时候，红色边框的位移会出现问题，推测和车的边缘矩形有关系，这部分还需要调试（已修正（2024.9.20））
- 同时，摄像头分辨黑色线的判定目前也有些问题：估计是和判定区域和摄像头的拍摄区域有关，之后将会着手修正这个问题（已修正（2024.9.20））
- 本来想让汽车的指令和摄像头的拍摄图像显示在同一个界面中(设定一个自定义的Widget类)，但是在实现过程中出现段错误，目前没找到原因，所以目前暂时使用两个QLable分别显示图像和指令
- 在项目过程中出现的部分问题记录在项目文件夹中的修改日志中
- 代码命名不规范的纠正：计划在完善项目的同时进行纠正，目前想法是将代码的命名规范为大驼峰格式。
- 摄像头目前的功能基本运转正常，剩下的就是考虑识别算法和与小车运动功能的配合程度了
- 21号将把控制小车运动的控件加上，测试小车运动功能,之后再解决自动巡线程序的实现，然后将摄像头黑线识别算法的问题解决
- （Update at 9.22）：创建小车运动控制接口，目前创建了几个按钮控制车的运动



### 项目平台和运行演示
![platform](images/equipment——RK3588.jpg)
![run_show](images/Project2_1_show_2024.9.17.jpg)
![run2_show](images/peoject-Button.jpg)


### 项目依赖
- Qt5 , gcc

### 使用说明
- 可以使用Qtcreator 直接编译运行
- 或者在项目文件目录下，执行sudo qmake 后 执行 sudo make , 之后执行可执行文件即可



### 下一步计划(Update at 2024.9.17)
- remotecontroller的小车例程给我提供了很大的帮助，但目前我没有完全掌握它代码的具体实现，下一步计划更深入地理解例程小车的代码
- 当摄像头代码调试完成后（即它可以分辨黑线和地面，并能及时通告往哪里拐）；将开始实现小车本身的运动
- 修正出现段错误的问题后让摄像头图像和小车指令文字显示在同一页面中
- 项目的模块化做的不会很好，很多代码是糅杂在一起的，下一步的想法是在基本功能调试没问题后，把摄像头的类从小车类里面拆分出来


### 联系方式
- qq:2867191922
- 微信（weixin）: zjq15396069991
- 邮箱：zhujiaqi@tiangong.edu.cn

 
## 感谢(Update at 2024.9.14)
本项目参考并使用了下列方案，在此表示感谢
- learn_programming_zhujiaqi(https://edu.gitee.com/nwpu-pilab/repos/nwpu-pilab/learn_programming_zhujiaqi/tree/master)
- 野火嵌入式QT教程(https://doc.embedfire.com/linux/rk356x/Qt/zh/latest/lubancat_qt/install/introduce.html)
- QT例程：remotecontroller（https://www.qt.io/zh-cn/）
