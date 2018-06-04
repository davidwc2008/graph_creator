/*David Chen
C++ 2018
Graph Creator Program
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//function prototypes
int getIndex(string, string[]);
void addVertex(string[], int &);
void addEdge(string[], int[20][20]);
void removeVertex(string[], int[20][20], int &);
void removeEdge(string[], int[20][20]);
void shortestPath(string[], int[20][20]);
void print(string[], int[20][20]);

struct Node {
	string name;
	int distance;
	Node* previous = NULL;	
};

int main() {
	bool done = false;
	
	string vertices[20]; //an ordered list of all the vertices
	int adjacencyTable[20][20]; //a 2D array
	int nextVertex = 0; //a counter for the next vertex

	//clear the vertices array
	for (int i = 0; i < 20; i++) {
	  vertices[i] = "";
	}
	
	//clear the adjacency table
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			adjacencyTable[i][j] = -1;
		}
	}
	
	cout << "Welcome to the Graph Creator Program with Breadth First Search" << endl;
	
	while (!done) {
		int command = 0;
	
		cout << "1: Add Vertex | 2: Add Edge | 3: Remove Vertex | 4: Remove Edge | 5: Find Shortest Path | 6: Print | 7: Quit" << endl;
		cout << "Enter your command: " << endl;
		cin >> command;
		
		if (command == 1) {
			addVertex(vertices, nextVertex);
		} else if (command == 2) {
			addEdge(vertices, adjacencyTable);
		} else if (command == 3) {
			removeVertex(vertices, adjacencyTable, nextVertex);
		} else if (command == 4) {
			removeEdge(vertices, adjacencyTable);
		} else if (command == 5) { 
			shortestPath(vertices, adjacencyTable);
		} else if (command == 6) {
			print(vertices, adjacencyTable);
		} else if (command == 7) {
			done = true;
		} else {
			cout << "Error: No such command." << endl;
		}
	}
	return 0;
}

int getIndex(string a, string vertices[20]) {
	for (int i = 0; i < 20; i++) {
		if (vertices[i] == a) {
				return i;
		}
	}
	return -1;
}

void addVertex(string vertices[20], int & nextVertex) {
	string name;
	cout << "Enter the name of the vertex (Unique): " << endl;
	cin >> name;
	
	for (int i = 0; i < 20; i++) {
		if (vertices[i] == name) {
			cout << "Error: The name already exists" << endl;
			return;
		}
	}
	vertices[nextVertex] = name;
	
	while (nextVertex < 20 && vertices[nextVertex] != "") {
		nextVertex++;
	}
	
	cout << "Success: Added Vertex" << endl;
}

void addEdge(string vertices[20], int adjacencyTable[20][20]) {
	string begin, end;
	int weight = 0;
	
	cout << "Beginning Vertex: " << endl;
	cin >> begin;
	cout << "Ending Vertex: " << endl;
	cin >> end;
	//weight is like the number of miles between
	cout << "Weight: " << endl;
	cin >> weight;
	//check to make sure the weight is an integer
	if (cin.fail()) {
		cout << "Error: Weight must be a number" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	
	//find the vertices of the beginning and ending
	int indexBegin = getIndex(begin, vertices);
	int indexEnd = getIndex(end, vertices);
	
	//check to see if there is no index (-1 case)
	if (indexBegin == -1 || indexEnd == -1) {
		cout << "Invalid Vertices" << endl;
		return;
	}
	
	//check to make sure weight is valid
	if (weight < 0) {
		cout << "Invalid weight" << endl;
		return;
	}
	
	adjacencyTable[indexBegin][indexEnd] = weight;
	
	cout << "Success: Edge Added" << endl;	
}

void removeVertex(string vertices[20], int adjacencyTable[20][20], int & nextVertex) {
	string name;
	cout << "Enter name: " << endl;
	cin >> name;
	
	//check to see if the vertex exists
	int index = getIndex(name, vertices);
	if (index == -1) {
		cout << "Error: The vertex does not exist" << endl;
		return;
	}
	
	vertices[index] = "";
	nextVertex = index;
	
	//remove the vertex and any references in the adjacencyTable
	for (int i = 0; i < 20; i++) {
		adjacencyTable[index][i] = -1; //removes row
		adjacencyTable[i][index] = 1; //removes column
	}
	
	cout << "Success: Removed Vertex" << endl;
}

void removeEdge(string vertices[20], int adjacencyTable[20][20]) {
	string begin;
	string end;
	
	cout << "Enter beginning vertex: " << endl;
	cin >> begin;
	cout << "Enter ending vertex: " << endl;
	cin >> end;
	
	int indexBegin = getIndex(begin, vertices);
	int indexEnd = getIndex(end, vertices);
	
	//check to see if there is no index (-1 case)
	if (indexBegin == -1 || indexEnd == -1) {
		cout << "Invalid Vertices" << endl;
		return;
	}
	
	//check to see if the edge exist
	if (adjacencyTable[indexBegin][indexEnd] < 0) {
		cout << "Error: Invalid Edge" << endl;
		return;
	}
	
	//Actually remove the edge from the adjacencyTable
	adjacencyTable[indexBegin][indexEnd] = -1;
	
	cout << "Success: Removed edge" << endl;	
}

//use breadth first search to find the shortest path
void shortestPath(string vertices[20], int adjacencyTable[20][20]) {
	string begin, end;
	cout << "Enter beginning vertex: " << endl;
	cin >> begin;
	cout << "Enter ending vertex: " << endl;
	cin >> end;
	
	int indexBegin = getIndex(begin, vertices);
	int indexEnd = getIndex(end, vertices);
	
	//check to make sure vertices exist
	if (indexBegin == -1 || indexEnd == -1) {
		cout << "Invalid Vertices" << endl;
		return;
	}
	
	vector<Node*> unvisited;
	vector<Node*> visited;
	
	//intialization
	for (int i = 0; i < 20; i++) {
		if(vertices[i] != "") {
			Node* a = new Node();
			a->name = vertices[i];
			if (i == indexBegin) {
				a->distance = 0;
			} else {
				a->distance = 99999999;
			}
			unvisited.push_back(a);
		}
	}
	
	while (!unvisited.empty()) {
		int minIndex = 0; //index of node with minimum distance
		for (int i = 1; i < unvisited.size(); i++) {
			if (unvisited[i]->distance < unvisited[minIndex]->distance) {
				minIndex = i;
			}
		}
		Node* u = unvisited[minIndex];
		unvisited.erase(unvisited.begin() + minIndex);
		visited.push_back(u);
		
		for(Node* v : unvisited) {
			int indexU = getIndex(u->name, vertices);
			int indexV = getIndex(v->name, vertices);
			//check to see if the edge exist, they are neighbors!
			if (adjacencyTable[indexU][indexV] >= 0) {
				int alternate = u->distance + adjacencyTable[indexU][indexV];
				if (alternate < v->distance) {
					v->distance = alternate;
					v->previous = u;
				}
			}

		}
	}
	Node* endNode;
	for (Node* n : visited) {
		if (n->name == end) {
			endNode = n;
			break;
		}
	}
	if (endNode->previous == NULL) {
		cout << "Error: No path exists." << endl;
	} else {
		vector<Node*> path;
		Node* current = endNode;
		while(current != NULL) {
			path.push_back(current);
			current = current->previous;
		}
		cout << "Path: " << endl;
		for (vector<Node*>::iterator it = path.end()-1; it != path.begin()-1; it--) {
			cout << (*it)->name << ", ";
		}
		cout << endl;
		cout << "Distance: " << endNode->distance << endl;	
	}
}

void print(string vertices[20], int adjacencyTable[20][20]) {
	//first we need to print the column names
	cout << " " << flush;
	for (int i = 0; i < 20; i++) {
		if (vertices[i] != "") {
			cout << " " << vertices[i] << flush;
		}
	}
	
	cout << endl;
	
	for (int row = 0; row < 20; row++) {
		if (vertices[row] != "") {
			cout << vertices[row] << flush;
			for (int cont = 0; cont < 20; cont++) {
				if (vertices[cont] != "") {
					if (adjacencyTable[row][cont] == -1) {
						cout << " -" << flush;
					} else {
						cout << " " << adjacencyTable[row][cont] << flush;
					}
				}
			}
			cout << endl;
		}
	}
}
