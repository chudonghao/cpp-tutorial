///=============================================================================
/// 计算机基础知识：
/// 1. 计算机的基本结构
/// 2. 计算机内存如何存储数据
/// 2. 计算机CPU如何存取数据
///=============================================================================
/// C++基础知识：
/// 1. 预处理（注释、头文件引入、定义宏）
/// 2. 数据类型
///    1. 基本数据类型与数组
///    2. 指针（特殊的基本数据类型）
///    3. 引用（特殊的语法糖与语法含义）
/// 3. 定义类型
///    1. 成员变量
/// 4. 定义变量
///    1. 定义基本数据类型变量
///    2. 定义结构体类型变量
///    2. 定义数组变量
/// 5. 定义函数
/// 6. 表达式
///    1. 运算符
///    2. 访问变量
///    3. 调用函数
/// 7. 逻辑语句
///    1. 条件语句 if switch(case default break)
///    2. 循环语句 for while do..while -- continue break
///    3. 跳转语句 goto
/// 8. 入口函数
/// 9. （自定义）类型的内存结构
/// 10. 函数的调用过程
///=============================================================================
/// 理解或思想：
/// 👉 预处理：💡简单的文本替换，提高代码复用
/// 👉 数据类型的作用：💡赋予格子（内存）含义，或者说💡标注内存的处理方式
///    👉 指针：💡整数，💡代表格子的地址（编号）
///    👉 引用：💡从底层角度看：引用是指针的语法糖，💡从语义角度看：引用是变量别名
/// 👉 定义（自定义）类型：
///    💡确定该类型变量占用的格子数（通过成员变量自动计算大小）
///    💡以及每个格子的含义（通过成员变量自动确定每个格子的含义）
/// 👉 定义变量：💡自动申请一段内存并赋予格子含义
/// 👉 定义数组：💡同定义变量，但一次性分配一段长的连续内存，连续存放多个变量（元素）
/// 👉 定义函数：💡描述一个过程：输入->处理->输出，即参数->函数体->返回值
/// 👉 访问变量：💡找到对应格子，按类型含义访问和处理格子内的数据
/// 👉 调用函数：💡很好理解
/// 👉 逻辑语句：💡比较+跳转
/// 👉 （自定义）类型的内存结构：
///    💡从避免CPU多次存取内存的角度出发，自动空出格子以提高内存访问效率
/// 👉 函数的调用过程：
///    💡递归！
///    💡栈！
///    💡输入（参数）输出（返回值）通过在函数调用栈上创建变量传递
///    💡参数和返回值必须通过复制值的方式传递，指针和引用的特殊之处在于复制（传递）的是地址
///=============================================================================
/// 思想！：
/// 👉 程序的基本作用：💡内存读写与指令执行
/// 👉 面向对象-理解方式1：💡数据+算法（过程）
/// 👉 面向对象-理解方式2：💡变量+函数
///=============================================================================

// 🏷 头文件引入
// 引入标准库.算法.函数std::clamp
#include <algorithm>
// 引入标准库.函数setlocale
#include <clocale>
// 引入标准库.随机数
#include <random>
// 引入ncurses库，包括类型和函数：
// * WINDOW - 窗口类型
// * newwin - 创建窗口
// * mvwprintw - 在窗口上显示内容
// * wrefresh - 刷新窗口显示
// * getch - 获取用户输入
// * napms - 等待若干时间
// * ...
#include <ncurses.h>

// 🏷 定义（全局）变量
WINDOW *game_window;
WINDOW *info_window;

// 🏷 定义函数
void CreateWindow() {
  game_window = newwin(20, 10, 0, 0);
  info_window = newwin(20, 70, 0, 10);
}

// 🏷 定义函数
void DestroyWindow() { endwin(); }

// 🏷 定义（自定义）类型
// 定义格子类型
struct Cell {
  bool has_tetro{};
};

// 🏷 定义（自定义）类型
// 定义棋盘类型
struct Board {
  Cell cell[20][10]{};
};

