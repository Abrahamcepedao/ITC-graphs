// Abraham Cepeda Oseguera
// A00827666
// GraphM Class - Act 4.1.1 Grafo: sus representaciones - Matriz/Lista de Adyacencias

#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

// Create class with its atributes and methods
template<class T>
class GraphM{
    private:
        vector< vector<bool> >  adjMatrix;
        vector<T> vertices;
        int qtyVertices;
        int qtyEdges;
        int findVertex(T vertex);
    void dfsR(T vertex, vector<bool> &status);
    public:
        GraphM(vector< vector<T> > list, int qtyVertices, int qtyEdges);
        void print();
        void bfs();
        void dfs();
};

// Constructor
// Description: creates the graph based on the list, quantity of vertices and edges
// Input: list (list of adjacencies), qtyVertices (number of vertexes), qtyEdges (number of edges)
// Output: NA
// Complexity: O(n^2)
template <class T>
GraphM<T>::GraphM(vector< vector<T> > list, int qtyVertices, int qtyEdges){
    this->qtyVertices = qtyVertices;
    this->qtyEdges = qtyEdges;
    int source = 0, target = 1;
    // Adding falses (adjMatrix)";
    for(int i = 0; i < qtyVertices; i++){
        vector<bool> temp;
        for(int j = 0; j < qtyVertices; j++){
            temp.push_back(false);
        }
        adjMatrix.push_back(temp);
    }
    // Adding vertexes to the corresponding vector
    for(vector<T> edge: list){
        T temp = edge[source];
        int pos = findVertex(temp);
        if(pos < 0){
            vertices.push_back(temp);
        }
        temp = edge[target];
        pos = findVertex(temp);
        if(pos < 0){
            vertices.push_back(temp);
        }
    }
    // Switch to "true" the adjMatrix at the corresponding positions
    sort(vertices.begin(), vertices.end());
    for(vector<T> edge: list){
        int posSource = findVertex(edge[source]);
        int posTarget = findVertex(edge[target]);
        adjMatrix[posSource][posTarget] = true;
    }
}

// Method: findVertex
// Description: looks inside the vertexes vector and attemps to find the given vertex
// Input: vertex (the vertex to be found)
// Output: the position of the vertex if found or else a -1
// Complexity: O(n) due to the find function
template<class T>
int GraphM<T>::findVertex(T vertex){
    typename vector<T>::iterator it;
    it = find(vertices.begin(), vertices.end(), vertex);
    return it != vertices.end() ? (it - vertices.begin()) : -1;
}


// Method: print
// Description: prints the matrix of adjancencies with either false or true
// Input: NA
// Output: the matrix of adjancecies (T/F)
// Complexity: O(n^2)
template<class T>
void GraphM<T>::print(){
    cout << "  ";
    for(T vertex: vertices){
        cout << vertex << " ";
    }
    cout << "\n";
    for(int i = 0; i < qtyVertices; i++){
        cout << vertices[i] << " ";
        for(int j = 0; j < qtyVertices; j++){
            cout << (adjMatrix[i][j] ? "T " : "F ");
        }
        cout << "\n";
    }
}


template<class T>
void GraphM<T>::bfs(){
    vector<bool> status(vertices.size(), false);
    queue<T> q;
    q.push(vertices[0]);
    status[0] = true;
    while (!q.empty()) {
        T vertex = q.front();
        cout << vertex << " ";
        int pos = findVertex(vertex);
        for(int i = 0; i < vertices.size(); i++){
            if(adjMatrix[pos][i]){
                if(!status[i]){
                    q.push(vertices[i]);
                    status[i] = true;
                }
            }
        }
        q.pop();
    }
    cout << "\n";
}



template<class T>
void GraphM<T>::dfs(){
    vector<bool> status(vertices.size(), false);
    dfsR(vertices[0], status);
}

template<class T>
void GraphM<T>::dfsR(T vertex, vector<bool> &status){
    int pos = findVertex(vertex);
    if(!status[pos]){
        cout << vertex << " ";
        status[pos] = true;
        for(int i = 0; i < vertices.size(); i++){
            if(adjMatrix[pos][i]){
                if(!status[i]){
                    dfsR(vertices[i], status);
                }
            }
        }
    }
    
}
