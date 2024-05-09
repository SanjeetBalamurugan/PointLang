#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Utils {
bool is_binop(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

template <typename T> bool contains(std::vector<T> hay, T needle) {
  return std::find(hay.begin(), hay.end(), needle) != hay.end();
}
} // namespace Utils
