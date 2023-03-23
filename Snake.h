#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>

#include "vec2.h"

class Map;

enum SnakeStepResult {
  SNAKE_STEP_NORMAL,     // = 0
  SNAKE_STEP_COLLISION,  // = last + 1 = 2
  SNAKE_STEP_GOT_FOOD,   // = last + 1 = 3
  SNAKE_STEP_TOO_LONG,   // = last + 1 = 4
};

class Snake {
  // int _length{2};
  // vec2 _seg[100]{};
  std::vector<vec2> _seg{};  // vector : 1: size 2: vec2 *

  vec2 _dir{-1, 0};

 public:
  Snake(int default_length);

  Snake(int default_length, vec2 init_pos);

  int length();

  const std::vector<vec2> &seg();

  vec2 dir();

  void Init(vec2 pos);

  SnakeStepResult Step(Map &map);

  void UpdateDir(vec2 dir);

 private:
  void Step(vec2 new_head);
};

#endif  // SNAKE_SNAKE_H
