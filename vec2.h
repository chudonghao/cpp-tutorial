#ifndef SNAKE_VEC2_H
#define SNAKE_VEC2_H

#include <vector>

struct vec2 {
  int x{};
  int y{};
  // vec2() : x{}, y{} {}
  // c // vec2(int, int);
};

vec2 operator+(vec2 l, vec2 r);

bool operator==(vec2 l, vec2 r);

bool operator!=(vec2 l, vec2 r);

bool in_bound(int width, int height, vec2 test);

// bool collision(int length_seg, vec2 *seg, vec2 test);
bool collision(const std::vector<vec2> &seg, vec2 test);

#endif  // SNAKE_VEC2_H
