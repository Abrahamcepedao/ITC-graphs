// Abraham Cepeda Oseguera
// A00827666
// Graph Class - Act 4.2 Grafos: Algoritmos complementarios

#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
struct Edge {
    T vertex;
    int weight;
};

// Create class with its atributes and methods
template<class T>
class Graph{
    private:
        vector< vector< Edge<T> > > adjList;
        vector<T> vertices;
        int qtyVertices;
        int qtyEdges;
        int findVertex(T vertex);
        void dfsR(T vertex, vector<bool> &status);
        int minWeight(vector<int> weight, vector<bool> status);
        void topologicalSortR(int n, vector<bool> &status, stack<int> &s);
        bool isBipartiteR(int n, vector<int> &colors, int color);
    public:
        Graph(vector< vector<T> > list);
        void print();
        void bfs();
        void dfs();
        void bfsP(T vertex);
        void dfsP(T vertex);
        void shortestPath(T vertex);
        void topologicalSort();
        bool isBipartite();
};



// Constructor
// Description: creates the graph based on the list, quantity of vertices and edges
// Input: list (list of adjacencies)
// Output: NA
// Complexity: O(n)
template <class T>
Graph<T>::Graph(vector< vector<T> > list){
    int source = 0, target = 1, weight = 2;
    // Add vertexes to its respective vector as well as the adjacencies
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
    sort(vertices.begin(), vertices.end());
    
    for(auto vertex: vertices){
        vector< Edge<T> > temp;
        Edge<T> edge;
        edge.vertex = vertex;
        edge.weight = 0;
        temp.push_back(edge);
        adjList.push_back(temp);
    }
    
    vector< Edge<T> > temp;
    vector< vector< Edge<T> > > tempList(vertices.size(), temp);
    adjList = tempList;
    
    for(auto path: list){
        int pos = findVertex(path[source]);
        Edge<T> edge;
        edge.vertex = path[target];
        edge.weight = path[weight];
        adjList[pos].push_back(edge);
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
    return (it != vertices.end() ? (int(it - vertices.begin())) : -1);
}

// Method: print
// Description: prints the adjacent list of each vertex
// Input: NA
// Output: the adjacent list of each vertex
// Complexity: O(n^2)
template<class T>
void Graph<T>::print(){
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i] << " --> ";
        for(auto edge: adjList[i]){
            cout << "{" <<  edge.vertex << "|" << edge.weight << "} ";
        }
        cout << "\n";
    }
}

// Method: bfs
// Description: prints the breath first
// Input: NA
// Output: the breath first order of vertexes
// Complexity: O(n^2)
template<class T>
void Graph<T>::bfs(){
    vector<bool> status(vertices.size(), false);
    queue<T> q;
    q.push(vertices[0]);
    status[0] = true;
    while (!q.empty()) {
        T vertex = q.front();
        cout << vertex << " ";
        int pos = findVertex(vertex);
        for(auto adj : adjList[pos]){
            pos = findVertex(adj.vertex);
            if(!status[pos]){
                q.push(adj.vertex);
                status[pos] = true;
            }
        }
        q.pop();
    }
    cout << "\n";
}


// Method: dfs
// Description: calls dfsR with the initial status and first vertex
// Input: NA
// Output: NA
// Complexity: O(1)
template<class T>
void Graph<T>::dfs(){
    vector<bool> status(vertices.size(), false);
    dfsR(vertices[0], status);
    cout << "\n";
}

// Method: dfsR
// Description: prints the depth first order of the vertexes
// Input: NA
// Output: NA
// Complexity: O(n^2)
template<class T>
void Graph<T>::dfsR(T vertex, vector<bool> &status){
    int pos = findVertex(vertex);
    if(!status[pos]){
        cout << vertex << " ";
        status[pos] = true;
        for(auto adj: adjList[pos]){
            int posAd = findVertex(adj.vertex);
            !status[posAd] ? dfsR(adj.vertex, status) : void();
        }
    }

}

// Method: bfsP
// Description: prints the breath first starting at the given vertex
// Input: vertex (the starting vertex)
// Output: the breath first order of vertexes
// Complexity: O(n^2)
template<class T>
void Graph<T>::bfsP(T vertex){
    vector<bool> status(vertices.size(), false);
    queue<T> q;
    int pos = findVertex(vertex);
    if(pos >= 0){
        q.push(vertices[pos]);
        status[pos] = true;
        while (!q.empty()) {
            T vertex = q.front();
            cout << vertex << " ";
            pos = findVertex(vertex);
            for(auto adj : adjList[pos]){
                pos = findVertex(adj.vertex);
                if(!status[pos]){
                    q.push(adj.vertex);
                    status[pos] = true;
                }
            }
            q.pop();
        }
        cout << "\n";
    }
}


