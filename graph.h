/*
Title: Homework No. 8 - Graphos
Date: November 20th, 2025
Author: Rodrigo Alejandro Hurtado Cortes - A01713854

Description: Homework that shows the implementation of reading
conections from a string and putting them into an adjacency list
and matrix in order to search an element through them using the
general DFS and BFS methods.

The present homework was completed by adapting and using the 
necessary methods from the Practice Work in Class - graphs 
provided by the professor Benjamín Valdés Aguirre. 
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

/*
==============================================================
CLASS GRAPH
==============================================================
Description: 
Class responsible for storing the connections between the nodes
into either an adjacency list or an adjacency matrix (in this
case both are used as are required for the main.cpp file); and
implement search algorithms to find the shortest route from one
node to another. 
*/

class Graph {
private:
    //PIV
	int edgesList; //Connections stored into the List
    int edgesMat;  //Connections stored into the Matrix
	int nodes;     //Number of Nodes

	vector<int> *adjList; //List
    int *adjMatrix;       //Matrix

public:
    //Constructor
    Graph();

    //Loading Methods
    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);

    //Auxiliar Loading Methods
    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);
    void sortAdjList();

    //Printing Methods
    string printAdjList();
    string printAdjMat();

    //Search Algorithms
    //Depth For Search
    string DFS(int, int);
    string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
    
    //Breadth For Search
    string BFS(int, int);
    string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
    
    //Auxiliar Search Methods
    string print_visited(list<int>);
    string print_path(vector<vector<int>>&,int ,int);
    bool contains(list<int>, int);
};

/*Declaration of Public Methods*/
/*--------- Constructor ---------*/
/*
Graph()

Default constructor without parameters.
*/

Graph::Graph() {
	edgesList = 0;
    edgesMat = 0;
    nodes = 0;
}


/*--------- Loading and Auxiliar Methods ---------*/

////////////// LIST //////////////
/*
void loadGraphList(string name, int a)

Method responsible for accepting the string which contains all the
connections in the graph in the format '(x,y) (x_1,y_1)' [name] and
the number of nodes [a].
With the number of nodes [a] the vector is created.
By reading each of the pairs contained inside the string [name] and
with the support of the function addEdgeAdjList() each of these are
added to their respective vector.
Finally the vector is sorted in order to be able to consult it in the
node order afterwards.
*/
void Graph::loadGraphList(string name, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v;
    bool finished = true;
    while(finished){
        //Obtention of (x,y)
        string conection = name.substr(0,5);
        //Obtention of x and y
        u = stoi(conection.substr(1,1));
		v = stoi(conection.substr(3,1));
        addEdgeAdjList(u,v);

        /*In case the next char is not a whitespace it means the end of
        the string. therefore ending the while loop.*/
        name = name.substr(5);
        if(name.substr(0,1) == " "){
            name = name.substr(1);
        }
        else{
            finished = false;
        }
    }
    sortAdjList();
}


//---------------------------------------------------------
/*
void addEdgeAdjList(int u, int v)

Method responsible for add into both nodes own vector the other pair
in order to make all connections bidirectional.
Additionally, it increases the edgeList counter by one.
*/
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}


//---------------------------------------------------------
/*
void sortAdjList(){

Method that using the sort function orders the node vectors of the List
in descending order to be able to consult them in order during the 
searches.
*/

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}


////////////// MATRIX //////////////

/*
void loadGraphMat(string name, int a, int b)

Method responsible for accepting the string which contains all the
connections in the graph in the format '(x,y) (x_1,y_1)' [name] and
the number of nodes [a,b].
With the number of nodes [a,b] the matrix is created.
By reading each of the pairs contained inside the string [name] and
with the support of the function addEdgeAdjMatrix() each of these 
connections is shown as 1 into the adyacency matrix.
*/
void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
    
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
    int u, v;
    bool finished = true;
    while(finished){
        //Obtention of (x,y)
        string conection = name.substr(0,5);
        //Obtention of x and y
        u = stoi(conection.substr(1,1));
        v = stoi(conection.substr(3,1));
        addEdgeAdjMatrix(u,v);

        /*In case the next char is not a whitespace it means the end of
        the string. therefore ending the while loop.*/
        name = name.substr(5);
        if(name.substr(0,1) == " "){
            name = name.substr(1);
        }
        else{
            finished = false;
        }
    }
}


