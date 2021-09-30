#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

/*struct Edge {
    int u; 
    int v; 
    int w;
};

struct Graph {
    struct Edge* edge;
};*/

struct Node {
    int index;
    int w;
    int key;
    bool visited;
    Node* parent;
};

//Returns the index of the node with the smallest key in minQueue
int findMin(vector<Node*> minQueue) {
    int minValue = minQueue[0]->key;
    int min = 0;
    for(int i = 1; i < minQueue.size(); i++) {
        if(minQueue[i]->key < minValue) {
            min = i;
            minValue = minQueue[i]->key;
        }
    }

    return min;
}

/*void minSpanningTree(int** graph, int vertices, int edges) {
    //Node* verts = new Node[vertices];
    //Make a vector for all of the vertices
    vector<Node*> minQueue;

    //For all the vertices, set their key value to max and their parent to null
    for(int i = 0; i < vertices; i++) {
        Node* z = new Node;
        minQueue.push_back(z);
        minQueue[i]->index = i;
        minQueue[i]->key = INT_MAX;
        minQueue[i]->parent = NULL;  
        minQueue[i]->visited = false;   
    }
    //cout << "This is after making minQueue" << endl;
    vector<Node*> outputQueue = minQueue;

    minQueue[0]->key = 0;
    int k = 0;
    //Find the shortest edge leaving the vertex and add it to the tree
    while(k < vertices) {
        //Find the minimum from minqueue
        int min = findMin(minQueue);
        Node* u = minQueue[min];
        int i = u->index;
        
        //cout << "This is after the extraction thing" << endl;

        //Go through each vertex that's a neighbor of u
        for(int j = 0; j < vertices; j++) {
            if(graph[i][j] != -1) { //If an edge between these two vertices exist
                //If the edge between the two vertices is less than the key value of the neighbor vertex and the neighbor vertex hasn't been visited yet
                if(graph[i][j] < minQueue[j]->key && minQueue[j]->visited == false) { 
                    minQueue[j]->parent = u;
                    //cout << minQueue[j]->parent->index << endl;
                    minQueue[j]->key = graph[i][j];
                }
            }
            
        }
        minQueue[i]->visited = true; //This vertex has now been visited so it shouldn't be visited again
        minQueue[i]->key = INT_MAX; //This makes sure it won't be found by findMin again
        //minQueue.erase(minQueue.begin() + min);
        k++;
    }

    //Print the minimum spanning tree
    for(int i = 1; i < vertices; i++) {
        if(minQueue[i]->parent != NULL)
            cout << minQueue[i]->parent->index << endl;
    }
    
}*/

/*void minSpanningTree(int** graph, int vertices, int edges) {
    //Make a vector for all of the vertices
    vector<Node*> outputQueue;

    //For all the vertices, set their key value to max and their parent to null
    for(int i = 0; i < vertices; i++) {
        Node* z = new Node;
        outputQueue.push_back(z);
        outputQueue[i]->index = i;
        outputQueue[i]->key = INT_MAX;
        outputQueue[i]->parent = NULL;  
        outputQueue[i]->visited = false;   
    }
    for(int i = 0; i < vertices; i++) {
        cout << outputQueue[i]->index << " " << outputQueue[i]->key << endl;
    }
    //cout << "This is after making outputQueue" << endl;

    outputQueue[0]->key = 0;
    vector<Node*> minQueue;
    minQueue.push_back(outputQueue[0]);
    int k = 0;

    //Find the shortest edge leaving the vertex and add it to the tree
    while(k < vertices && !minQueue.empty()) {
        //Find the minimum from minqueue
        int min = findMin(minQueue);
        Node* u = minQueue[min];
        //cout << "The index of the minimum is " << u->index << endl;
        int i = u->index;
        minQueue.erase(minQueue.begin() + min);
        outputQueue[i]->visited = true; //This vertex has now been visited so it shouldn't be visited again
        
        //cout << "This is after the extraction thing" << endl;

        //Go through each vertex that's a neighbor of u
        //int yes;
        for(int j = 0; j < vertices; j++) {
            if(graph[i][j] != -1) { //If an edge between these two vertices exist
                //If the edge between the two vertices is less than the key value of the neighbor vertex and the neighbor vertex hasn't been visited yet
                cout << outputQueue[j]->key << endl;
                if(graph[i][j] < outputQueue[j]->key && outputQueue[j]->visited == false) { 
                    outputQueue[j]->key = graph[i][j];
                    minQueue.push_back(outputQueue[j]);
                    outputQueue[j]->parent = u;
                }
            }
            
        }
        //minQueue[i]->key = INT_MAX; //This makes sure it won't be found by findMin again
        k++;
    }
    //cout << "This is after all the crap is done" << endl;
    //cout<< "outputQueue size: " << outputQueue.size() << endl;

    //Print the minimum spanning tree
    for(int i = 0; i < vertices; i++) {
        if(outputQueue[i]->parent != NULL)
            cout << outputQueue[i]->parent->index << endl;
    }
    
}*/

