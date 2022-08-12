#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);
  std::vector<int> vect;
  int value = 0;
  while (ifs.good()) {
    ifs >> value;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      vect.push_back(value);
    }
  }
  if (vect.size() != (width_ * height_)) {
    throw std::runtime_error("invalid width or height");
  }
  int max = vect.at(0);
  int min = vect.at(0);
  for (int i : vect) {
    if (i < min) {
      min = i;
    }
    if (i > max) {
      max = i;
    }
  }
  max_ele_ = max;
  min_ele_ = min;
  std::vector<int> row;
  int idx = 0;
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      row.push_back(vect.at(idx));
      idx++;
    }
    data_.push_back(row);
    row.clear();
  }
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}