//---------------------------------------------------------
/*
void addEdgeAdjMatrix(int u, int v)

Function responsible for adding the connection represented
as 1 in the matrix into its corresponding column and line
from both nodes, making it bidirectlional.
Additionally, it increases the edgesMat counter by one.

*/
void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}


/*--------- Printing Methods ---------*/

////////////// LIST //////////////

/*
string printAdjList(){

Method responsible for returning a string that shows the vertexes (nodes)
of the graph and all the other vertexes they have connections to in the
adjacency list adjList.
*/
string Graph::printAdjList(){
	stringstream aux;
		for (int i = 0; i < nodes; i++){
			aux << "vertex "<< i << " :";
			for (int j = 0; j < adjList[i].size(); j ++){
				aux << " " << adjList[i][j];
			}
		aux << " ";
    }
		return aux.str();
}


////////////// MATRIX //////////////

/*
string printAdjMat(){

Method responsible for returning a string that shows the adjacency matrix
adjMatrix showing form top to bottom its connections as 0 or 1.
*/
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
		for (int j = 0; j < nodes; j++){
				aux << adjMatrix[i*nodes+j] << " ";
			}
	}
	return aux.str();
}


/*--------- Search Algorithms ---------*/
/*========= Depth For Search =========*/

/*
string DFS(int start, int goal){

Depth for Search method responsible for staring from a vertex [start]
and looking to go towards a different vertex [goal] will develop a 
search that priors looking into the smaller vertex connections of each
vertex, and if stuck, will return looking for other connections of vertex
that have not been found until either the element is found (returning a 
string that collects the visited vertexes and shortest path) or the whole
graph has been visited (returns "no found").

This process is developed mainly by the auxiliar recursive function 
depthHelper().
*/
string Graph::DFS(int start, int goal){
	stack<int> st;
	list<int> visited;
	vector<vector<int>> paths(nodes);

	for(int i = 0; i < nodes; i++){
		paths[i].push_back(-1);
	}	

	if(start == goal){
		return "visited: "+to_string(start)+" path: "+to_string(start);
	}

	st.push(start);
	string answer = depthHelper(st.top(), goal, st, visited, paths);
	if(answer == "no answer"){
		return "no found";
	}
	return answer + print_path(paths, start, goal);
		return "";
}


//---------------------------------------------------------
/*
string Graph::depthHelper(int current,int goal, stack<int> &st, 
list<int> &visited, vector<vector<int>> &paths)

Recursive method responsible for orienting the search based on the
current node, the nodes in the stack, if the node has been visited 
previously, and its connections.

If the current node is the goal, it is added to the visited list and
the method return its visited list.

If there are no more connections into the queue, the graph has been 
completely traversed and the element has not been found.

If the node has been visited previously, the element is taken out of
the stack but its connections are checked in case a vertex that has not
been visited is available, afterwards calling inmediately the recursive
function.

If the node is new, it is registered as visited and its connections are
checked, if these are not visited there are registered and the recursive
function is called inmediately.

This method allows to keep order of the elements in the stack, while 
saving time in the visited nodes and registering their parents (path)
until the goal is found or the graph all visited.
*/
string Graph::depthHelper(int current,int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths){
	//The goal has been found
	if(current == goal){
		visited.push_back(current);
		return print_visited(visited);
	}
	//No more elements available to consult.
	else if(st.empty()){
		return "no answer";
	}
	else{
		//The node has been visited previously
		if(contains(visited,current)){
			st.pop();
		}

		//The node is new
		if(!contains(visited,current)){
			visited.push_back(current);
		}
		//Checking for the connection of the current node
		for (int j = 0; j < adjList[current].size(); j ++){

			/*If a connection is new, it is registered and the recursive
			function called inmediately*/
			
			if(!(contains(visited,adjList[current][j]))){
				int next = adjList[current][j];
				st.push(next);
				if(paths[next][0] == -1)
					paths[next][0] = current;
				return depthHelper(st.top(), goal, st, visited, paths);
			}
		}
		return depthHelper(st.top(), goal, st, visited, paths);
	}
	return "no answer";
}


