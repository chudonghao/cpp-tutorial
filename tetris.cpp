// 引入std::clamp函数
#include <algorithm>
// 引入随机数函数
#include <locale>
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

WINDOW *game_window;
WINDOW *info_window;

void CreateWindow() {
  game_window = newwin(20, 10, 0, 0);
  info_window = newwin(20, 70, 0, 10);
}

void DestroyWindow() { endwin(); }

// 定义格子类型
struct Cell {
  bool has_tetro{};
};

// 定义棋盘类型
struct Board {
  Cell cell[20][10]{};
};

// I O T J L S Z
struct Mino {
  // Mi mi[4];
  Cell cell[4][4]{};
};

// 定义棋盘变量
Board board;

// 定义四连骨牌
Mino mino;
int x;
int y;

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
void ClearBoard() {
  // 遍历每个格子
  for (int row = 0; row < 20; ++row) {
    for (int col = 0; col < 10; ++col) {
      board.cell[row][col].has_tetro = false;
    }
  }
}
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

void ClearLine(int y) {
  for (int col = 0; col < 10; ++col) {
    board.cell[y][col].has_tetro = false;
  }
}

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

void CheckAndDeleteLine() {
  for (int row = 0; row < 20; ++row) {
    if (IsLineFull(row)) {
      ClearLine(row);
      MoveDownAllAboveLine(row);
    }
  }
}

#define GAME_OVER 0
#define EXIT 1
#define RESTART 2

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

void HelpInfo() {
  wclear(info_window);
  mvwprintw(info_window, 3, 0, "Keys:");
  mvwprintw(info_window, 5, 0, "w rotate");
  mvwprintw(info_window, 6, 0, "a left");
  mvwprintw(info_window, 7, 0, "s land");
  mvwprintw(info_window, 8, 0, "d right");
  mvwprintw(info_window, 9, 0, "e exit");
}

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
