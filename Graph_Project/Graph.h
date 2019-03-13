#ifndef Graph_H
#define Graph_H
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <iterator>
#include <algorithm>
#include <list>
#include <random>
#include <set>
#include <stack>
#include <queue>

using namespace std;


class Graph{
private:
	struct Vertex
	{
		int data;
		Vertex *next;
		set<int> anti;
	};
	struct Neighbors
	{
		Vertex *head = NULL;
		//Vertex *tail = NULL;
	};
public:
	int counter = 0;
	int Limit; bool Type;
	list<int> print_list;
	Neighbors *adjacent;
	Graph();
	Graph(int Limit);
	Vertex* Add_Vertex(int data);
	void Connect(int before, int data, bool type);
	void Display(bool type);
	list<int> BFS(int v);
	list<int> DFS(int source);
};


class AMatrix {
private:
	int **Neighbor;
	bool *Exists;
public:
	int Limit;
	list<int> print_list;
	void Connect(int first, int second, bool type);
	void Display();
	list<int> DFS(int i);
	list<int> BFS(int i);
	AMatrix(int limit);
};
#endif
