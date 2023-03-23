#include "vec2.h"

vec2 operator+(vec2 l, vec2 r) { return vec2{l.x + r.x, l.y + r.y}; }

bool operator==(vec2 l, vec2 r) { return l.x == r.x && l.y == r.y; }

bool operator!=(vec2 l, vec2 r) { return !(l == r); }

bool in_bound(int width, int height, vec2 test) {
  return !(test.x < 0 || test.x >= width || test.y < 0 || test.y >= height);
}

// bool collision(int length_seg, vec2 *seg, vec2 test){
bool collision(const std::vector<vec2>& seg, vec2 test) {
  for (int i = 0; i < seg.size(); ++i) {
    if (seg[i] == test) {
      return true;
    }
  }
  return false;
}