// 🏷 定义（自定义）类型
// 定义四连骨牌类型
// 四连骨牌有7种形式：I O T J L S Z
struct Mino {
  // Mi mi[4];
  Cell cell[4][4]{};
};

// 🏷 定义（全局）变量
// 定义棋盘变量
Board board;

// 🏷 定义（全局）变量
// 定义四连骨牌
Mino mino;
// 🏷 定义（全局）变量
// 定义四连骨牌的位置
int x;
int y;

// 🏷 定义函数
// 绘制棋盘
void RenderBoard() {
  // 遍历每个格子
  for (int row = 0; row < 20; ++row) {
    for (int col = 0; col < 10; ++col) {
      if (board.cell[row][col].has_tetro) {
        mvwprintw(game_window, row, col, "■");
      } else {
        mvwprintw(game_window, row, col, "□");
      }
    }
  }
}

// 🏷 定义函数
// 清除磁盘
void ClearBoard() {
  // 遍历每个格子
  for (int row = 0; row < 20; ++row) {
    for (int col = 0; col < 10; ++col) {
      board.cell[row][col].has_tetro = false;
    }
  }
}

// 🏷 定义函数
// 绘制四连骨牌
void RenderMino() {
  // 遍历MINO的每个格子
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      if (mino.cell[row][col].has_tetro) {
        mvwprintw(game_window, y + row, (x + col), "■");
      }
    }
  }
}

// 🏷 定义函数
// 碰撞检测
bool CollisionDetect(Mino &mino, int x, int y) {
  // 每个mino的骨牌是否产生碰撞
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      if (mino.cell[row][col].has_tetro) {
        int tetro_x = x + col;
        int tetro_y = y + row;
        // 棋盘边界
        if (tetro_x < 0 || 10 <= tetro_x) {
          return true;
        }
        if (20 <= tetro_y) {
          return true;
        }
        // 和之前已落下的骨牌
        if (board.cell[tetro_y][tetro_x].has_tetro) {
          return true;
        }
      }
    }
  }
  return false;
}

// 🏷 定义函数
// 创建四连骨牌
bool CreateMino() {
  // 随机创建其中一种类型：I O T J L S Z
  std::random_device rd;
  std::default_random_engine re(rd());
  std::uniform_int_distribution<int> generator(0, 6);
  int type_id = generator(re);

  Mino mino_proto[7]{};
  // I
  // - * - -
  // - * - -
  // - * - -
  // - * - -
  mino_proto[0].cell[0][1].has_tetro = true;
  mino_proto[0].cell[1][1].has_tetro = true;
  mino_proto[0].cell[2][1].has_tetro = true;
  mino_proto[0].cell[3][1].has_tetro = true;
  // O
  // - - - -
  // - * * -
  // - * * -
  // - - - -
  mino_proto[1].cell[1][1].has_tetro = true;
  mino_proto[1].cell[1][2].has_tetro = true;
  mino_proto[1].cell[2][1].has_tetro = true;
  mino_proto[1].cell[2][2].has_tetro = true;
  // T
  // - - - -
  // - * - -
  // * * * -
  // - - - -
  mino_proto[2].cell[1][1].has_tetro = true;
  mino_proto[2].cell[2][0].has_tetro = true;
  mino_proto[2].cell[2][1].has_tetro = true;
  mino_proto[2].cell[2][2].has_tetro = true;
  // J
  // - - * -
  // - - * -
  // - * * -
  // - - - -
  mino_proto[3].cell[0][2].has_tetro = true;
  mino_proto[3].cell[1][2].has_tetro = true;
  mino_proto[3].cell[2][1].has_tetro = true;
  mino_proto[3].cell[2][2].has_tetro = true;
  // L
  // - * - -
  // - * - -
  // - * * -
  // - - - -
  mino_proto[4].cell[0][1].has_tetro = true;
  mino_proto[4].cell[1][1].has_tetro = true;
  mino_proto[4].cell[2][1].has_tetro = true;
  mino_proto[4].cell[2][2].has_tetro = true;
  // S
  // - * - -
  // - * * -
  // - - * -
  // - - - -
  mino_proto[5].cell[0][1].has_tetro = true;
  mino_proto[5].cell[1][1].has_tetro = true;
  mino_proto[5].cell[1][2].has_tetro = true;
  mino_proto[5].cell[2][2].has_tetro = true;
  // Z
  // - - - -
  // - * * -
  // - - * *
  // - - - -
  mino_proto[6].cell[1][1].has_tetro = true;
  mino_proto[6].cell[1][2].has_tetro = true;
  mino_proto[6].cell[2][2].has_tetro = true;
  mino_proto[6].cell[2][3].has_tetro = true;

  if (CollisionDetect(mino_proto[type_id], 4, 0)) {
    mino = {};
    return false;
  }

  mino = mino_proto[type_id];
  x = 4;
  y = 0;
  return true;
}

