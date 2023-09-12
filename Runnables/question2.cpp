
#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int u, v, weight;
};

// A* algorithm
int a_star(vector<vector<Edge>> graph, int source, int target) {
  // Initialize the distances array.
  vector<int> distances(graph.size(), INT_MAX);
  distances[source] = 0;

  // Create a priority queue to store the vertices that have not yet been visited.
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
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

    // For each neighbor of the vertex, do the following:
    for (Edge edge : graph[u]) {
      int v = edge.v;
      int weight = edge.weight;

      // Calculate the estimated cost of the path from the source vertex to v.
      int estimated_cost = distances[u] + weight;

      // If the distance from the source vertex to v is greater than the estimated cost, then update the distance to v.
      if (distances[v] > estimated_cost) {
        distances[v] = estimated_cost;
        queue.push({distances[v], v});
      }
    }
  }

  return -1;
}