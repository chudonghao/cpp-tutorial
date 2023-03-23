// hello-world主要用于理解编译过程，我们可以分别生成如下目标：
// 1. hello-world-ii
// 2. hello-world-s
// 3. hello-world-o
// 4. hello-world
// 他们通过如下指令生成：
// 1. cc -E hello-world.cpp -o hello-world.cpp.ii
// 2. cc -S hello-world.cpp.ii -o hello-world.cpp.s
// 3. cc -c hello-world.cpp.s -o hello-world.cpp.o
// 4. cc hello-world.cpp.o -o hello-world
// 他们分别对应了编译的四个过程：
// 1. 预处理；文本替换
// 2. 编译；将源码转换为汇编代码
// 3. 汇编；将汇编代码转换为机器码
// 4. 链接；将机器码链接为可执行程序

#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
