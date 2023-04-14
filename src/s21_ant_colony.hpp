#include "s21_ant.hpp"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance = INFINITY;
};

class AntColony {
 public:
  AntColony(int number_of_ants, int size, double alfa, double beta,
            double pheromon_level, double evaporation)
      : kSize(size),
        kNumberOfAnts(number_of_ants),
        kAlpha(alfa),
        kBeta(beta),
        kPheromonLevel(pheromon_level),
        kEvaporation(evaporation) {
    pheromon_ = std::vector<std::vector<double>>(
        kSize, std::vector<double>(kSize, 0.001));
  }

  TsmResult AntAnlgorithm(Graph g, size_t iterations) {
    std::vector<Ant> ants(kNumberOfAnts, Ant(kSize, kAlpha, kBeta));
    for (size_t i = 0; i < iterations; i++) {
      for (size_t k = 0; k < kNumberOfAnts; k++) {
        ants[k].ResetAnts();
        for (size_t j = 1; j < kSize; j++)
          if (!ants[k].GetDeadEnd()) ants[k].Move(g, pheromon_);
        if (!ants[k].GetDeadEnd()) ants[k].Return(g);
        if (ants[k].GetDistance() < result_.distance &&
            ants[k].GetDistance() != 0) {
          result_.distance = ants[k].GetDistance();
          result_.vertices = ants[k].GetVertices();
        }
        PheromoneUpdate(ants[k].GetVertices(), ants[k].GetDistance());
      }
      EvaporatePheromone(g);
      PheromoneUpdate(result_.vertices, result_.distance);
    }
    if (!result_.vertices.empty())
      if (result_.vertices[0] != 0) FlipAnswer(result_);
    for (size_t i = 0; i < result_.vertices.size(); i++) result_.vertices[i]++;
    return result_;
  }

 private:
  const size_t kSize, kNumberOfAnts;
  const double kAlpha, kBeta, kPheromonLevel, kEvaporation;
  std::vector<std::vector<double>> pheromon_;
  TsmResult result_;

  void EvaporatePheromone(Graph g) {
    for (size_t i = 0; i < g.GetVertices(); i++)
      for (size_t j = 0; j < g.GetVertices(); j++)
        if (g.GetIndex(i, j) > 0) pheromon_[i][j] *= (1.0 - kEvaporation);
  }

  void FlipAnswer(TsmResult &result) {
    std::vector<int> temp;
    size_t initial_position =
        std::find(result.vertices.begin(), result.vertices.end(), 0) -
        result.vertices.begin();
    for (size_t i = initial_position; i < result.vertices.size(); i++)
      temp.push_back(result.vertices[i]);
    for (size_t i = 1; i < initial_position; i++)
      temp.push_back(result.vertices[i]);
    temp.push_back(result.vertices[initial_position]);
    result.vertices = temp;
  }

  void PheromoneUpdate(std::vector<int> vertices, double distance) {
    if (!vertices.empty())
      for (size_t i = 0; i < vertices.size() - 1; i++)
        pheromon_[vertices[i]][vertices[i + 1]] =
            pheromon_[vertices[i + 1]][vertices[i]] +=
            (kPheromonLevel / distance);
  }
};
}  // namespace s21
