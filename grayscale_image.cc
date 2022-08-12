#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset): width_(dataset.Width()),
    height_(dataset.Height()) {
  std::vector<Color> temp;
  const int kMinEle = dataset.MinEle();
  const int kMaxEle = dataset.MaxEle();
  int shade_of_gray = 0;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      if (kMaxEle - kMinEle == 0) {
        shade_of_gray = 0;
      } else {
        shade_of_gray = std::round(((dataset.DatumAt(i, j) - kMinEle)) / (double)(kMaxEle - kMinEle) * kMaxColorValue);
      }
      temp.push_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
    }
    image_.push_back(temp);
    temp.clear();
  }
}
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
      GrayscaleImage(ElevationDataset(filename, width_, height_));
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n';
  ofs << width_ << " " << height_ << '\n';
  ofs << kMaxColorValue << '\n';
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ofs << ColorAt(i, j).Red() << " " << ColorAt(i, j).Green() << " " << ColorAt(i, j).Blue() << " ";
    }
    ofs << '\n';
  }
  ofs.close();
}