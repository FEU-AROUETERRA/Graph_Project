#include "Graph.h"
#include "Painter.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <iterator>
#include <list>
#include <tuple>
#include <Windows.h>
#include <stdlib.h>
using namespace std;


void Connect(Graph list, int edges, bool type, int limit) {
	int i = 0;
	while (edges > 0) {
		string s = "[";
		s.append(to_string(i));
		s.append("] Edge from: ");
		int a, b;
		Colorize format;
		format.Paint(10, s, "\n");
		cin >> a; 
		s = "[";
		s.append(to_string(i));
		s.append("] To: ");
		format.Paint(10,s, "\n");
		cin >> b; 
		if (a >= limit || b >= limit || a < 0 || b < 0) {
			format.Paint(12, " The number should be within the domain of the limit!", "\n");
			cout << "";
			system("pause");
			return;
		}
		list.Connect(a, b, type);
		edges--;
		i++;
	}
}

void Matrix_Connect(AMatrix map, int limit, int max_edge, bool type) {
	Colorize format;
	format.Paint(14, " Input the limit to stop.", "\n");
	while (max_edge > 0) {

		int a, b;
		
		cout << "\n Vertex 1: ";
		cin >> a;
		cout << "connects to.. Vertex 2: ";
		cin >> b;
		if (a == limit || b  == limit) {
			format.Paint(12, "\n BREAK ", "\n");
			system("pause");
			break;
		}
		if (a >= limit || b >= limit) {
			format.Paint(12, " The number should be within the domain of the limit!", "\n");

			system("pause");
			return;
		}

		map.Connect(a, b, type);
		max_edge--;
	}
}

void List_BFS(Graph List, int source) {
	Colorize format;
	format.Paint(14, " Starting the BFS... ", "\n");
	list<int> print_list = List.BFS(source);
	for (auto p : print_list)
		std::cout << p << " ";
	cout << endl;
}
void List_DFS(Graph List, int source) {
	Colorize format;
	format.Paint(14, " Starting the DFS... ", "\n");
	list<int> print_list = List.DFS(source);
	for (auto p : print_list)
		std::cout << p << " ";
	cout << endl;
}
void Matrix_BFS(AMatrix map, int source) {
	Colorize format;
	format.Paint(14, " Starting the BFS... ", "\n");
	list<int> print_list = map.BFS(source);
	for (auto p : print_list)
		std::cout << p << " ";
	cout << endl;
}
void Matrix_DFS(AMatrix map, int source) {
	Colorize format;
	format.Paint(14, " Starting the DFS... ", "\n");
	list<int> print_list = map.DFS(source);
	for (auto p : print_list)
		std::cout << p << " ";
	cout << endl;
}
void Matrix() {
	int choice, limit, Edge_Limit, source, type = true; Colorize format;
	format.Paint(14, " Create an N*N Matrix where N is: ", "\n");
	cin >> limit;
	AMatrix map(limit);

	Edge_Limit = limit * (limit - 1);
	do {
		system("cls");
		format.Paint(14, " Directed: ", to_string(type)); cout << endl;
		format.Paint(14, " Select an Option: ", "\n");
		cout << "[1] Enter Graph?" << endl;
		cout << "[2] Display Matrix?" << endl;
		cout << "[3] Perform BFS?" << endl;
		cout << "[4] Perform DFS?" << endl;
		cout << "[5] Switch Type?" << endl;
		cout << "[0] Exit" << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			Matrix_Connect(map, limit ,Edge_Limit, type);break;
		case 2:
			map.Display(); 
			system("pause");
			break;
		case 3:
			format.Paint(14, "\n Select the source node: ", "\n");
			cin >> source;
			if (source >= map.Limit || source < 0) {
				format.Paint(12, " Source is beyond the node domain!", "\n");
				system("pause");
				continue;
				break;
			}
			Matrix_BFS(map, source);
			system("pause");
			break;
		case 4:
			format.Paint(14, "\n Select the source node: ", "\n");
			cin >> source;
			if (source >= map.Limit || source < 0) {
				format.Paint(12, " Source is beyond the node domain!", "\n");
				system("pause");
				continue;
				break;
			}
			Matrix_DFS(map, source);
			system("pause");
			break;
		case 5:
			if (type == true) {
				type = false;
				format.Paint(14, "\n The mode is now set to: Undirected Matrix", "\n");
			}
			else { 
			type = true;
			format.Paint(14, "\n The mode is now set to: Directed Matrix", "\n");
			}

		case 0:
			system("CLS");
			break;
		default:
			exit(1);
			break;
		}
	} while (choice != 0);
}

tuple<Graph, int, int> Enter_Graph() {
	int limit, edges;
	Colorize format;
	format.Paint(14, " Range limit of pre-allocated nodes (1 -> N-1): ", "\n");
	cin >> limit;
	format.Paint(14, " Number of potential edges: ", "\n");
	cin >> edges;
	Graph List(limit);
	return make_tuple(List,limit,edges);
}
void List() {
	int type, limit, edges, source;
	Colorize format;
	format.Paint(14, " Type of output (1 = Head, 0 = Tail): ", "\n");
	cin >> type;
	bool t;
	if (type == 0)
		t = false;
	else
		t = true;

	int choice;
	Graph List;
	do {
		system("cls");
		format.Paint(14, " Select an Option: ", "\n");
		cout << "[1] Enter Graph?" << endl;
		cout << "[2] Display connections?" << endl;
		cout << "[3] Perform BFS?" << endl;
		cout << "[4] Perform DFS?" << endl;
		cout << "[0] Exit" << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			tie(List, limit, edges) = Enter_Graph();
			if (List.Limit <= 0 || edges <= 0) {
				format.Paint(12, " The graph was not properly initialized!", "\n");
				system("pause");
				continue;
			}
			Connect(List, edges, t, limit);
			system("pause");
			break;
		case 2:
			if (List.Limit <= 0 || edges <= 0) {
				format.Paint(12, " The graph was not properly initialized!", "\n");
				system("pause");
				continue;
			}
			List.Display(type);
			system("pause");
			break;
		case 3:
			if (List.Limit <= 0 || edges <= 0) {
				format.Paint(12, " The graph was not properly initialized!", "\n");
				system("pause");
				continue;
			}
			format.Paint(14, "\n Select the source node: ", "\n");
			cin >> source;
			if (source >= List.Limit || source < 0)  {
				format.Paint(12, " Source is beyond the node limit!", "\n");
				system("pause");
				continue;
				break;
			}
			List_BFS(List, source);
			system("pause");
			break;
		case 4:
			if (List.Limit <= 0 || edges <= 0) {
				format.Paint(12, " The graph was not properly initialized!", "\n");
				system("pause");
				continue;
			}
			format.Paint(14, "\n Select the source node: ", "\n");
			cin >> source;
			if (source >= List.Limit || source < 0) {
				format.Paint(12, " Source is beyond the node limit!", "\n");
				system("pause");
				continue;
				break;
			}
			List_DFS(List, source);
			system("pause");
		case 0:
			system("CLS");
			break;
		default:
			exit(1);
			break;
		}
	} while (choice != 0);
	
}
void Menu() {
	int choice;
	Colorize format;
	do {
		system("cls");
		format.Paint(14, " Select Matrix Type: ", "\n");
		cout << "[1] Directed Adjacency Matrix?" << endl;
		cout << "[2] Undirected Adjacency List?" << endl; 
		cout << "[0] Exit" << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			Matrix();break;
		case 2:
			List();break;

		}
	} while (choice != 0);
	exit(1);
}

int main()
{
	while (true) {
		Menu();
	}
}