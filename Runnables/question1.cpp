
#include <bits/stdc++.h>

struct Vertex {
  int v;
  int weight;
};

std::vector<std::vector<Vertex>> read_graph(std::string filename) {
  // Read the graph from the file.
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  // Create a vector of vectors to store the graph.
  std::vector<std::vector<Vertex>> graph(1000);

  // Read the edges from the file.
  int u, v, weight;
  while (file >> u >> v >> weight) {
    graph[u].push_back({v, weight});
    graph[v].push_back({u, weight});
  }

  return graph;
}

int dijkstra(std::vector<std::vector<Vertex>> graph, int source, int target) {
  // Initialize the distances array.
  std::vector<int> distances(graph.size(), INT_MAX);
  distances[source] = 0;

  // Create a priority queue to store the vertices that have not yet been visited.
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
  queue.push({0, source});

  // While the queue is not empty, do the following:
  while (!queue.empty()) {
    // Pop the vertex with the shortest distance from the queue.
    int u = queue.top().second;
    queue.pop();

    // If the vertex is the target vertex, then return the distance to the vertex.
    if (u == target) {
      return distances[u];
    }

    // For each neighbor of u, do the following:
    for (Vertex edge : graph[u]) {
      int v = edge.v;
      int weight = edge.weight;

      // If the distance from the source vertex to v is greater than the distance from the source vertex to u plus the weight of the edge, then update the distance to v.
      if (distances[v] > distances[u] + weight) {
        distances[v] = distances[u] + weight;
        queue.push({distances[v], v});
      }
    }
  }

  return -1;
}

int main() {
  // Read the graph from the file.
  std::string filename = "graph.txt";
  auto graph = read_graph(filename);

  // Run Dijkstra's algorithm for 200 random queries.
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 200; i++) {
    int source = rand() % graph.size();
    int target = rand() % graph.size();
    dijkstra(graph, source, target);
  }
  end = std::chrono::high_resolution_clock::now();

  // Print the total runtime.
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "Total runtime: " << duration.count() << " seconds" << std::endl;

  return 0;
}