/*========= Breadth For Search =========*/
/*
string BFS(int start, int goal){


Breadth for Search method responsible for staring from a vertex [start]
and looking to go towards a different vertex [goal] will develop a 
search that priors looking into all the vertex connections of the present
vertex and if the element is not found, start traversing repearing this
patter recursively through these connections,  until either the element
is found (returning a string that collects the visited vertexes and
shortest path) or the whole graph has been visited (returns "no found").

This process is developed mainly by the auxiliar recursive function 
breadthHelper().
*/
string Graph::BFS(int start, int goal){
	queue<int> qu;
	list<int> visited;
	vector<vector<int>> paths(nodes);

	for(int i = 0; i < nodes; i++){
		paths[i].push_back(-1);
	}	

	if(start == goal){
		return "visited: "+to_string(start)+" path: "+to_string(start);
	}

	qu.push(start);
	string answer = breadthHelper(qu.front(), goal, qu, visited, paths);
	if(answer == "no answer"){
		return "no found";
	}
	return answer + print_path(paths, start, goal);
}


//---------------------------------------------------------
/*
string Graph::breadthHelper(int current, int goal, queue<int> &qu,
list<int> &visited, vector<vector<int>> &paths)

Recursive method responsible for orienting the search based on the
current node, the nodes in the queue, if the node has been visited 
previously, and its connections.

If the current node is the goal, it is added to the visited list and
the method return its visited list.

If there are no more connections into the queue, the graph has been 
completely traversed and the element has not been found.

If the node has been visited previously, the function is called again
as the node has been taken out of the queue.

If the node is new, it is registered as visited and all its connections
if not visited before are added to the queue, as well as their path
registered, finally calling again the recursive function.

This method allows to keep order of the elements in the queue, while 
saving time in the visited nodes and registering their parents (path)
until the goal is found or the graph all visited.
*/
string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &paths){
	//The goal has been found
	if(current == goal){
		visited.push_back(current);
		return print_visited(visited);
	}
	//No more elements available to consult.
	else if(qu.empty()){
		return "no answer";
	}
	else{
		qu.pop();
		//The element has been visited before
		if(contains(visited,current)){
			return breadthHelper(qu.front(), goal, qu, visited, paths);
		}

		//The element is new
		visited.push_back(current);
		//Consult all connections of the current vertex.
		for (int j = 0; j < adjList[current].size(); j ++){
			
			/*If a connection is new, it is registered and added 
			to the queue*/
			if(!(contains(visited,adjList[current][j]))){
				qu.push(adjList[current][j]);
				if(paths[adjList[current][j]][0] == -1)
					paths[adjList[current][j]][0] = current;
			}
		}

		//The recursive function is called afterwards
		return breadthHelper(qu.front(), goal, qu, visited, paths);
	}

	return "no answer";
}

/*========= Auxiliar Search Methods =========*/
/*
bool contains(list<int> ls, int node)

Method responsible for traverting the adjacency list and check for the
presence of [node] into the list [ls], returning a boolean.
*/
bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}


//---------------------------------------------------------
/*
string Graph::print_visited(list<int> q){

Method responsible for returning a string with all the visited nodes
available in the list [q].
*/
string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
    }
	return aux.str();
}


//---------------------------------------------------------
/*
string print_path(vector<vector <int>> &path, int start, int goal){

Method responsible for returning a string that contains all the 
vertexes that are required to go from the start to the goal by checking
which are the parents of each discovered node, going backwards from the
goal until the start is reached, afterwards ordered correctly.

*/
string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;

	aux  << "path:";
	
	while (node != start) {
		reverse.push(node);
		node = path[node][0];
	}

	reverse.push(start);
	
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
	}
	return aux.str();
}


#endif