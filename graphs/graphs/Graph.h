// Abraham Cepeda Oseguera
// A00827666
// Graph Class - Act 4.1.2 Grafo: sus representaciones y sus recorridos

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
    public:
        Graph(vector< vector<T> > list);
        void print();
        void bfs();
        void dfs();
        void bfsP(T vertex);
        void dfsP(T vertex);
        void shortestPath(T vertex);
    void topologicalSort();
};



// Constructor
// Description: creates the graph based on the list, quantity of vertices and edges
// Input: list (list of adjacencies), qtyVertices (number of vertexes), qtyEdges (number of edges)
// Output: NA
// Complexity: O(n^2)
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
// Output: the ajancent list of each vertex
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


template<class T>
void Graph<T>::dfs(){
    vector<bool> status(vertices.size(), false);
    dfsR(vertices[0], status);
    cout << "\n";
}

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


template<class T>
void Graph<T>::dfsP(T vertex){
    int pos = findVertex(vertex);
    if(pos >= 0){
        vector<bool> status(vertices.size(), false);
        dfsR(vertices[pos], status);
        cout << "\n";
    }
    
}

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


template<class T>
void Graph<T>::topologicalSortR(int n, vector<bool> &status, stack<int> &s){
    status[n] = true;
    int pos = findVertex(vertices[n]);
    for(int i  = 0; i < adjList[pos]; i++){
        int posAd =  findVertex(adjList[pos][i]);
        if(!status[posAd]){
            topologicalSortR(posAd, status, s);
        }
    }
    s.push(n);
}

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
