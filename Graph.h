#ifndef EX4_GRAPH_H
#define EX4_GRAPH_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

/** Ex-4 in C++ class --..
 * Usage of the "Big Three", generics, vector, BFS.
 * */
// Directed Graph.
template <typename T> class Graph {
public:
  explicit Graph() = default;

  Graph(const Graph &other);
  Graph &operator=(const Graph &other);
  ~Graph() = default;

  bool addVerticle(const T &verticleName);
  bool deleteVerticle(const T &verticleName);
  bool addEdge(const T &startPoint, const T &endPoint, int value);
  bool deleteEdge(const T &startPoint, const T &endPoint);

  int getWeight(const T &startPoint, const T &endPoint) const;
  int operator()(int i, int j) const;

  int verticlesSize() const { return verticles.size(); }
  const T &getVerticleByIndex(int i) const { return verticles[i]; }

  // for a given startPoint, returns a string representing verticles that can be
  // reached within 1 step.
  std::string getNearbyVerticles(const T &startPoint) const;
  // for a given startPoint, returns all reachable point using BFS.
  std::string getAllLinkedVerticles(const T &startPoint);
  // for a given startPoint, returns all verticles that can reach startPoint.
  // within 1 step.
  std::string getLinkedtoVerticle(const T &startPoint) const;

  template <typename E>
  friend std::ostream &operator<<(std::ostream &out, const Graph<E> &other);

private:
  std::vector<T> verticles;
  std::vector<std::vector<int>> edges;
  void traverseGraph(std::vector<bool> &isConnected,
                     std::vector<std::vector<int>> &edgesDummy, int startIndex);
  int *getStartEndIndexes(const T &startPoint, const T &endPoint) const;
  int getSingleIndex(const T &point) const;
};

template <typename T> Graph<T>::Graph(const Graph<T> &other) {
  verticles = other.verticles;
  edges = other.edges;
}

template <typename T> Graph<T> &Graph<T>::operator=(const Graph<T> &other) {
  if (this == &other) {
    return *this;
  } else {
    verticles = other.verticles;
    edges = other.edges;
  }
  return *this;
}

template <typename T> bool Graph<T>::addVerticle(const T &verticleName) {
  for (int i = 0; i < int(verticles.size()); i++) {
    if (verticleName == verticles[i])
      return false;
  }
  T name = verticleName;
  verticles.emplace_back(name);

  // Add a new column in matrix
  for (int i = 0; i < int(edges.size()); i++) {
    edges[i].emplace_back(0);
  }
  // Add a new row in matrix
  std::vector<int> newRow(edges.size() + 1, 0);
  edges.emplace_back(newRow);
  return true;
}
// upon removing a verticle from the graph we shrink it  -- example 3x3 -> 2x2
template <typename T> bool Graph<T>::deleteVerticle(const T &verticleName) {
  if (int(verticles.size()) <= 0)
    return false;

  int indexToDelete = -1;
  for (int i = 0; i < int(verticles.size()); i++) {
    if (verticleName == verticles[i]) {
      indexToDelete = i;
      edges.erase(edges.begin() + i);
      verticles.erase(verticles.begin() + i);
      return true;
    }
  }
  // remove the specified position of the index in each vector in the matrix.
  for (int j = 0; j < int(edges.size()); j++) {
    edges[j].erase(edges[j].begin() + indexToDelete);
  }
  return false;
}

template <typename T> int Graph<T>::getSingleIndex(const T &point) const {
  for (int i = 0; i < int(verticles.size()); i++) {
    if (verticles[i] == point)
      return i;
  }
  return -1;
}

// gets a start and end as it returns their indexes in the verticles vector.
template <typename T>
int *Graph<T>::getStartEndIndexes(const T &startPoint,
                                  const T &endPoint) const {
  int *indexes = new int[2];
  int startIndex = -1;
  int endIndex = -1;
  for (int i = 0; i < int(verticles.size()); i++) {
    if (verticles[i] == startPoint) {
      startIndex = i;
    }
    if (verticles[i] == endPoint) {
      endIndex = i;
    }
  }
  indexes[0] = startIndex;
  indexes[1] = endIndex;
  return indexes;
}

