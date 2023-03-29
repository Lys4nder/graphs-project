#ifndef graph
#define graph
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

class Graph {
public:
    Graph(int vertex) : vertex_(vertex) {}

    void addVertex(int v) {
        adjMap_[v] = std::vector<int>();
    }

    void addEdge(int u, int v) {
        adjMap_[u].push_back(v);
        adjMap_[v].push_back(u);
    }

    void printGraph() {
        for (auto const& [v, adjList] : adjMap_) {
            std::cout << v << ": ";
            for (auto const& adj : adjList) {
                std::cout << adj << " ";
            }
            std::cout << '\n';
        }
    }

    void adjListToAdjMat() 
    {
        int index = 0;
        std::map<int, int> indexMap;

        for (auto const& [v, adjList] : adjMap_) {
            indexMap[v] = index++;
        }

        adjMat_.resize(indexMap.size(), std::vector<bool>(indexMap.size(), false));

        for (auto const& [v, adjList] : adjMap_) {
            int row = indexMap[v];
            for (auto const& adj : adjList) {
                if (indexMap.count(adj) > 0) {
                    int col = indexMap[adj];
                    adjMat_[row][col] = true;
                }
            }
        }
    }   

    void printAdjMat() {
        std::cout << "Adjacency Matrix:\n";
        for (auto const& row : adjMat_) {
            for (auto const& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << '\n';
        }
    }
    void deleteEmptyMapItems() {
        std::vector<int> emptyVertices;
        for (auto it = adjMap_.begin(); it != adjMap_.end(); ++it) {
            if (it->second.empty()) {
                emptyVertices.push_back(it->first);
            }
        }
        for (int vertex : emptyVertices) {
            adjMap_.erase(vertex);
        }
    }
    //conectivity
    void DFS_traversal(int start) {
        std::map<int, bool> visited;

        for (auto const& [v, adjList] : adjMap_) {
            visited[v] = false;
        }

        DFS(start, visited);
    }

    //shortest path
    void dijkstra(int start) {
        std::map<int, int> distances;
        std::map<int, bool> visited;
        std::map<int, std::vector<int>> path;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        for (auto const& [v, adjList] : adjMap_) {
            distances[v] = INT_MAX;
            visited[v] = false;
        }

        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            for (int v : adjMap_[u]) {
                int w = 1; // assuming all edges have weight 1
                if (distances[u] + w < distances[v]) {
                    distances[v] = distances[u] + w;
                    path[v] = path[u];
                    path[v].push_back(u);
                    pq.push({distances[v], v});
                }
            }
        }

        std::cout << "\nPath from " << start << " to:\n";
        for (auto const& [v, p] : path) {
            std::cout << v << ": ";
            if (distances[v] == INT_MAX) {
                std::cout << "No path found\n";
            } else {
                std::cout << start << " ";
                for (int u : p) {
                    std::cout << u << " ";
                }
                std::cout << v << " (size=" << distances[v] << ")\n";
            }
        }
    }

    bool hasHamiltonianCycle() {
        std::vector<int> path;
        std::vector<bool> visited(vertex_, false);
        path.push_back(0);
        visited[0] = true;
        return hasHamiltonianCycleUtil(1, path, visited);
    }

    bool hasHamiltonianCycleUtil(int count, std::vector<int>& path, std::vector<bool>& visited) {
        if (count == vertex_) {
            // all vertices are visited, check if there is a path back to starting vertex
            if (std::find(adjMap_[path.back()].begin(), adjMap_[path.back()].end(), 0) != adjMap_[path.back()].end()) {
                // there is a path back to starting vertex, so it forms a Hamiltonian cycle
                return true;
            } else {
                // there is no path back to starting vertex
                return false;
            }
        }
        for (int adj : adjMap_[path.back()]) {
            if (!visited[adj]) {
                visited[adj] = true;
                path.push_back(adj);
                if (hasHamiltonianCycleUtil(count + 1, path, visited)) {
                    // a Hamiltonian cycle is found
                    return true;
                }
                // backtrack
                visited[adj] = false;
                path.pop_back();
            }
        }
        // no Hamiltonian cycle found
        return false;
    }

    bool hasEulerianCycle() {
        // check if all vertices have even degree
        for (auto const& [v, adjList] : adjMap_) {
            if (adjList.size() % 2 != 0) {
                return false;
            }
        }
        // check if the graph is connected
        std::map<int, bool> visited;
        for (auto const& [v, adjList] : adjMap_) {
            visited[v] = false;
        }
        DFS(0, visited);
        for (auto const& [v, adjList] : adjMap_) {
            if (!visited[v]) {
                return false;
            }
        }
        // all vertices have even degree and the graph is connected, so it has an Eulerian cycle
        return true;
    }


    
private:
    int vertex_;
    std::map<int, std::vector<int>> adjMap_;
    std::vector<std::vector<bool>> adjMat_;


    void DFS(int v, std::map<int, bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";

        // Recur for all adjacent vertices
        for (int adj : adjMap_[v]) {
            if (!visited[adj]) {
                DFS(adj, visited);
            }
        }
    }
};

#endif