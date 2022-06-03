# HIT 成绩管理系统

## 特点

- Super fancy *Splash Screen*
- 容错性, 如果输入有误则显示invalid, 并且让用户继续输入
- 直观且类excel的输入表格, 使用颜色进行区分, 方便用户使用
- 一些小彩蛋, 尝试在自己的期末作业中加入一丝趣味的成分
- ~~检查用户的输入是否有效, 若无效则跳过该记录~~(咕咕咕)
- 面向对象的编程方法, 输入窗口可以多次复用, 窗口之间的等级属于平等关系, 安排相对合理

## 依赖库

- ncursesw 用于文本图形界面的绘制, 'w'用于支持宽字符
- ncursesw/form 用于读取用户输入

## 其他一些过程中用到的内容

- figlet 使用了figlet命令打印出了ascii字符艺术字

- cowsay 把奶牛放进来

## 项目由来

本次项目参考了github上开源项目[nvtop](https://github.com/Syllo/nvtop/), 采用了经典UNIX库**ncurses**和**ncurses/form**共同构建文本用户界面(Text Based User Interface, 即TBUI或TUI), 从实用性和部分趣味性出发, 使用了部分ASCII艺术字, 力图从中体现哈工大的特色, 但由于个人水平有限, 加之准备时间实在紧促, 部分功能打磨属于一种非常粗糙, 完全不能让我自己满意的情况, 还请老师以及评审同学多多见谅

本项目参考的一些内容还有:

- WPF中窗口和控件关系的逻辑

**并非所有的内容都是我直接写的, 有部分函数是我在查资料过程中发现的非常有用的代码, 直接粘贴进来的, 这些函数会在前面加一个`_COPY__`的前缀**

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

如果你使用MSVC/Clang, 个人由于没有对应开发环境, 并不清楚应该如何部署, 还请见谅

**WINDOWS10及以下用户注意** 由于这些版本的Windows终端模拟器通常都没有设置等宽字体, 可能会导致显示效果不佳, 建议使用Windows Terminal并且设置字体为等宽且符合拓展字符集的字体(可以使用Cascadia字体)或者手动设定Powershell为等宽字体, 不过也可以尝试先运行看看效果如何

如果你电脑中已经安装了GNU Make(通常来说大部分人并没有), 可以类似于上面Linux下部署的方式

如果不带GNU, 那默认电脑中应该有Mingw gcc

使用如下命令

```
gcc -c -o interface.o src/interface.c -lncursesw -Iinclude
gcc -c -o controls.o src/controls.c -lncursesw -Iinclude
gcc -c -o wins.o src/wins.c -lncursesw -Iinclude -lform
gcc -c -o student.o src/student.c -lncursesw -Iinclude
gcc -o main.exe src/main.c student.o wins.o controls.o interface.o -lncursesw -Iinclude -lform
del *.o
```


# 附录

## 开发环境

1. WSL on Ubuntu + Windows Terminal完成了前面部分界面的开发
2. Manjaro KDE + Konsole 完成了后面大部分的开发

## 开发软件

Visual Studio Code + gcc + make

## 在开发过程中遇到的问题

1. Windows的编码问题

Windows11终端运行那些拓展字符会导致出现大量的乱码, 经过推测应该是UTF-8字体被当成GBK编码, 然而, 常用手段`chcp 65001`并不能解决这个问题, 而且Windows11的终端本身就是默认UTF-8编码(至少自称如此), 经过了多次尝试之后猜测可能是Windows Terminal是伪UTF-8编码, 本质上还是用GBK在读写, 经过尝试, 只有先把自己的源代码转成GBK编码才能正确地打印

2. ncurses奇怪的刷新问题

这个问题真的是很玄学我只能说, 你可能会注意到我源码里面写了大量的`refresh()`, 原因是我完全把握不透它到底该什么时候刷新, 感到一种匪夷所思


## 时间仓促存在的问题

原本以为存在非常充裕的时间, 结果因为各种问题导致最后一天赶工, 有些很尴尬的问题并没有解决, 比如说

- 学生名称不能存在空格
- 当科目数量太多 (这在哈工大是非常可能出现的事情) 的时候没有很好的同时显示的方法(nvtop解决了这个问题, 通过从某个字符开始打印的方式实现了左右横向滚动, 但是, 没有时间实现了:-{