// Abraham Cepeda Oseguera
// A00827666
// Main cpp file - Act 4.2 Grafos: Algoritmos complementarios

#include  "Graph.h"
#include <vector>

// Function: checkInt
// Description: validates input to be of type (int)
// Input: NA
// Output: validated number
// Complexity: best case O(1), worst case O(n) - depends on the user input
int checkInt(){
    int num;
    cin >> num;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Input must be a number.. try again: ";
            cin >> num;
        }
        if(!cin.fail()){
            break;
        }
    }
    return num;
}

// Function: checkIntR
// Description: validates input to be of type (int) and in the range of the given values
// Input: min (minimum value), max (maximum value)
// Output: validated number
// Complexity: best case O(1), worst case O(n) - depends on the user input
int checkIntR(int min, int max){
    int num;
    cin >> num;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Input must be a number.. try again: ";
            cin >> num;
        }
        if(!cin.fail()){
            if(num < min || num > max){
                cout << "Enter a valid number: ";
                cin >> num;
            } else{
                break;
            }
        }
    }
    return num;
}


int main(){
    vector< vector<int> > list;
    int ans;
    cout << "---> Welcome to the complementary algorithms of graphs program!\n\n";
    cout << "Do you want to use a predifined list or do you prefer to enter one?\n";
    cout << "1. Predifined list\n";
    cout << "2. New list\n";
    ans = checkIntR(1, 2);
    
    if(ans == 1){
        list = {{0,1,1},{0,3,2},{1,0,3},{1,2,4},{2,1,5},{2,3,6},{3,0,7},{3,2,8}};  // is bipartite
    } else{
        int vertex, adjacent, weight;
        bool continuee = true;
        while(continuee){
            cout << "Adding new edge..\n\n";
            vector<int> edge;
            cout << "Enter the vertex: ";
            vertex = checkInt();
            cout << "Enter the adjacent: ";
            adjacent = checkInt();
            cout << "Enter the weight: ";
            weight = checkInt();
            edge.push_back(vertex);
            edge.push_back(adjacent);
            edge.push_back(weight);
            list.push_back(edge);
            edge.clear();
            cout << "Do you want to add another edge?\n";
            cout << "1. Yes\n";
            cout << "2. No\n";
            ans = checkIntR(1, 2);
            continuee = ans == 1;
        }
    }
    
    
    
    cout << "<---Graph--->\n";
    Graph<int> graph(list);
    graph.print();
    
    cout << "\n\n<---Graph DFS--->\n";
    graph.dfsP(0);
    
    cout << "\n\n<---Graph BFS--->\n";
    graph.bfsP(0);
    
    cout << "\n\n<---Shortest Path--->\n";
    graph.shortestPath(0);
    
    cout << "\n\n<---Topological sort--->\n";
    graph.topologicalSort();
    
    cout << "\n\n<---Is Bipartite--->\n";
    cout << (graph.isBipartite() ? "Is bipartite\n" : "Is not bipartite\n");
    
    cout << "\n\n\n";
    
    return 0;
}
