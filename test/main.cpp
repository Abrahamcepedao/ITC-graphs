// Abraham Cepeda Oseguera
// A00827666
// Main cpp file - Act 4.1.1 Grafo: sus representaciones - Matriz/Lista de Adyacencias

#include  "Graph.h"
#include  "GraphM.h"
#include <vector>
int main(){
    vector< vector<char> > list = {{'a', 'b'}, {'a', 'c'}, {'a', 'e'}, {'b', 'a'}, {'b', 'd'}, {'c', 'a'}, {'c', 'd'}, {'d', 'b'}, {'d', 'c'}, {'d', 'e'}, {'e', 'a'}, {'e', 'd'}};
    vector< vector<char> > list2 = {{'A','B'},{'A','E'},{'A','H'},{'B','A'},{'B','C'},{'B','E'},{'C','B'},{'C','D'},{'C','E'},{'C','F'},{'D','C'},{'E','A'},{'E','B'},{'E','C'},{'E','G'},{'E','H'},{'F','C'},{'F','J'},{'G','E'},{'G','J'},{'H','A'},{'H','E'},{'H','I'},{'H','J'},{'I','H'},{'J','F'},{'J','G'},{'J','H'}};
    cout << "<---Graph--->\n";
    Graph<char> graph(list, 5, 12);
    graph.print();
    
    cout << "\n\n<---GraphM--->\n";
    GraphM<char> graphM(list, 5, 12);
    graphM.print();
    
    
    cout << "\n\n<---Graph2--->\n";
    Graph<char> graph2(list2, 10, 26);
    graph2.print();
    cout << "\n<-DFS->\n";
    graph2.dfs();
    
    cout << "\n\n<---GraphM2--->\n";
    Graph<char> graphM2(list2, 10, 26);
    graphM2.print();
    cout << "\n<-DFS->\n";
    graphM2.dfs();

//    vector< vector<char> > list3 = {{'A','B'},{'A','E'},{'A','H'},{'B','A'},{'B','C'},{'B','E'},{'C','B'},{'C','D'},{'C','E'},{'C','F'},{'D','C'},{'E','A'},{'E','B'},{'E','C'},{'E','G'},{'E','H'},{'F','C'},{'F','J'},{'G','E'},{'G','J'},{'H','A'},{'E','A'},{'H','E'},{'H','I'},{'H','J'},{'I','H'},{'J','F'},{'J','G'},{'J','H'}};
    return 0;
}
