#include <algorithm>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>

#include "s21_ant_colony.hpp"
#include "s21_queue.hpp"
#include "s21_stack.hpp"

namespace s21 {
class GraphAlgorithms {
 public:
  s21::Stack<int> DepthFirstSearch(s21::Graph &graph, size_t start_vertex) {
    if (start_vertex < 1 || start_vertex > graph.GetVertices() ||
        graph.GetVertices() < 2)
      throw std::exception();
    s21::Stack<int> res, temp;
    std::vector<bool> visited(graph.GetVertices(), false);
    res.push(start_vertex);
    temp.push(start_vertex - 1);
    visited[start_vertex - 1] = true;
    while (!temp.empty()) {
      int position = temp.top();
      size_t neighbor = 0;
      for (; neighbor < graph.GetVertices(); neighbor++)
        if (graph.GetIndex(position, neighbor) > 0 &&
            visited[neighbor] == false) {
          visited[neighbor] = true;
          temp.push(neighbor);
          res.push(neighbor + 1);
          break;
        }
      if (neighbor == graph.GetVertices()) temp.pop();
    }
    return res;
  }

  s21::Queue<int> BreadthFirstSearch(Graph &graph, size_t start_vertex) {
    if (start_vertex < 1 || start_vertex > graph.GetVertices() ||
        graph.GetVertices() < 2)
      throw std::exception();
    s21::Queue<int> res, temp;
    std::vector<bool> visited(graph.GetVertices(), false);
    res.push(start_vertex);
    temp.push(start_vertex - 1);
    visited[start_vertex - 1] = true;
    while (!temp.empty()) {
      int position = temp.front();
      temp.pop();
      for (size_t i = 0; i < graph.GetVertices(); i++)
        if (graph.GetIndex(position, i) > 0 && visited[i] == false) {
          visited[i] = true;
          res.push(i + 1);
          temp.push(i);
        }
    }
    return res;
  }

  int GetShortestPathBetweenVertices(Graph &graph, size_t vertex1,
                                     size_t vertex2) {
    if (vertex1 < 1 || vertex1 > graph.GetVertices() || vertex2 < 1 ||
        vertex2 > graph.GetVertices() || graph.GetVertices() < 2)
      throw std::exception();
    std::vector<bool> visited(graph.GetVertices(), false);
    std::vector<int> vertexes_values(graph.GetVertices(), kMaxValue);
    int position = vertex1 - 1, target = vertex2 - 1;
    vertexes_values[position] = 0;
    while (true) {
      visited[position] = true;
      for (size_t i = 0; i < graph.GetVertices(); i++)
        if (graph.GetIndex(position, i) > 0 && visited[i] == false &&
            vertexes_values[i] >
                vertexes_values[position] + graph.GetIndex(position, i))
          vertexes_values[i] =
              vertexes_values[position] + graph.GetIndex(position, i);
      int shortest_way = kMaxValue, next_vertex = -1;
      for (size_t i = 0; i < graph.GetVertices(); i++)
        if (graph.GetIndex(position, i) > 0 && visited[i] == false &&
            vertexes_values[i] < shortest_way) {
          shortest_way = vertexes_values[i];
          next_vertex = i;
        }
      if (next_vertex == -1 || next_vertex == target) break;
      position = next_vertex;
    }
    return vertexes_values[target];
  }

  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph) {
    if (graph.GetVertices() < 2) throw std::exception();
    std::vector<std::vector<int>> res(graph.GetVertices(),
                                      std::vector<int>(graph.GetVertices()));
    for (size_t i = 0; i < graph.GetVertices(); i++)
      for (size_t j = 0; j < graph.GetVertices(); j++)
        res[i][j] = graph.GetIndex(i, j);

    for (size_t i = 0; i < graph.GetVertices(); i++)
      for (size_t j = 0; j < graph.GetVertices(); j++)
        for (size_t k = 0; k < graph.GetVertices(); k++)
          if (graph.GetIndex(j, i) > 0 && graph.GetIndex(i, k) > 0)
            res[j][k] = std::min(graph.GetIndex(j, k),
                                 graph.GetIndex(j, i) + graph.GetIndex(i, k));
    return res;
  }

  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph) {
    if (graph.GetVertices() < 2) throw std::exception();
    std::vector<std::vector<int>> res(graph.GetVertices(),
                                      std::vector<int>(graph.GetVertices()));
    std::vector<bool> visited(graph.GetVertices(), false);
    int from = 0, position = 0;
    for (size_t i = 0; i < graph.GetVertices(); i++) {
      int minimal_weight = kMaxValue;
      visited[position] = true;
      for (size_t j = 0; j < graph.GetVertices(); j++)
        for (size_t k = 0; k < graph.GetVertices(); k++)
          if (visited[j] && !visited[k] && graph.GetIndex(j, k) > 0 &&
              graph.GetIndex(j, k) < minimal_weight) {
            minimal_weight = graph.GetIndex(j, k);
            from = j;
            position = k;
          }
      res[from][position] = res[position][from] =
          graph.GetIndex(from, position);
    }
    return res;
  }

  TsmResult SolveTravelingSalesmanProblem(Graph &graph) {
    if (graph.GetVertices() < 2) throw std::exception();
    double alfa = 1.0, beta = 4.0, pheromon_level = 100.0, evaporation = 0.5;
    size_t number_of_ants = 10, iterations = 100;
    AntColony aco(number_of_ants, graph.GetVertices(), alfa, beta,
                  pheromon_level, evaporation);
    return aco.AntAnlgorithm(graph, iterations);
  }

 private:
  const int kMaxValue = std::numeric_limits<int>::max();
};
}  // namespace s21