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
