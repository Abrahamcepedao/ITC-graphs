// Abraham Cepeda Oseguera
// A00827666
// Graph Class - Act 4.1.1 Grafo: sus representaciones - Matriz/Lista de Adyacencias

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Create class with its atributes and methods
template<class T>
class Graph{
    private:
        vector< vector<T> > adjList;
        vector<T> vertices;
        int qtyVertices;
        int qtyEdges;
        int findVertex(T vertex);
    public:
        Graph(vector< vector<T> > adjList, int qtyVertices, int qtyEdges);
        void print();
};

// Constructor
// Description: creates the graph based on the list, quantity of vertices and edges
// Input: list (list of adjacencies), qtyVertices (number of vertexes), qtyEdges (number of edges)
// Output: NA
// Complexity: O(n^2)
template <class T>
Graph<T>::Graph(vector< vector<T> > list, int qtyVertices, int qtyEdges){
    this->qtyVertices = qtyVertices;
    this->qtyEdges = qtyEdges;
    int source = 0, target = 1;
    // Add vertexes to its respective vector as well as the adjacencies
    for(vector<T> edge: list){
        T temp = edge[source];
        int pos = findVertex(temp);
        if(pos >= 0){
            adjList[pos].push_back(edge[target]);
        } else{
            vertices.push_back(temp);
            adjList.push_back(edge);
        }
    }
    // Add missing vertexes
    if(vertices.size() < qtyVertices){
        for(vector<T> edge: list){
            T temp = edge[target];
            int pos = findVertex(temp);
            if(pos < 0){
                vertices.push_back(temp);
                vector<T> tempVertex;
                tempVertex.push_back(temp);
                adjList.push_back(tempVertex);
            }
        }
    }
}

// Method: findVertex
// Description: looks inside the vertexes vector and attemps to find the given vertex
// Input: vertex (the vertex to be found)
// Output: the position of the vertex if found or else a -1
// Complexity: O(n) due to the find function
template<class T>
int Graph<T>::findVertex(T vertex){
    typename vector<T>::iterator it;
    it = find(vertices.begin(), vertices.end(), vertex);
    return (it != vertices.end() ? (it - vertices.begin()) : -1);
}

// Method: print
// Description: prints the adjacent list of each vertex
// Input: NA
// Output: the ajancent list of each vertex
// Complexity: O(n^2)
template<class T>
void Graph<T>::print(){
    for(vector<T> vertex: adjList){
        for(T node: vertex){
            cout << node << " ";
        }
        cout << "\n";
    }
}
