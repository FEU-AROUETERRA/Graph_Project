#include "Graph.h"
#include "Painter.h"
const int cX = 40, cY = 35;
using namespace std;

Graph::Graph() {
	Limit = 0;
	adjacent = new Neighbors[Limit];
	for (int i = 0; i < Limit; ++i) {
		adjacent[i].head = NULL;
	}
}
Graph::Graph(int limit) {
	Limit = limit;
	adjacent = new Neighbors[Limit];
	for (int i = 0; i < Limit; ++i) {
		adjacent[i].head = NULL; 
	}
}

void Graph::Display(bool type) {
	Colorize format;
	for (int i = 0; i < Limit; i++)
	{
		Vertex *Displaying = adjacent[i].head;
		if (Displaying != NULL) {
			string s = to_string(i); s.append("\n");
			format.Paint(14, " Adjacent to ", s);
			if (type == true)
				cout << i << " ";
		}
		vector<int> temp;
		while (Displaying)
		{
			if (find(temp.begin(), temp.end(), Displaying->data) != temp.end() == true) {
				// Do nothing
			}
			else {
				temp.push_back(Displaying->data);
				//cout << " -> " << Displaying->data;
				if (type == true) {
					format.Paint(8, " -> ", to_string(Displaying->data));
				}
				else {
					format.Paint(8, " -> ", ""); cout << to_string(Displaying->data);
				}
				
			}			
			Displaying = Displaying->next;
		}
		cout << endl;
	}
}

Graph::Vertex* Graph::Add_Vertex(int data)
{
	//Initialize vertex
	Vertex* temp = new Vertex;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void Graph::Connect(int first, int second, bool type)
{
	if (type == false)
	{
		if (counter == 0) {
			Vertex *temp, *temp2;
			for (int i = 0; i < Limit; i++) {
				temp = Add_Vertex(i);
				temp2 = Add_Vertex(i);
				adjacent[i].head = temp;
				adjacent[i].head = temp2;
			}
		}
		counter++;
		Vertex *temp, *temp2;
		temp = Add_Vertex(first);
		temp2 = Add_Vertex(second);
		if (adjacent[first].head == nullptr || adjacent[second].head == nullptr) {
			adjacent[first].head = temp;
			adjacent[second].head = temp2;
		}
		else {
			Vertex *it = adjacent[second].head;
			while (it->next) {
				it = it->next;
			}
			it->next = temp;
			Vertex *it2 = adjacent[first].head;
			while (it2->next) {
				it2 = it2->next;
			}
			it2->next = temp2;
		}
		
	}
	else
	{
		Vertex *temp;
		if (first != second) {
			temp = Add_Vertex(second);
			temp->next = adjacent[first].head;
			adjacent[first].head = temp;
		}
		temp = Add_Vertex(first);
		temp->next = adjacent[second].head;
		adjacent[second].head = temp;
		
	}
}

list<int> Graph::BFS(int from) {
	print_list.clear();
	bool *visited = new bool[Limit];
	for (int i = 0; i < Limit; i++)
		visited[i] = false;
	
	list<int> queue;
	visited[from] = true;
	queue.push_back(from);

	while (!queue.empty())
	{
		from = queue.front();
		print_list.push_back(from);
		queue.pop_front();
		
		Vertex *Displaying = adjacent[from].head;
		while (Displaying)
		{
			int adjacent_node = Displaying->data;
			if (!visited[adjacent_node])
			{
				visited[adjacent_node] = true;
				queue.push_back(adjacent_node);
			}
			Displaying = Displaying->next;
		}
	}
	return print_list;
}

list<int> Graph::DFS(int from)
{
	print_list.clear();
	bool *visited = new bool[Limit];
	for (int i = 0; i < Limit; i++)
		visited[i] = false;

	stack<int> pringles;
	pringles.push(from);

	while(!pringles.empty()) {
		from = pringles.top();
		pringles.pop();
		if (!visited[from])
		{
			print_list.push_back(from);
			visited[from] = true;
		}
		Vertex *Displaying = adjacent[from].head;
		while (Displaying)
		{
			int adjacent_node = Displaying->data;
			if (!visited[adjacent_node])
			{
				pringles.push(adjacent_node);
			}
			Displaying = Displaying->next;
		}
	}
	return print_list;
}


void AMatrix::Connect(int first, int second, bool type)
{
	if (first >= Limit || second >= Limit || first < 0 || second < 0)
	{
		Colorize format;
		format.Paint(12, " Edge cannot be created!", "\n");
	}
	else
	{
		if (type == false) {
			if (Neighbor[first][second] == 1 && Neighbor[second][first] == 1) {
				Neighbor[first][second] = 2;
				Neighbor[second][first] = 2;
			}
			else {
				Neighbor[first][second] = 1;
				Neighbor[second][first] = 1;
			}
		}
		else {
			if (Neighbor[first][second] == 1) {
				Neighbor[first][second] = 2;
			}
			else {
				Neighbor[first][second] = 1;
			}
		}

		
	}
}

void AMatrix::Display()
{
	cout << endl;
	int i, j; Colorize format;
	for (i = 0;i < Limit;i++)
	{
		for (j = 0; j < Limit; j++)
			if (Neighbor[i][j] == 0) 
				format.Paint(8, to_string(Neighbor[i][j]), " ");
			else
				format.Paint(14, to_string(Neighbor[i][j]), " ");
		cout << endl;
	}
}


AMatrix::AMatrix(int limit)
{
	Limit = limit;
	Exists = new bool[Limit];
	Neighbor = new int*[Limit];
	for (int i = 0; i < Limit; i++)
	{
		Neighbor[i] = new int[Limit];
		for (int j = 0; j < Limit; j++)
		{
			Neighbor[i][j] = 0;
		}
	}
}
list<int> AMatrix::BFS(int node) {
	print_list.clear();
	bool *visited = new bool[Limit];
	for (int i = 0; i < Limit; i++)
		visited[i] = false;

	queue<int> que;
	que.push(node);                        
	visited[node] = true;                 
	while (!que.empty())               
	{
		node = que.front();                 
		print_list.push_back(node);              
		que.pop();                      
		for (int i = 0; i < Limit; i++)      
		{
			if (Neighbor[node][i] >= 1 && visited[i] == false)
			{                           
				que.push(i);             
				visited[i] = true;      
			}
		}
	}
	return print_list;
}
list<int> AMatrix::DFS(int node) {
	print_list.clear();
	bool *visited = new bool[Limit];
	for (int i = 0; i < Limit; i++)
		visited[i] = false;

	stack<int> pringles;
	pringles.push(node);
	visited[node] = true;
	while (!pringles.empty())                 
	{
		node = pringles.top();  
		pringles.pop();
		//cout << node << " ";
		print_list.push_back(node);
		//print_list.push_front(node);
		for (int i = 0; i < Limit; i++)    
		{
			if (Neighbor[node][i] <= 0) { 
				continue;
			}
			if (Neighbor[node][i] >= 1 && visited[i] == false)
			{                           
				pringles.push(i);            
				visited[i] = true;
			}
		}
	}
	return print_list;
}