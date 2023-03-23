#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include <vector>

#include "vec2.h"

class Map {
  int _width{20};
  int _height{20};
  vec2 _food_pos;

 public:
  Map(int width, int height);

  int width();

  int height();

  vec2 food_pos();

  // bool CreateFood(int length, vec2 *exclude);
  bool CreateFood(const std::vector<vec2> &exclude);
};

#endif  // SNAKE_MAP_H
