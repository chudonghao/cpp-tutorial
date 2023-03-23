#include "Snake.h"

#include "Map.h"

Snake::Snake(int default_length) : _seg(default_length) {}

Snake::Snake(int default_length, vec2 init_pos) : _seg(default_length) {
  Init(init_pos);
}

int Snake::length() { return _seg.size(); }

const std::vector<vec2> &Snake::seg() { return _seg; }

vec2 Snake::dir() { return _dir; }

void Snake::Init(vec2 pos) {
  for (int i = 0; i < _seg.size(); ++i) {
    _seg[i] = pos + vec2{i, 0};
  }
}

SnakeStepResult Snake::Step(Map &map) {
  vec2 new_head = _seg[0] + _dir;
  if (map.food_pos() == new_head) {
    // Step(new_head);
    _seg.insert(_seg.begin(), new_head);
    // if(_length == SNAKE_MAX_LENGTH) {
    //     return SNAKE_STEP_TOO_LONG;
    // }
    return SNAKE_STEP_GOT_FOOD;
  }

  if (!in_bound(map.width(), map.height(), new_head)) {
    return SNAKE_STEP_COLLISION;
  }

  // if(collision(_length, _seg, new_head))
  if (collision(_seg, new_head)) {
    return SNAKE_STEP_COLLISION;
  }

  Step(new_head);

  return SNAKE_STEP_NORMAL;
}

void Snake::UpdateDir(vec2 dir) {
  if (_dir + dir == vec2{}) {
    return;
  }
  _dir = dir;
}

void Snake::Step(vec2 new_head) {
  for (int i = _seg.size(); 0 <= i; --i) {
    if (i == 0) {
      _seg[i] = new_head;
    } else {
      _seg[i] = _seg[i - 1];
    }
  }
}