template <typename T>
bool Graph<T>::addEdge(const T &startPoint, const T &endPoint, int value) {
  // Add an Edge between two Verticles, if Edge exists select minimum value.
  int *indexes = getStartEndIndexes(startPoint, endPoint);
  int startIndex = indexes[0];
  int endIndex = indexes[1];
  if (startIndex == -1 || endIndex == -1)
    return false;
  if (edges[startIndex][endIndex] > 0) {
    edges[startIndex][endIndex] = std::min(edges[startIndex][endIndex], value);
  } else {
    edges[startIndex][endIndex] = value;
  }
  delete[] indexes;
  return true;
}

template <typename T>
bool Graph<T>::deleteEdge(const T &startPoint, const T &endPoint) {
  int *indexes = getStartEndIndexes(startPoint, endPoint);
  int startIndex = indexes[0];
  int endIndex = indexes[1];
  if (startIndex == -1 || endIndex == -1)
    return false;
  edges[startIndex][endIndex] = 0;
  return true;
}

template <typename T>
int Graph<T>::getWeight(const T &startPoint, const T &endPoint) const {
  int *indexes = getStartEndIndexes(startPoint, endPoint);
  int startIndex = indexes[0];
  int endIndex = indexes[1];
  delete[] indexes;
  if (startIndex == -1 || endIndex == -1)
    return 0;
  return edges[startIndex][endIndex];
}

template <typename T>
std::string Graph<T>::getNearbyVerticles(const T &startPoint) const {
  std::ostringstream output;
  int pointIndex = getSingleIndex(startPoint);
  if (pointIndex == -1) {
    return output.str();
  }
  output << startPoint;
  for (int i = 0; i < int(edges.size()); i++) {
    if (edges[pointIndex][i] > 0) {
      output << '\t';
      output << verticles[i];
    }
  }
  return output.str();
}

template <typename T>
std::string Graph<T>::getAllLinkedVerticles(const T &startPoint) {
  std::ostringstream output;
  int pointIndex = getSingleIndex(startPoint);
  if (pointIndex == -1) {
    return output.str();
  }

  // Initialize the isConnected vector
  std::vector<bool> isConnected(verticles.size(), false);

  // Perform BFS traversal
  traverseGraph(isConnected, edges, pointIndex);

  // Build the output string
  output << verticles[pointIndex];
  for (int v = 0; v < isConnected.size(); v++) {
    if (isConnected[v] && v != pointIndex) {
      output << '\t' << verticles[v];
    }
  }
  return output.str();
}

template <typename T>
void Graph<T>::traverseGraph(std::vector<bool> &isConnected,
                             std::vector<std::vector<int>> &edgesDummy,
                             int startIndex) {
  std::queue<int> q;
  q.push(startIndex);
  isConnected[startIndex] = true;

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    for (int neighbor = 0; neighbor < edges.size(); ++neighbor) {
      // If there's an edge and the neighbor hasn't been visited yet
      if (edges[current][neighbor] > 0 && !isConnected[neighbor]) {
        isConnected[neighbor] = true;
        q.push(neighbor);
      }
    }
  }
}

template <typename T>
std::string Graph<T>::getLinkedtoVerticle(const T &startPoint) const {
  int pointIndex = getSingleIndex(startPoint);
  std::ostringstream output;
  output << verticles[pointIndex];
  for (int i = 0; i < verticles.size(); i++) {
    if (edges[i][pointIndex] > 0) {
      output << '\t';
      output << verticles[i];
    }
  }
  return output.str();
}

// replaces nested arrays access attribute.
template <typename T> int Graph<T>::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= int(edges.size()) || j >= int(edges.size()))
    return -1;
  return edges[i][j];
}

// prints the graph state.
template <typename T>
std::ostream &operator<<(std::ostream &out, const Graph<T> &g) {
  for (int i = 0; i < g.verticlesSize(); i++) {
    std::string text = g.getNearbyVerticles(g.verticles[i]);
    out << text;
    out << '\n';
  }
  return out;
}
#endif