// 🏷 定义函数
// 下落四连骨牌
// 落地之后需要其它逻辑，返回值代表是否下落成功
bool Fall() {
  // 判断能不能下落
  if (CollisionDetect(mino, x, y + 1)) {
    return false;
  }

  // x = x;
  y = y + 1;
  return true;
}

// 🏷 定义函数
// 使四连骨牌落地，即将四连骨牌分解为单个骨牌放置在棋盘上
void Land() {
  // 把当前的四连骨牌放在棋盘上
  // 绘制在棋盘上
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      if (mino.cell[row][col].has_tetro) {
        board.cell[y + row][x + col].has_tetro = true;
      }
    }
  }
}

// 🏷 定义函数
// 旋转四连骨牌
void Rotate() {
  // ↻
  // - - - -
  // - - - -
  // - - - -
  // - - - -
  // 临时的旋转后的MINO，用于碰撞检测
  Mino tmp_mino{};
  tmp_mino.cell[0][0].has_tetro = mino.cell[3][0].has_tetro;
  tmp_mino.cell[0][1].has_tetro = mino.cell[2][0].has_tetro;
  tmp_mino.cell[0][2].has_tetro = mino.cell[1][0].has_tetro;
  tmp_mino.cell[0][3].has_tetro = mino.cell[0][0].has_tetro;
  tmp_mino.cell[1][0].has_tetro = mino.cell[3][1].has_tetro;
  tmp_mino.cell[1][1].has_tetro = mino.cell[2][1].has_tetro;
  tmp_mino.cell[1][2].has_tetro = mino.cell[1][1].has_tetro;
  tmp_mino.cell[1][3].has_tetro = mino.cell[0][1].has_tetro;
  tmp_mino.cell[2][0].has_tetro = mino.cell[3][2].has_tetro;
  tmp_mino.cell[2][1].has_tetro = mino.cell[2][2].has_tetro;
  tmp_mino.cell[2][2].has_tetro = mino.cell[1][2].has_tetro;
  tmp_mino.cell[2][3].has_tetro = mino.cell[0][2].has_tetro;
  tmp_mino.cell[3][0].has_tetro = mino.cell[3][3].has_tetro;
  tmp_mino.cell[3][1].has_tetro = mino.cell[2][3].has_tetro;
  tmp_mino.cell[3][2].has_tetro = mino.cell[1][3].has_tetro;
  tmp_mino.cell[3][3].has_tetro = mino.cell[0][3].has_tetro;

  // 如果不碰撞，就执行旋转
  if (!CollisionDetect(tmp_mino, x, y)) {
    mino = tmp_mino;
  }
}

// 🏷 定义函数
// 清除棋盘上的一行
void ClearLine(int y) {
  for (int col = 0; col < 10; ++col) {
    board.cell[y][col].has_tetro = false;
  }
}

// 🏷 定义函数
// 将棋盘上的某一行的上方所有行向下移动一行
void MoveDownAllAboveLine(int y) {
  for (int row = y; 0 <= row; --row) {
    if (row == 0) {
      ClearLine(0);
    } else {
      for (int col = 0; col < 10; ++col) {
        board.cell[row][col].has_tetro = board.cell[row - 1][col].has_tetro;
      }
    }
  }
}

