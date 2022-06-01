# HIT 成绩管理系统

# before use...

For and the display effect, please make sure to use English only, otherwise the format will failed.

## 特点

- 极其花哨的Splash Screen
- 

## 

## 依赖库

- ncursesw 用于文本图形界面的绘制, 'w'用于支持宽字符

## 其他一些过程中用到的内容

- figlet 使用了figlet命令打印出了ascii字符艺术字

- cowsay 把奶牛放进来

## 项目由来

本次项目参考了github上开源项目[nvtop](https://github.com/Syllo/nvtop/), 采用了经典UNIX库**ncurses**和**ncurses/form**共同构建文本用户界面(Text Based User Interface, 即TBUI或TUI), 从实用性和部分趣味性出发, 使用了部分ASCII艺术字, 力图从中体现哈工大的特色, 但由于个人水平有限, 加之准备时间实在紧促, 部分功能打磨还显粗糙, 还请老师以及评审同学多多见谅

本项目参考的一些内容还有:

- WPF中窗口和控件关系的逻辑
- 

## 如何部署

**重要:** 由于Windows平台下对UTF-8编码十分不友好, 导致本项目并不能完全呈现出本人在Linux下开发的效果, 但是由于Linux下又缺少方便快捷的播放音乐的库(Windows下可以使用`PlaySound()`简易地实现), 所以本作业最后部署平台还是在windows上, 但是需要需要注意, 如果试图在windows上部署此文件, 请将所有的文档改成GBK编码, 否则哈工大校徽(可见png.txt)会直接变成乱码

### [推荐]在linux环境下部署

如果你电脑中有linux/虚拟机/WSL, 个人强烈建议在linux下, 原因是依赖库`ncursesw`, `form`gcc已经自带, 开箱即用

1. 进入文件夹中

```
cd ASSIGNMENT_HIT_EXAM
```

2. 编译

```
make
```

3. 运行

```
./main
```

如果提示没有ncursesw, 则可能需要安装对应依赖库(Ubuntu 20.04 WSL 亲测已自带)

```
sudo apt install libncurses-dev
```

### 在Windows下部署此项目

如果使用MinGW以及GNU-Make搭建环境, Windows需要首先将所有的代码转化为GBK编码, 关于为何需要, 请参考`#开发过程中遇到的编码问题`, 我在其中对自己遇到的许多问题作了描述

如果你使用MSVM/Clang, 个人由于没有对应开发环境, 并不清楚应该如何部署, 还请见谅

# 附录

## 开发环境

1. WSL Ubuntu + Windows Terminal完成了前面部分界面的开发
2. Manjaro KDE + Konsole 完成了后面大部分的开发

## 开发软件

Visual Studio Code + gcc + make + git

