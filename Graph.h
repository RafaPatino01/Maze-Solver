#pragma once
#include <list>
#include <iostream> 
using namespace std;

class Graph
{
private:
	int aV;
public:
	list<int>* Adj_L;
	Graph(int pV);
	void addEdge(int v, int w);
	void show(void);

	list<int> BFS(int pS, int pE);
};