void minSpanningTree(int** graph, int vertices, int edges) {
    //Make a vector for all of the vertices
    vector<Node*> outputQueue;

    //For all the vertices, set their key value to max and their parent to null
    for(int i = 0; i < vertices; i++) {
        Node* z = new Node;
        outputQueue.push_back(z);
        outputQueue[i]->index = i;
        outputQueue[i]->key = INT_MAX;
        outputQueue[i]->parent = NULL;  
        outputQueue[i]->visited = false;   
    }
    //cout << "This is after making outputQueue" << endl;

    outputQueue[0]->key = 0;
    vector<Node*> minQueue;
    minQueue.push_back(outputQueue[0]);
    int k = 0;

    //Start with the source vertex 0
    while(!minQueue.empty()) {
        //The minQueue has all the key values of the vertices
        //Find the minimum key value from minQueue and call it u, REMOVE it from the priority queue
        int min = findMin(minQueue);
        cout << min << endl;
        Node* u = minQueue[min];
        cout << "The min is " << u->index << endl;
        int i = u->index;
        cout << "IS it here" << endl;
        outputQueue[i]->visited = true;
        cout << "Is it here" << endl;
        for(int i = 0; i < minQueue.size(); i++) {
            cout << minQueue[i]->index << " ";
        } cout << endl;


        //Add all of u's neighbors to the priority queue
        for(int j = 0; j < vertices; j++) {
            if(graph[i][j] != -1) { //If an edge between these two vertices exists
                //cout << outputQueue[j]->key << endl;
                if(outputQueue[j]->visited == false) { 
                    cout << "Adding " << outputQueue[j]->index << " to the queue" << endl;
                    outputQueue[j]->key = graph[i][j];
                    minQueue.push_back(outputQueue[j]);
                }
            }
        }
        minQueue.erase(minQueue.begin() + min);
        cout << "This is after the extraction thing" << endl;

        //Find the neighbor of u with the minimum key value and make u its parent
        int minIndex;
        min = INT_MAX; 
        for(int j = 0; j < vertices; j++) {
            if(graph[i][j] != -1) { //If an edge between these two vertices exists
                //cout << outputQueue[j]->key << endl;
                if(graph[i][j] < outputQueue[j]->key && outputQueue[j]->visited == false && graph[i][j] < min) { 
                    min = graph[i][j];
                    minIndex = j;
                }
            }
        }
        cout << "The minimum is " << outputQueue[minIndex]->index << endl;
        outputQueue[minIndex]->parent = u;
        cout << "What" << endl;
        k++;
    }
    //cout << "This is after all the crap is done" << endl;
    //cout<< "outputQueue size: " << outputQueue.size() << endl;

    //Print the minimum spanning tree
    for(int i = 0; i < vertices; i++) {
        if(outputQueue[i]->parent != NULL)
            cout << outputQueue[i]->parent->index << endl;
    }
    
}

//Make a vector for all of the vertices
/*void minSpanningTree(int** graph, int vertices, int edges) {
    vector<Node*> outputQueue;

    //For all the vertices, set their key value to max and their parent to null
    for(int i = 0; i < vertices; i++) {
        Node* z = new Node;
        outputQueue.push_back(z);
        outputQueue[i]->index = i;
        outputQueue[i]->key = INT_MAX;
        outputQueue[i]->parent = NULL;  
        outputQueue[i]->visited = false;   
    }
    cout << "This is after making outputQueue" << endl;

    outputQueue[0]->key = 0;
    //vector<Node*> minQueue;
    //minQueue.push_back(outputQueue[0]);
    int k = 0;
    int i = 0;
    int yes; int min;
    //Find the shortest edge leaving the vertex and add it to the tree
    while(k < vertices) {
        //Find the minimum from minqueue
        Node* u = outputQueue[i];
        cout << "The index of the minimum is " << u->index << endl;
        outputQueue[i]->visited = true; //This vertex has now been visited so it shouldn't be visited again
        
        cout << "This is after the extraction thing" << endl;

        //Go through each vertex that's a neighbor of u
        //int yes;
        min = INT_MAX;
        for(int j = 0; j < vertices; j++) {
            if(graph[i][j] != -1) { //If an edge between these two vertices exist
                //If the edge between the two vertices is less than the key value of the neighbor vertex and the neighbor vertex hasn't been visited yet
                cout << outputQueue[j]->key << endl;
                if(graph[i][j] < outputQueue[j]->key && outputQueue[j]->visited == false && graph[i][j] < min) { 
                    cout << "What the fuck 1" << endl;
                    outputQueue[j]->key = graph[i][j];
                    cout << "What the fuck 2" << endl;
                    outputQueue[j]->parent = u;
                    min = outputQueue[j]->key;
                    yes = j;
                }
            }
            
        }
        i = yes;
        k++;
    }
    cout << "This is after all the crap is done" << endl;
    //cout<< "outputQueue size: " << outputQueue.size() << endl;

    //Print the minimum spanning tree
    for(int i = 0; i < vertices; i++) {
        if(outputQueue[i]->parent != NULL)
            cout << outputQueue[i]->parent->index << endl;
    }
    
}*/



int main() {
    int vertices;
    cin >> vertices;
    int edges;
    cin >> edges;

    //Initialize the graph
    /*struct Graph* graph = new Graph;
    graph->edge = new Edge[edges];
    
    string input;
    int j; int k; int weight;
    int * neighbors = new int[vertices]; //An array for the amount of neighbors each vertex of the graph has*/

    //The graph is a 2D matrix of nodes with the values being the edge weights
    int** graph = new int*[vertices];
    for(int i = 0; i < vertices; i++) {
        graph[i] = new int[vertices];
    }
    
    //Initialize all the weight values of the graph to -1
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            graph[i][j] = -1;
        }
    }
    //cout << "This is after initializing the graph" << endl;

   //Gets the edges and the weights
    string input;
    int j; int k; int weight;
    for(int i = 0; i < edges; i++) {
        getline(cin, input, ' ');
        j = stoi(input);
        getline(cin, input, ' ');  
        k = stoi(input);
        getline(cin, input, '\n');
        weight = stoi(input);
        /*graph->edge[i].u = j;
        graph->edge[i].v = k;
        graph->edge[i].w = weight;*/
        graph[j][k] = weight;
        graph[k][j] = weight;
        
    }
    //cout << "This is after getting input" << endl;

   /* for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }*/

    minSpanningTree(graph, vertices, edges);
}
