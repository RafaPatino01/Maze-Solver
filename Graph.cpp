#include "Graph.h"
#include "FiFo.h"

Graph::Graph(int pV)
{
	aV = pV;
	Adj_L = new list<int>[aV];
}

void Graph::addEdge(int v, int w)
{
	Adj_L[v].push_back(w);
}

void Graph::show(void)
{
	for (int i = 0; i < aV; i++)
	{
		cout << "Vertex " << i << "->";
		for (int neighbor : Adj_L[i])
		{
			cout << neighbor << ",";
		}
		cout << endl;
	}
}

list<int> Graph::BFS(int pS, int pE)
{
	int start = pS;

	//Crear cola
	CFiFo<int> queue = CFiFo<int>(1, 1);

	//Comenzar con todos los nodos sin visitar
	bool* visited = new bool[aV];
	for (int i = 0; i < aV; i++)
	{
		visited[i] = false;
	}

	//Marcar visitado el punto de inicio
	visited[pS] = true;
	queue.push(pS);

	//Prev
	int* prev = new int[aV];
	for (int i = 0; i < aV; i++)
	{
		prev[i] = -1;
	}

	//Loop mientras la cola tenga valores
	while (!queue.isEmpty())
	{
		//nodo actual = el que sigue en la cola
		pS = queue.front();
		queue.pop();

		cout << "Revisando nodos adyacentes al nodo " << pS << endl;
		for (auto i = Adj_L[pS].begin(); i != Adj_L[pS].end(); i++)
		{
			//Ignorarlo si ya ha sido visitad
			if (!visited[*i])
			{
				//Marcarlo como ya visitado
				cout << "Visitando nodo " << *i << endl;
				visited[*i] = true;

				//Mandarlo a la cola
				queue.push(*i);

				prev[*i] = pS;
			}
		}
	}

	list<int> path;
	for(int at = pE; at != -1; at = prev[at])
	{
		path.push_front(at);
	}
	path.reverse();

	if (path.front() == start)
	{
		return(path);
	}
	return(path);
}