// Method: dfs
// Description: calls dfsR with the initial status and the given vertex
// Input: vertex (the starting vertex)
// Output: NA
// Complexity: O(1)
template<class T>
void Graph<T>::dfsP(T vertex){
    int pos = findVertex(vertex);
    if(pos >= 0){
        vector<bool> status(vertices.size(), false);
        dfsR(vertices[pos], status);
        cout << "\n";
    }
    
}

// Method: minWeight
// Description: calculates the edge with the minimun weight
// Input: weight (vector containing the weight of each vertex, status (the status of each vertex)
// Output: pos (position of vertex with minimun weight)
// Complexity: O(n)
template<class T>
int Graph<T>::minWeight(vector<int> weight, vector<bool> status){
    int min = INT_MAX;
    int pos = -1;
    for(int i = 0; i < vertices.size(); i++){
        if(!status[i]){
            if(min > weight[i]){
                pos = i;
                min = weight[i];
            }
        }
    }
    return pos;
}

// Method: shortestPath
// Description: prints the wieght of each path given the initial vertex
// Input: vertex (The initial vertex)
// Output: NA
// Complexity: O(n^2)
template<class T>
void Graph<T>::shortestPath(T vertex){
    int pos = findVertex(vertex);
    if(pos >= 0){
        vector<bool> status(vertices.size(), false);
        vector<int> weight(vertices.size(), INT_MAX);
        vector<int> path(vertices.size(), -1);
        weight[pos] = 0;
        int next = pos;
        while(next >= 0){
            status[next] = true;
            for(int i = 0; i < adjList[next].size(); i++){
                int posAd = findVertex(adjList[next][i].vertex);
                if(!status[posAd]){
                    if(weight[posAd] > (weight[next] + adjList[next][i].weight)){
                        weight[posAd] = weight[next] + adjList[next][i].weight;
                        path[posAd] = next;
                    }
                }
            }
            next = minWeight(weight, status);
        }
        
        for(int i = 0; i < vertices.size(); i++){
            stack<int> s;
            s.push(i);
            int p = path[i];
            while(p >= 0){
                s.push(p);
                p = path[p];
            }
            int times = int(20 - s.size()*2);
            while(!s.empty()){
                cout << s.top() << " ";
                s.pop();
            }
            for(int j = 0; j < times; j++){
                cout << ".";
            }
            cout << "weight: " << weight[i] << "\n";
        }
    }
}


// Method: topologicalSortR
// Description: sort the vertex in topological order
// Input: n (number of vertex in listof vertexes), status (status of each vertex), s (stack of vertex in topological order)
// Output: NA
// Complexity: O(n)
template<class T>
void Graph<T>::topologicalSortR(int n, vector<bool> &status, stack<int> &s){
    status[n] = true;
    int pos = findVertex(vertices[n]);
    for(int i  = 0; i < adjList[pos].size(); i++){
        int posAd =  findVertex(adjList[pos][i].vertex);
        if(!status[posAd]){
            topologicalSortR(posAd, status, s);
        }
    }
    s.push(vertices[n]);
}

// Method: topologicalSort
// Description: calls topologicalSortR for each vertex with its number, the current status and the current stack. Then prints the final stack
// Input: NA
// Output: NA
// Complexity: O(n)
template<class T>
void Graph<T>::topologicalSort(){
    vector<bool> status(vertices.size(), false);
    stack<int> s;
    for(int i = 0; i < vertices.size(); i++){
        if(!status[i]){
            topologicalSortR(i, status, s);
        }
    }
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
}

// Method: isBipartiteR
// Description: checks if adjacent vertex of a given vertex are colored or not. If colored checks if they are alike
// Input: n (number of vertex to check), colors (vectors of colors), color (current color)
// Output: boolean (false if is not bipartite, true if bipartite)
// Complexity: O(n)
template<class T>
bool Graph<T>::isBipartiteR(int n, vector<int> &colors, int color){
    if(colors[n] != 0){
        return colors[n] == color;
    } else{
        colors[n] = color;
        for(int i = 0; i < adjList[n].size(); i++){
            if(!isBipartiteR(findVertex(adjList[n][i].vertex), colors, -color)){
                return false;
            }
        }
    }
    return true;
}

// Method: isBipartite
// Description: calls isBipartite for each vertex if not colored
// Input: NA
// Output: boolean (false if is not bipartite, true if bipartite)
// Complexity: O(n)
template<class T>
bool Graph<T>::isBipartite(){
    vector<int> colors(vertices.size(), 0);
    for(int i = 0; i < vertices.size(); i++){
        if(colors[i] == 0 && !isBipartiteR(i, colors, 1)){
            return false;
        }
    }
    return true;
}
