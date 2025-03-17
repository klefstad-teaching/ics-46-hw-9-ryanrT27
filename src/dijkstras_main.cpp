#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> prev;
    int source = 0;
    vector<int> distances = dijkstra_shortest_path(G, source, prev);
    for (int i = 0; i < G.numVertices; ++i){
        vector<int> shortest = extract_shortest_path(distances, prev, i);
        print_path(shortest, distances[i]);
    }
    return 0;
    //

}