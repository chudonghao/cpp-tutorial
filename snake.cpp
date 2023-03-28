///=============================================================================
/// C++基础知识：
/// 1. 多源代码（编译单元）构建
///    1. （全局）变量在所有编译单元中唯一
///    2. （全局）函数在所有编译单元中唯一
///    3. 类型定义在编译单元内唯一，因为类型定义不占内存，仅说明类型的内存结构
/// 2. 声明（普通变量与函数）
///    1. 声明全局变量
///    1. 声明函数
/// 4. 定义（普通变量与函数）
///    1. 定义全局变量
///    2. 定义函数
///    3. 定义局部变量
///    4. 定义局部静态变量（与全局变量相同，仅可见性差异）
/// 5. 定义类（class）
///    1. 定义成员变量
///    2. 声明类静态变量（与全局变量相同）
///    3. 声明类静态函数（与全局函数相同）
///    4. 声明成员函数
///    5. 定义类静态变量（全局）
///    6. 定义类静态函数（全局）
///    6. 定义类成员函数
/// 6. 成员访问
///    1. 成员变量访问
///    2. 静态成员变量访问
/// 7. 函数调用
///    1. 成员函数调用
///    2. 静态成员函数调用
/// 8. 构造函数
///    1. 默认构造函数
///    2. 带参构造函数
///    3. 复制构造函数
///    4. 移动构造函数
/// 9. 析构函数
/// 11. 初始化列表
///     1. 成员变量的默认初始化
///     2. 在构造函数上创建初始化列表
/// 12. 类中变量与函数的可见性
///     1. private
///     2. protected
///     3. public
/// 13. 定义枚举类型
///=============================================================================
/// 理解或思想：
/// 👉 静态成员变量：💡与全局变量无异
/// 👉 静态成员函数：💡与普通函数无异
/// 👉 成员函数：
///    💡隐含一个this参数
///    💡底层实现上与普通函数无异
/// 👉 C++的默认行为：
///     如果我们没有定义构造函数，则C++会尝试为我们创建默认构造函数
///     如果我们没有定义析构函数，则C++会为我们创建默认析构函数
///=============================================================================
/// 思想！：
/// 👉 RAII：💡有始有终
///=============================================================================

// 引入ncurses库，包括类型和函数：
// * WINDOW - 窗口类型
// * newwin - 创建窗口
//*  enwin-
// * mvwprintw - 在窗口上显示内容
// * wrefresh - 刷新窗口显示
// * getch - 获取用户输入
// * napms - 等待若干时间
// * ...
#include "Snake.h"

#include <ncurses.h>

#include "Map.h"
#include "vec2.h"

WINDOW *window;

Map map{30, 20};
Snake snake{3, vec2{10, 10}};

void CreateWindow(int width, int height) {
  window = newwin(height, width, 0, 0);
}

void RenderMap() {
  for (int y = 0; y < map.height(); ++y) {
    for (int x = 0; x < map.width(); ++x) {
      mvwprintw(window, y, x, " ");
    }
  }
  mvwprintw(window, map.food_pos().y, map.food_pos().x, "x");
}

void RenderSnake() {
  for (int i = 0; i < snake.length(); ++i) {
    mvwprintw(window, snake.seg()[i].y, snake.seg()[i].x, "*");
  }
}

int main() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  scrollok(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  CreateWindow(map.width(), map.height());

  snake.Init(vec2{map.width() / 2, map.height() / 2});
  map.CreateFood(snake.seg());

  int time = 0;
  for (;;) {
    napms(1);
    time = time + 1;
    if (time > 300) {
      time = 0;
      int state = snake.Step(map);
      switch (state) {
        case SNAKE_STEP_COLLISION:
          // TODO Game Over
          break;
        case SNAKE_STEP_GOT_FOOD:
          if (!map.CreateFood(snake.seg())) {
            // TODO Win
          }
          break;
        case SNAKE_STEP_TOO_LONG:
          // TODO Win
          break;
        case SNAKE_STEP_NORMAL:
          break;
      }
    }

    char input = getch();
    switch (input) {
      case 'w':
        snake.UpdateDir(vec2{0, -1});
        break;
      case 'a':
        snake.UpdateDir(vec2{-1, 0});
        break;
      case 's':
        snake.UpdateDir(vec2{0, 1});
        break;
      case 'd':
        snake.UpdateDir(vec2{1, 0});
        break;
    }
    RenderMap();
    RenderSnake();
    wrefresh(window);
  }

  return 0;
}
