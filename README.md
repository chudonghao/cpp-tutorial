# 楚栋浩的C++入门教程

我们的入门课程以视频授课的形式开展，循序渐进地讲述C++的知识。

我们从视频课程中提炼两个部分，一个是课程博客，一个是课程代码。

课程博客同样循序渐进总结C++的知识。

课程代码是为了让我们从实践中深入理解C++的知识。

---

我们再强调一下：

**最重要的是理解C++的设计！**

---

学习指导：

我们可以跟随课程博客[楚栋浩的C++入门课程](https://blog.csdn.net/qq_24654009/article/details/129170760)的内容来学习。

有能力也可以直接按照代码列表来从代码中学习，我们会在代码中加入很多注释。

> 我们在代码中以`///`开头的注释为知识性注释，`//`开头的注释为针对某一段代码的注释

---

代码列表：

1. Hello World
   * [hello-world.cpp](hello-world.cpp)
2. Tetris
   * [tetris.cpp](tetris.cpp)
3. Snake
   * [snake.cpp](snake.cpp)
   * [Snake.h](Snake.h)
   * [Snake.cpp](Snake.cpp)
   * [Map.h](Map.h)
   * [Map.cpp](Map.cpp)
   * [vec2.h](vec2.h)
   * [vec2.cpp](vec2.cpp)

---

如何运行代码列表中的代码：

> 如果你没有学习如何开发C++程序，那么你应该首先从课程博客中学习。

1. 安装依赖库`ncurese`
2. 使用IDE构建对应目标
3. 从命令行运行程序（CLion似乎无法直接调试ncurses程序；QtCreator可以选择在调试时选择在终端中运行）

> Ubuntu下通过如下指令安装ncurses
> ```shell
> sudo apt install libncurses-dev
> ```
