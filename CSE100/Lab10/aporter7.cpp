#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u; 
    int v; 
    int w;
};

struct Graph {
    struct Edge* edge;
};

int findMin(int i1, int i2) {
    if(i1 < i2) 
        return i1;
    else
        return i2;
}


void bellmanFord(Graph* graph, int vertices, int edges) {
    int* distance = new int(vertices);
    for(int i = 0; i < vertices; i++) {
        distance[i] = 2147483647;
    }
    distance[0] = 0;
    int src; int dest; int weight; int temp;
    for(int i = 1; i < vertices-1; i++) {
        for(int j = 0; j < edges; j++) {
            src = graph->edge[j].u;
            dest = graph->edge[j].v;
            weight = graph->edge[j].w;
            if(distance[src] != 2147483647)
                distance[dest] = findMin(distance[dest], distance[src] + weight);
            
        }
    }
    //Checks for a negative cycle
    bool negCycle = false;
    for(int j = 0; j < edges; j++) {
        src = graph->edge[j].u;
        dest = graph->edge[j].v;
        temp = distance[src] + graph->edge[j].w;
        if(temp < distance[dest] && distance[src] != 2147483647)
            negCycle = true;
    }
   
    if(negCycle)
        cout << "FALSE" << endl;    
    else {
        cout << "TRUE" << endl;
        for(int i = 0; i < vertices; i++) {
            if(distance[i] == 2147483647)
                cout << "INFINITY" << endl;
            else
                cout << distance[i] << endl;
        }
    }
}


int main() {
    string input;
    getline(cin, input, ' ');
    int vertices = stoi(input);
    getline(cin, input, '\n');  
    int edges = stoi(input);
    //cin.ignore();

    //Initialize the graph
    struct Graph* graph = new Graph;
    graph->edge = new Edge[edges];
    
    int j; int k; int weight;
   //Gets the edges and the weights
    for(int i = 0; i < edges; i++) {
        getline(cin, input, ' ');
        j = stoi(input);
        getline(cin, input, ' ');  
        k = stoi(input);
        getline(cin, input, '\n');
        weight = stoi(input);
        graph->edge[i].u = j;
        graph->edge[i].v = k;
        graph->edge[i].w = weight;
    }

    bellmanFord(graph, vertices, edges);
}
