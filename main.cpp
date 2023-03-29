#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include "graph.hpp"

std::vector<std::vector<std::string>> data;
std::vector<std::vector<std::string>> data2;
std::ifstream file;
std::ifstream file2;

void readFile1()
{
    int i = 0;
    std::string line;
    //10.000.000
    while (i<100.000) 
    {
        std::getline(file, line);
        std::vector<std::string> row;
        std::string value;
        std::stringstream ss(line);

        while (std::getline(ss, value, ',')) 
        {
            row.push_back(value);
        }
        data.push_back(row);

        i++;
    }
    std::cout << "Read from file 1 done\n";
}

void readFile2()
{
    int i = 0;
    std::string line;
    while (i<100.000) 
    {   
        std::getline(file2, line);
        std::vector<std::string> row;
        std::string value;
        std::stringstream ss(line);

        while (std::getline(ss, value, ',')) 
        {
            row.push_back(value);
        }        
        data2.push_back(row);

        
        
        i++;
    }
    std::cout << "Read from file 2 done\n";
}
int main()
{
    std::cout << "Reading from files...\n";
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    file.open("../nodes.csv");
    file2.open("../edges.csv");

    std::thread reader1(readFile1);
    std::thread reader2(readFile2);

    reader1.join();
    reader2.join();

    file.close();
    file2.close();

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    std::cout << "It took " << time_span.count() / 1000 << "s to read the data\n";

    t1 = std::chrono::high_resolution_clock::now();

    Graph g(100.000);
    for (const auto& row : data) {
        g.addVertex(std::stoi(row[0]));
    }

    for (const auto& row : data2) {
        g.addEdge(std::stoi(row[0]), std::stoi(row[1]));
    }
    g.deleteEmptyMapItems();
    t2 = std::chrono::high_resolution_clock::now();
    time_span = t2 - t1;
    std::cout << "It took " << time_span.count() / 1000 << "s to create the graph\n";
    std::cout << "Waiting 3s before printing...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    //g.printGraph();
    //g.DFS_traversal(1);
    //g.dijkstra(6);
    std::cout << "Hamiltonian cycle: "<< g.hasHamiltonianCycle() << '\n';
    std::cout << "Eulerian cycle: " << g.hasEulerianCycle() << '\n';

    
}