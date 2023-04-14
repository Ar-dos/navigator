#include <fstream>
#include <iostream>
#include <vector>

namespace s21 {
class Graph {
 public:
  Graph() : vertices_(0), weighted_(false), oriented_(false) {}

  bool IsEmpty() { return (vertices_ == 0 ? true : false); }

  int GetIndex(int i, int j) { return indices_[i][j]; }

  size_t GetVertices() { return vertices_; }

  bool GetWeighted() { return weighted_; }

  bool GetOriented() { return oriented_; }

  void LoadGraphFromFile(std::string filename) {
    std::ifstream file(filename.c_str());
    file >> vertices_;
    indices_ = std::vector(vertices_, std::vector<int>(vertices_));
    for (size_t i = 0; i < vertices_; i++)
      for (size_t j = 0; j < vertices_; j++) file >> indices_[i][j];
    file.close();
    SetType();
  }

  void ExportGraphToDot(std::string filename) {
    std::ofstream file(filename.c_str());
    file << "graph " << filename.substr(0, filename.length() - 4) << " {"
         << std::endl;
    for (size_t i = 0; i < vertices_; i++)
      file << "\t" << i + 1 << ";" << std::endl;
    std::string connection;
    oriented_ ? connection = " -> " : connection = " -- ";
    for (size_t i = 0, j = 0; i < vertices_; i++) {
      if (!oriented_) j = i;
      for (; j < vertices_; j++)
        if (indices_[i][j] > 0)
          file << "\t" << i + 1 << connection << j + 1 << ";" << std::endl;
    }
    file << "}" << std::endl;
    file.close();
  }

  void Print() {
    if (weighted_)
      std::cout << "Weighted ";
    else
      std::cout << "Unweighted ";
    if (oriented_)
      std::cout << "Oriented ";
    else
      std::cout << "Unoriented ";
    std::cout << std::endl;
    for (size_t i = 0; i < vertices_; i++) {
      for (size_t j = 0; j < vertices_; j++) std::cout << indices_[i][j] << " ";
      std::cout << std::endl;
    }
  }

 private:
  size_t vertices_;
  std::vector<std::vector<int>> indices_;
  bool weighted_;
  bool oriented_;

  void SetType() {
    weighted_ = false;
    oriented_ = false;
    for (size_t i = 0; i < vertices_; i++)
      for (size_t j = 0; j < vertices_; j++) {
        if (indices_[i][j] != indices_[j][i]) oriented_ = true;
        if (indices_[i][j] > 1) weighted_ = true;
      }
  }
};

}  // namespace s21
