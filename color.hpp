#ifndef COLOR_H
#define COLOR_H
#include <stdexcept>

class Color {
public:
  Color();
  Color(int r, int g, int b);
  int Red() const;
  int Green() const;
  int Blue() const;

private:
  int red_ = 0;
  int green_ = 0;
  int blue_ = 0;
  static const int kMaxColorValue = 255;
};

bool operator==(const Color& rhs, const Color& lhs);

#endif