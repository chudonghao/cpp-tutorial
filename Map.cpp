#include "Map.h"

#include <random>

Map::Map(int width, int height) : _width(width), _height(height) {}

int Map::width() { return _width; }

int Map::height() { return _height; }

vec2 Map::food_pos() { return _food_pos; }

// bool Map::CreateFood(int length, vec2 *exclude) {
bool Map::CreateFood(const std::vector<vec2> &exclude) {
  std::random_device rd;
  std::default_random_engine re{rd()};
  std::uniform_int_distribution<int> gen_x(0, _width - 1);
  std::uniform_int_distribution<int> gen_y(0, _height - 1);

  vec2 food_pos = vec2{gen_x(re), gen_y(re)};
  vec2 food_pos_start = food_pos;

  bool collision_occurred = false;
  for (; collision(exclude, food_pos) && food_pos != food_pos_start;) {
    collision_occurred = true;
    food_pos = food_pos + vec2{1, 0};
    if (!in_bound(_width, _height, food_pos)) {
      food_pos = vec2{0, (food_pos.y + 1) % _height};
    }
  }

  if (collision_occurred && food_pos == food_pos_start) {
    return false;
  }

  _food_pos = food_pos;
  return true;
}
