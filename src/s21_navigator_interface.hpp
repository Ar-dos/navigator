#include <iostream>

#include "s21_graph_algorithms.hpp"

namespace s21 {
class NavigatorInterface {
 public:
  void Start() {
    int input = -1;
    while (input != 0) {
      PrintOptions();
      std::cin >> input;
      switch (input) {
        case 1:
          LoadFromFile();
          break;
        case 2:
          if (CheckEmptyGraph()) TraverseInBreadth();
          break;
        case 3:
          if (CheckEmptyGraph()) TraverseInDepth();
          break;
        case 4:
          if (CheckEmptyGraph()) SearchMinPathTwoVertices();
          break;
        case 5:
          if (CheckEmptyGraph()) SearchMinSpanningTree();
          break;
        case 6:
          if (CheckEmptyGraph()) SearchMinPathAllVertices();
          break;
        case 7:
          if (CheckEmptyGraph()) SolveSalesmanProblem();
          break;
        case 0:
          std::exit(0);
        default:
          std::cout << "Wrong input" << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          input = -1;
          break;
      }
    }
  }

 private:
  Graph graph_;
  GraphAlgorithms algorithms_;

  void ClearInput() {
    std::cout << "Wrong input" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  bool CheckIfFileExists(std::string filename) {
    bool res = false;
    std::ifstream f(filename.c_str());
    res = f.good();
    f.close();
    return res;
  }

  void LoadFromFile() {
    std::string filename;
    std::cout << "Insert filename" << std::endl;
    std::cin >> filename;
    if (CheckIfFileExists(filename)) {
      graph_.LoadGraphFromFile(filename);
      std::cout << "Success" << std::endl;
    } else {
      std::cout << "Wrong filename" << std::endl;
    }
  }

  int GetStartVertex(bool start) {
    int start_vertex = -1;
    if (start)
      std::cout << "Insert start vertex" << std::endl;
    else
      std::cout << "Insert other vertex" << std::endl;
    std::cin >> start_vertex;
    if (start_vertex <= 0 ||
        start_vertex > static_cast<int>(graph_.GetVertices())) {
      // std::cout << "Wrong input" << std::endl;
      ClearInput();
      start_vertex = -1;
    }
    return start_vertex;
  }

  void TraverseInBreadth() {
    int start_vertex = static_cast<int>(GetStartVertex(true));
    if (start_vertex != -1) {
      s21::Stack<int> stack =
          algorithms_.DepthFirstSearch(graph_, start_vertex);
      while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
      }
      std::cout << std::endl;
    }
  }

  void TraverseInDepth() {
    int start_vertex = GetStartVertex(true);
    if (start_vertex != -1) {
      s21::Queue<int> queue =
          algorithms_.BreadthFirstSearch(graph_, start_vertex);
      while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.pop();
      }
      std::cout << std::endl;
    }
  }

  void SearchMinPathTwoVertices() {
    int vertex1 = GetStartVertex(true), vertex2 = GetStartVertex(false);
    if (vertex1 != -1 && vertex2 != -1)
      std::cout << algorithms_.GetShortestPathBetweenVertices(graph_, vertex1,
                                                              vertex2);
  }

  void PrintGraph(std::vector<std::vector<int>> g) {
    size_t size = graph_.GetVertices();
    for (size_t i = 0; i < size; i++) {
      for (size_t j = 0; j < size; j++) std::cout << g[i][j] << " ";
      std::cout << std::endl;
    }
  }

  void SearchMinSpanningTree() {
    std::vector<std::vector<int>> tree =
        algorithms_.GetLeastSpanningTree(graph_);
    PrintGraph(tree);
  }

  void SearchMinPathAllVertices() {
    std::vector<std::vector<int>> path =
        algorithms_.GetShortestPathsBetweenAllVertices(graph_);
    PrintGraph(path);
  }

  void SolveSalesmanProblem() {
    TsmResult result = algorithms_.SolveTravelingSalesmanProblem(graph_);
    for (size_t i = 0; i < result.vertices.size() - 1; i++)
      std::cout << result.vertices[i] << " - ";
    std::cout << result.vertices.back() << std::endl;
    std::cout << result.distance << std::endl;
  }

  bool CheckEmptyGraph() {
    bool res = false;
    if (!graph_.IsEmpty())
      res = true;
    else
      std::cout << "Empty graph" << std::endl;
    return res;
  }

  void PrintOptions() {
    std::cout << std::endl;
    std::cout << "1. Load the original graph from a file" << std::endl;
    std::cout << "2. Traverse graph in breadth" << std::endl;
    std::cout << "3. Traverse graph in depth" << std::endl;
    std::cout << "4. Search for the shortest path between any two vertices"
              << std::endl;
    std::cout << "5. Search for the minimal spanning tree in the graph"
              << std::endl;
    std::cout
        << "6. Search for the shortest paths between all pairs of vertices"
        << std::endl;
    std::cout << "7. Solve the salesman problem" << std::endl;
    std::cout << "0. Exit" << std::endl;
  }
};
}  // namespace s21