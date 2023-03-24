///=============================================================================
/// 相关基础知识：
/// 1. 编译的四个过程 https://blog.csdn.net/qq_24654009/article/details/129170760#compilation-process
/// 2. 预处理
/// 3. 编译单元
///=============================================================================

/// hello-world主要用于理解编译过程，我们可以分别生成如下目标：
/// 1. hello-world-ii
/// 2. hello-world-s
/// 3. hello-world-o
/// 4. hello-world
/// 他们通过如下指令生成：
/// 1. cc -E hello-world.cpp -o hello-world.cpp.ii
/// 2. cc -S hello-world.cpp.ii -o hello-world.cpp.s
/// 3. cc -c hello-world.cpp.s -o hello-world.cpp.o
/// 4. cc hello-world.cpp.o -o hello-world
/// 他们分别对应了编译的四个过程：
/// 1. 预处理；文本替换
/// 2. 编译（区别于整个编译过程）；将源码转换为汇编代码
/// 3. 汇编；将汇编代码转换为机器码
/// 4. 链接；将机器码链接为可执行程序

/// 我们可以在hello-world目标后打开各个文件

/// hello-world.cpp.ii文件为预处理后的结果，
/// 可以看到，我们已经没有#include<iostream>指令了，
/// 取而代之的是<iostream>文件中的内容（我们可以通过按住ctrl点击文件名），以及一些标注`# ...`

/// hello-world.cpp.s文件为编译之后的结果，
/// 可以看到汇编代码，
/// 编译的四个过程中的"编译"就是将源代码转换为汇编代码的过程
/// 我们可以在代码中看到诸如"mov""call"等汇编指令

/// hello-world.cpp.o文件为汇编之后的结果，
/// 它们包括二进制的机器指令、静态数据等二进制的数据，计算机可以直接存入内存并执行或使用它们

/// hello-world为链接后的结果，
/// 因为我们只有一个编译单元，所以hello-world的内容和hello-world.cpp.o的内容基本相同

// 这段代码将被<iostream>文件的内容取代
#include <iostream>

// 这段代码将出现在hello-world.cpp.ii的最后
int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
