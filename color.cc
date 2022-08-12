#include "color.hpp"

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if ((red_ < 0 || red_ > kMaxColorValue) || (green_ < 0 || green_ > kMaxColorValue) || (blue_ < 0 || blue_ > kMaxColorValue)) {
    throw std::invalid_argument("argument out of range");
  }
}

Color::Color() {
  red_ = 0;
  green_ = 0;
  blue_ = 0;
} 

int Color::Red() const {
  return red_;
}

int Color::Green() const {
  return green_;
}

int Color::Blue() const {
  return blue_;
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}