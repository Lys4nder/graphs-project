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

    

    
    

private:
    int vertex_;
    std::map<int, std::vector<int>> adjMap_;
    std::vector<std::vector<bool>> adjMat_;
    std::map<std::pair<int, int>, int> weightMap_;


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