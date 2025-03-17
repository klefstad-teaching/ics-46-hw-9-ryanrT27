#include "dijkstras.h"
//dijkstra only likes positive weights !
// PSUEDO CODE FROM PROFESSORS WRITE UP
// vector<int> dijkstras_shortest_path(source, graph):
//     n = graph.adjacencyList.size()
//     graph.distance.resize(n, INT_MAX)
//     graph.previous.resize(n, -1)
//     graph.visited.resize(n, false)
//     priorityQueue pq
//     pq.push(Node(source, 0))
//     graph.distance[source] = 0
//     while !pq.empty():
//         current = pq.pop_top()
//         u = current.vertex
//         if graph.visited[u]:
//             continue
//         graph.visited[u] = true
//         for each neighbor in graph.adjacencyList[u]:
//             v = neighbor.vertex
//             weight = neighbor.weight
//             if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
//                 graph.distance[v] = graph.distance[u] + weight
//                 graph.previous[v] = u
//                 pq.push(Node(v, graph.distance[v]))

// end function
vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int>& previous){
    // previous? store previous node for each vertex 
    int n_verts = G.size();
    //stores shortest dist from SOURCE to each node, keeping track of the lowest cost to reach each node
    vector<int> distance(n_verts, INF);
    //keeps track of nodes visited
    vector<bool> been_visited(n_verts, false);
    // keeps track of shorted path by storing predecessor, so start with -1
    previous.assign(n_verts, -1);

    // stores PAIRS (Dist, vertex) as they get sorted by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //source node always has 0 dist to itself
    distance[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int vert = pq.top().second;
        //gets node from top (which should be smallest distance)
        // second pulls the vertex from the pair that the pq returns because that is the node whose closest unvisited neighbor we want to find
        pq.pop();
        if (been_visited[vert]) continue; // if visited skip that boi
        been_visited[vert] = true;
        //iter through neighbors of current vertex
        for (const Edge &neighbor : G[vert]) {
            int destin = neighbor.dst;
            int weigh = neighbor.weight;
            // check for shorter path to destination; if exists, update distance with shortest, curr vertex becomes predecessor and push into priority q
            if (!been_visited[destin] && distance[vert] + weigh < distance[destin]) {
                distance[destin] = distance[vert] + weigh;
                previous[destin] = vert;
                pq.push({distance[destin], destin});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    if (destination == 0) return {0};
    
    vector<int> shortest_path;
    // traversing previous to construct path
    for (int curr = destination; curr != -1; curr = previous[curr])
        shortest_path.push_back(curr);
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

void print_path(const vector<int>& v, int total){
    if (v.empty()) {
        cout << total << endl << "Total cost is " << total << endl;
        return;
    }
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << endl << "Total cost is " << total << endl;


}