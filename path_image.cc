#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  for (size_t i = 0; i < height_; i++) {
    Path path(image.Width(), i);
    size_t row_idx = i;
    path.SetLoc(0, i);
    size_t col_idx = 0;
    while (col_idx < dataset.Width() - 1) {
      int dif_up = INT32_MAX;
      int dif_down = INT32_MAX;
      int current_val = dataset.DatumAt(row_idx, col_idx);
      if (row_idx != 0) {
        dif_up = abs(current_val - dataset.DatumAt(row_idx - 1, col_idx + 1));
      }
      if (row_idx != height_ - 1) {
        dif_down = abs(current_val - dataset.DatumAt(row_idx + 1, col_idx + 1));
      }
      int dif_same = abs(current_val - dataset.DatumAt(row_idx, col_idx + 1));
      if (dif_same <= dif_up && dif_same <= dif_down) {
        path.IncEleChange(dif_same);
      } else if (dif_down <= dif_up && dif_down <= dif_same) {
        path.IncEleChange(dif_down);
        row_idx++;
      } else {
        path.IncEleChange(dif_up);
        row_idx--;
      }
      path.SetLoc(col_idx + 1, row_idx);
      col_idx++;
    }
    paths_.push_back(path);
  }
  ColorPaths(image);
}

void PathImage::ColorPaths(const GrayscaleImage& image) {
  path_image_ = image.GetImage();
  unsigned int least_ele = paths_.at(0).EleChange();
  size_t best_path_row = 0;
  for (size_t i = 0; i < paths_.size(); i++) {
    if (paths_.at(i).EleChange() < least_ele) {
      least_ele = paths_.at(i).EleChange();
      best_path_row = i;
    }
  }
  for (size_t i = 0; i < paths_.size(); i++) {
    for (size_t j = 0; j < paths_.at(i).Length(); j++) {
      if (i != best_path_row) {
        path_image_.at(paths_.at(i).GetPath().at(j)).at(j) =
            Color(kRForRed, kGForRed, kBforRed);
      }
    }
  }
  for (size_t i = 0; i < paths_.at(best_path_row).Length(); i++) {
    path_image_.at(paths_.at(best_path_row).GetPath().at(i)).at(i) =
        Color(kRForGreen, kGForGreen, kBForGreen);
  }
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n';
  ofs << width_ << " " << height_ << '\n';
  ofs << kMaxColorValue << '\n';
  for (size_t i = 0; i < path_image_.size(); i++) {
    for (size_t j = 0; j < path_image_.at(i).size(); j++) {
      ofs << path_image_.at(i).at(j).Red() << " "
          << path_image_.at(i).at(j).Green() << " "
          << path_image_.at(i).at(j).Blue() << " ";
    }
    ofs << '\n';
  }
  ofs.close();
}
