# Navigator

Implementation of the Navigator project.

Within this task, all graphs must meet the following requirements:
- Edge weights are only natural numbers
- There may be loops
- Weights may differ on all edges
- Only a nonzero connected graph

Implementation of the _s21_graph.h_  library:  
* The library must be developed in C++ language of C++17 standard
* The library code must be located in the src folder in the develop branch  
* When writing code it is necessary to follow the Google style
* Make it as a static library (with the _s21_graph.h_ header file)
* The library must be represented as a `Graph` class that stores information about the graph using an **adjacency matrix**. The dimensionality of the adjacency matrix should be set dynamically when initializing the graph (when loading it from a file)
* The program must be built with Makefile which contains standard set of targets for GNU-programs: _all, clean, test, s21_graph.a_
*Prepare full coverage of the `Graph` class methods with unit-tests
* The class `Graph` must contain at least the following public methods:
    + `LoadGraphFromFile(string filename)` - loading a graph from a file in the adjacency matrix format
    + `ExportGraphToDot(string filename)`- exporting a graph to a dot file (see materials)

Implementation of the _s21_graph_algorithms.h_ library:  
* The library must be developed in C++ language of C++17 standard
* The library code must be located in the src folder in the develop branch  
* Make it as a static library (with the _s21_graph_algorithms.h_ header file)
* The library must be represented as a ` GraphAlgorithms ` class that stores the implementation of algorithms on graphs. The class `GraphAlgorithms` itself must not know anything about the internal representation of the graph from the class `Graph`. To interact with graph data, the class `GraphAlgorithms` can only use the public methods and properties provided by the `Graph` class. 
* Add to the Makefile _s21_graph_algorithms.a_ target 
*Prepare full coverage of the `GraphAlgorithms` class methods with unit-tests
* The class ` GraphAlgorithms ` must contain at least the following public methods:
    + `DepthFirstSearch(Graph &graph, int start_vertex)` - a *non-recursive* depth-first search in the graph from a given vertex. The function should return an array that contains the traversed vertices in the order they were traversed. When implementing this function, you must use the *self-written* data structure **stack**, which should be previously made as a separate static library
    + `BreadthFirstSearch(Graph &graph, int start_vertex)` - breadth-first search in the graph from a given vertex. The function should return an array that contains the traversed vertices in the order they were traversed. When implementing this function, you must use the *self-written* data structure **queue**, which should be previously made as a separate static library
     + `GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)` - searching for the shortest path between two vertices in a graph using *Dijkstra's algorithm*. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them
    + `GetShortestPathsBetweenAllVertices(Graph &graph)` - searching for the shortest paths between all pairs of vertices in a graph using the *Floyd-Warshall algorithm*. As a result, the function returns the matrix of the shortest paths between all vertices of the graph
    + `GetLeastSpanningTree(Graph &graph)` - searching for the minimal spanning tree in a graph using *Prim's algorithm*. As a result, the function should return the adjacency matrix for the minimal spanning tree
    + `SolveTravelingSalesmanProblem(Graph &graph)` - solving the traveling salesman's problem using the *ant colony algorithm*.
You need to find the shortest path that goes through all vertices of the graph at least once, followed by a return to the original vertex. As a result, the function should return the `TsmResult` structure.

*In this and the following tasks, consider that the vertex numbers start from 1*


Console interface

* You need to write the main program, which is a console application for testing the functionality of the implemented s21_graph.h and s21_graph_algorithms.h libraries 
* The console interface must provide the following functionality:
    1. loading the original graph from a file
    2. graph traversal in breadth with output of the result to the console   
    3. graph traversal in depth with output of the result to the console
    4. searching for the shortest path between any two vertices and displaying the result to the console
    5. searching for the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
    6. searching for the minimal spanning tree in the graph with the output of the resulting adjacency matrix to the console
    7. solving the salesman problem with the output of the resulting route and its length to the console
