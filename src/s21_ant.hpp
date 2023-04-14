#include <random>
#include <vector>

#include "s21_graph.hpp"

namespace s21 {
class Ant {
 public:
  Ant(int size, double alpha, double beta)
      : kAlpha(alpha), kBeta(beta), kSize(size) {
    ResetAnts();
  }

  double GetDistance() { return distance_; }

  std::vector<int> GetVertices() { return vertices_; }

  void ResetAnts() {
    distance_ = 0;
    visited_ = std::vector<bool>(kSize, false);
    vertices_.clear();
    position_ = GetRandomposition();
    next_position_ = -1;
    visited_[position_] = true;
    vertices_.push_back(position_);
  }

  void Move(Graph g, std::vector<std::vector<double>> &p) {
    next_position_ = -1;
    int count = 0;
    while (next_position_ == -1) {
      next_position_ = ChoosePath(g, p);
      if (count == 100) {
        SetDeadEnd();
        break;
      }

      count++;
    }
    if (position_ != -1 && next_position_ != -1) {
      distance_ += g.GetIndex(position_, next_position_);
      position_ = next_position_;
      visited_[position_] = true;
      vertices_.push_back(position_);
    }
  }

  void Return(Graph g) {
    if (g.GetIndex(position_, vertices_[0]) > 0) {
      distance_ += g.GetIndex(position_, vertices_[0]);
      vertices_.push_back(vertices_[0]);
    } else {
      SetDeadEnd();
    }
  }

  bool GetDeadEnd() { return (position_ == -1 ? true : false); };

 private:
  const double kAlpha, kBeta;
  const size_t kSize;
  int position_, next_position_;
  double distance_;
  std::vector<int> vertices_;
  std::vector<bool> visited_;

  double GetRandomNumber() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, 1);
    return distr(eng);
  }

  double GetAttractiveness(int target, Graph g,
                           std::vector<std::vector<double>> p) {
    double avalible_paths = 0;
    for (size_t i = 0; i < kSize; i++)
      if (g.GetIndex(position_, i) > 0 && !visited_[i])
        avalible_paths += GetPathAttractivness(i, g, p);
    avalible_paths = GetPathAttractivness(target, g, p) / avalible_paths;
    return avalible_paths;
  }

  double GetPathAttractivness(int target, Graph g,
                              std::vector<std::vector<double>> p) {
    return std::pow(p[position_][target], kAlpha) *
           std::pow(1.0 / g.GetIndex(position_, target), kBeta);
  }

  int ChoosePath(Graph g, std::vector<std::vector<double>> p) {
    double sum = 0, random = GetRandomNumber();
    size_t i = -1;
    while (sum < random) {
      i++;
      if (i == kSize) {
        i = -1;
        break;
      }
      if (g.GetIndex(position_, i) > 0 && !visited_[i])
        sum += GetAttractiveness(i, g, p);
    }
    return i;
  }

  int GetRandomposition() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, kSize - 1);
    return distr(eng);
  }

  void SetDeadEnd() {
    ResetAnts();
    position_ = -1;
  }
};
}  // namespace s21