// 🏷 定义函数
// 判断棋盘上的某一行是否放满骨牌
bool IsLineFull(int y) {
  // return std::all_of(&board.cell[y][0], &board.cell[y][10], [](auto
  // &cell){return cell.has_tetro;});
  for (int col = 0; col < 10; ++col) {
    if (!board.cell[y][col].has_tetro) {
      return false;
    }
  }
  return true;
}

// 🏷 定义函数
// 检查棋盘上的某一行是否放满骨牌、清理放满的行、将清理的行的上方所有骨牌向下移动
void CheckAndDeleteLine() {
  for (int row = 0; row < 20; ++row) {
    if (IsLineFull(row)) {
      ClearLine(row);
      MoveDownAllAboveLine(row);
    }
  }
}

// 🏷 定义宏
#define GAME_OVER 0
#define EXIT 1
#define RESTART 2

// 🏷 定义函数
// 显示欢迎信息
bool Welcome() {
  wclear(info_window);
  mvwprintw(info_window, 3, 0, "Welcome Tetris!");
  mvwprintw(info_window, 5, 0, "s start");
  mvwprintw(info_window, 6, 0, "e exit");

  for (;;) {
    napms(1);
    char input = getch();
    if (input == 's') {
      return true;
    }
    if (input == 'e') {
      return false;
    }
    wrefresh(info_window);
  }
}

// 🏷 定义函数
// 显示游戏结束信息
int GameOver() {
  wclear(info_window);
  mvwprintw(info_window, 5, 0, "Game Over!");
  mvwprintw(info_window, 6, 0, "r restart");
  mvwprintw(info_window, 7, 0, "e exit");

  for (;;) {
    napms(1);
    char input = getch();
    if (input == 'r') {
      return RESTART;
    }
    if (input == 'e') {
      return EXIT;
    }
    wrefresh(info_window);
  }
}

// 🏷 定义函数
// 显示游戏帮助信息
void HelpInfo() {
  wclear(info_window);
  mvwprintw(info_window, 3, 0, "Keys:");
  mvwprintw(info_window, 5, 0, "w rotate");
  mvwprintw(info_window, 6, 0, "a left");
  mvwprintw(info_window, 7, 0, "s land");
  mvwprintw(info_window, 8, 0, "d right");
  mvwprintw(info_window, 9, 0, "e exit");
}

// 🏷 定义函数
// 单次游戏循环
int GameLoop() {
  HelpInfo();
  ClearBoard();
  // 创建一个特定类型的MINO
  CreateMino();

  int time = 0;
  for (;;) {
    napms(1);
    time = time + 1;

    // 自动下落MINO
    if (time > 1000) {
      // Fall
      bool success = Fall();
      if (!success) {
        Land();
        CheckAndDeleteLine();
        if (!CreateMino()) {
          return GAME_OVER;
        }
      }
      time = 0;
    }

    char input = getch();
    switch (input) {
      case 'w':
        Rotate();
        break;
      case 'a':
        if (!CollisionDetect(mino, x - 1, y)) {
          x = x - 1;
        }
        break;
      case 's':
        for (; Fall();)
          ;
        Land();
        CheckAndDeleteLine();
        if (!CreateMino()) {
          return GAME_OVER;
        }
        break;
      case 'd':
        if (!CollisionDetect(mino, x + 1, y)) {
          x = x + 1;
        }
        break;
      case 'e':
        return EXIT;
      case 'r':
        return RESTART;
    }
    // wrefresh();
    RenderBoard();
    RenderMino();
    wrefresh(game_window);
    wrefresh(info_window);
  }
}

// 🏷 定义函数
// 入口函数
int main() {
  setlocale(LC_ALL, "");
  // 初始化界面系统ncurses
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  scrollok(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  // 创建窗口
  CreateWindow();

welcome:
  if (!Welcome()) {
    return 0;
  }

start_game:
  int opt = GameLoop();
  if (opt == EXIT) {
    goto exit;
  }

  if (opt == RESTART) {
    goto welcome;
  }

  if (GameOver() == RESTART) {
    goto start_game;
  }

exit:
  DestroyWindow();
  return 0;
}
