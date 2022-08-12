#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  void ColorPaths(const GrayscaleImage& image);
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kRForGreen = 31;
  static const int kGForGreen = 253;
  static const int kBForGreen = 13;
  static const int kRForRed = 252;
  static const int kGForRed = 25;
  static const int kBforRed = 63;
};

#endif