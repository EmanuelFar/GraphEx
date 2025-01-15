# Graph Data Structure in C++

This project implements a **Graph** data structure in C++ using an adjacency matrix representation. The graph supports various operations such as adding and deleting vertices and edges, retrieving weights, and traversing connected vertices.

## Features
- **Add Vertex**: Add a new vertex to the graph.
- **Delete Vertex**: Remove a vertex from the graph, automatically adjusting the adjacency matrix.
- **Add Edge**: Add an edge between two vertices with a specified weight.
- **Delete Edge**: Remove an edge between two vertices.
- **Get Weight**: Retrieve the weight of an edge between two vertices.
- **Get Nearby Vertices**: Get a list of vertices directly connected to a given vertex.
- **Get All Linked Vertices**: Perform a breadth-first traversal to find all vertices connected to a given vertex.
- **Overloaded Operator**: Access edge weights using the `()` operator.
- **Graph Printing**: Use the overloaded `<<` operator to print the graph state.

## Class Diagram
```
Graph<T>
|
|-- std::vector<T> verticles
|-- std::vector<std::vector<int>> edges
|
|-- Graph(const Graph<T> &other)
|-- Graph<T> &operator=(const Graph<T> &other)
|-- bool addVerticle(const T &verticleName)
|-- bool deleteVerticle(const T &verticleName)
|-- bool addEdge(const T &startPoint, const T &endPoint, int value)
|-- bool deleteEdge(const T &startPoint, const T &endPoint)
|-- int getWeight(const T &startPoint, const T &endPoint) const
|-- std::string getNearbyVerticles(const T &startPoint) const
|-- std::string getAllLinkedVerticles(const T &startPoint)
|-- int operator()(int i, int j) const
|-- friend std::ostream &operator<<(std::ostream &out, const Graph<T> &g)
```

## Example Usage
```cpp
#include <iostream>
#include "Graph.h"

int main() {
    Graph<std::string> g;

    // Add vertices
    g.addVerticle("A");
    g.addVerticle("B");
    g.addVerticle("C");

    // Add edges
    g.addEdge("A", "B", 5);
    g.addEdge("B", "C", 3);

    // Print the graph
    std::cout << g;
    // Get weight of edge
    int weight = g.getWeight("A", "B");
    std::cout << "Weight between A and B: " << weight << std::endl;

    return 0;
}
```
## ** Pay Attention ! **
The Main is set to read files as arguments, each file contains a startPoint /t endPoint /t distance
Also there's a config file that compiles and and runs a test with all Example files provided in infiles directory.

## How to Compile
Use the following command to compile the project:
```bash
g++ -std=c++11 -o graph Graph.h main.cpp
```

## Project Structure
```
.
├── Graph.h        # Header file containing the Graph class template
├── main.cpp       # Example usage of the Graph class
└── README.md      # Project documentation
```

## How to Use
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/graph-data-structure.git
   ```
2. Navigate to the project directory:
   ```bash
   cd graph-data-structure
   ```
3. Compile the project:
   ```bash
   g++ -std=c++11 -o graph Graph.h main.cpp
   ```
4. Run the executable:
   ```bash
   ./graph
   ```

## Future Improvements
- Implement a depth-first traversal method.
- Add support for weighted undirected graphs.
- Optimize the adjacency matrix to use a sparse representation for large graphs.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## Contact
For any questions or suggestions, feel free to contact me at **[your.email@example.com](mailto:your.email@example.com)**.

