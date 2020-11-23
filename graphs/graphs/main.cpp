// Abraham Cepeda Oseguera
// A00827666
// Main cpp file - Act 4.1.2 Grafo: sus representaciones y sus recorridos

#include  "Graph.h"
#include <vector>
int main(){
//    vector< vector<int> > list = {{0,3,4}, {0,4,8}, {1,6,5}, {2,6,9},{3,7,8},{4,2,3},{5,1,9},{5,6,7},{5,7,8},{7,5,9}};
    vector< vector<int> > list = {{0,2,1},{0,3,7},{1,2,1},{1,6,3},{1,5,4},{2,0,1},{2,1,1},{2,6,3},{3,0,7},{3,5,7},{3,7,1},{4,6,6},{5,1,4},{5,6,4},{5,3,7},{6,2,3},{6,2,3},{6,1,3},{6,5,4},{6,4,6},{6,7,6},{7,6,6},{7,3,1}};
    cout << "<---Graph--->\n";
    Graph<int> graph(list);
    graph.print();
    
    cout << "\n\n<---Graph DFS--->\n";
    graph.dfsP(0);
    
    cout << "\n\n<---Graph BFS--->\n";
    graph.bfsP(0);
    
    cout << "\n\n<---Shortest Path--->\n";
    graph.shortestPath(0);
    
    cout << "\n\n\n";
    
    return 0;
}
