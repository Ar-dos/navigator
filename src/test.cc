#include "gtest/gtest.h"
#include "s21_graph_algorithms.hpp"

TEST(depth_first_search_test, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_search.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  s21::Stack<int> result = a.DepthFirstSearch(g, 5);
  s21::Stack<int> answer({5, 2, 1, 3, 4, 6, 7});
  while (!result.empty()) {
    ASSERT_EQ(result.top(), answer.top());
    result.pop();
    answer.pop();
  }
}

TEST(breadth_first_search_test, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_search.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  s21::Queue<int> result = a.BreadthFirstSearch(g, 5);
  s21::Queue<int> answer({5, 2, 6, 1, 3, 7, 4});
  while (!result.empty()) {
    ASSERT_EQ(result.front(), answer.front());
    result.pop();
    answer.pop();
  }
}

TEST(shortest_path_two_vertices, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_shortests.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  int result = a.GetShortestPathBetweenVertices(g, 1, 6);
  ASSERT_EQ(result, 11);
}

TEST(shortest_path_all_vertices, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_shortests.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  std::vector<std::vector<int>> result =
      a.GetShortestPathsBetweenAllVertices(g);
  std::vector<std::vector<int>> answer = {
      {0, 7, 9, 0, 0, 11},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {11, 0, 2, 0, 9, 0}};
  for (size_t i = 0; i < g.GetVertices(); i++)
    for (size_t j = 0; j < g.GetVertices(); j++)
      ASSERT_EQ(result[i][j], answer[i][j]);
}

TEST(least_spanning_tree, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_tsm.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  std::vector<std::vector<int>> result = a.GetLeastSpanningTree(g);
  std::vector<std::vector<int>> answer = {
      {0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0}, {0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12},
      {0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 13}, {0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0},
      {0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0},  {0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0},
      {0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
      {0, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0}};
  for (size_t i = 0; i < g.GetVertices(); i++)
    for (size_t j = 0; j < g.GetVertices(); j++)
      ASSERT_EQ(result[i][j], answer[i][j]);
}

TEST(traveling_salesman_problem, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_shortests.txt";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  s21::TsmResult result = a.SolveTravelingSalesmanProblem(g);
  std::vector<int> answer;
  if (result.vertices[1] == 3)
    answer = std::vector<int>({1, 3, 6, 5, 4, 2, 1});
  else
    answer = std::vector<int>({1, 2, 4, 5, 6, 3, 1});
  ASSERT_EQ(answer, result.vertices);
  ASSERT_DOUBLE_EQ(result.distance, 48);
  filename = "../datasets/matrix_broken.txt";
  g.LoadGraphFromFile(filename);
  result = a.SolveTravelingSalesmanProblem(g);
  ASSERT_TRUE(result.vertices.empty());
  ASSERT_DOUBLE_EQ(result.distance, INFINITY);
}

TEST(exceptions, s21_graph_algorithms) {
  s21::Graph g;
  std::string filename = "";
  g.LoadGraphFromFile(filename);
  s21::GraphAlgorithms a;
  ASSERT_ANY_THROW(a.BreadthFirstSearch(g, 1));
  ASSERT_ANY_THROW(a.DepthFirstSearch(g, 1));
  ASSERT_ANY_THROW(a.GetLeastSpanningTree(g));
  ASSERT_ANY_THROW(a.GetShortestPathBetweenVertices(g, 1, 2));
  ASSERT_ANY_THROW(a.GetShortestPathsBetweenAllVertices(g));
  ASSERT_ANY_THROW(a.SolveTravelingSalesmanProblem(g));
}

TEST(export_to_dot, s21_graph) {
  s21::Graph g;
  std::string filename = "../datasets/matrix_shortests.txt";
  g.LoadGraphFromFile(filename);
  g.ExportGraphToDot("test.dot");
  std::ifstream file("test.dot");
  std::string result;
  std::getline(file, result);
  std::string answer = "graph test {";
  ASSERT_EQ(result, answer);
  for (size_t i = 1; i < 7; i++) {
    answer = "\t" + std::to_string(i) + ";";
    std::getline(file, result);
    ASSERT_EQ(result, answer);
  }
  answer = "\t1 -- 2;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t1 -- 3;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t1 -- 6;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t2 -- 3;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t2 -- 4;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t3 -- 4;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t3 -- 6;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t4 -- 5;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "\t5 -- 6;";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  answer = "}";
  std::getline(file, result);
  ASSERT_EQ(result, answer);
  file.close();
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
