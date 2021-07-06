#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stack>
#include <queue>
#include <map>
#include <list>
#include <bits/stdc++.h>

using namespace std;

class Graph
{

	int V = 0;
	list<int>* adj;
	bool donguSorgula(int v, bool visited[], int parent);

public:


	Graph(int V);
	double* betweennessCentrality();
	void add_edge(int v, int w);
	int dugumSayisi = 0;
	bool agacSorgula();

};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

}

void Graph::add_edge(int v, int w)
{
	dugumSayisi++;
	adj[v].push_back(w);
	adj[w].push_back(v);
}

bool Graph::donguSorgula(int v, bool visited[], int parent)

{
	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{

		if (!visited[*i])
		{
			if (donguSorgula(*i, visited, v))
				return true;
		}


		else if (*i != parent)
			return true;
	}
	return false;
}

bool Graph::agacSorgula()
{


	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;


	for (int u = 0; u < V; u++)
	{
		if (!visited[u]) {
			if (donguSorgula(u, visited, -1)) {
				cout << "Verilen graf bir agac degildir. Cunku dongu barindiriyor\n";
				return true;
			}
		}
		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				cout << "Verilen graf bir agac degildir. Cunku bagli olmayan dugum var\n";
				return true;
			}
		}
	}
	cout << "Verilen graf bir agactir.\n";

	return false;
}




double* Graph::betweennessCentrality()
{
	const int nodeCount = dugumSayisi;

	double* bwCentrality = new double[nodeCount]();
	vector<int>* predecessor = new vector<int>[nodeCount];

	double* dependency = new double[nodeCount];
	int* sigma = new int[nodeCount];
	int* distance = new int[nodeCount];


	for (int s = 0; s < nodeCount; s++)
	{

		stack<int> st;


		memset(distance, -1, nodeCount * sizeof(int));
		memset(sigma, 0, nodeCount * sizeof(int));
		memset(dependency, 0, nodeCount * sizeof(double));

		distance[s] = 0;
		sigma[s] = 1;
		queue<int> q;
		q.push(s);
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			st.push(v);


			list<int>::iterator it;
			for (it = adj[v].begin(); it != adj[v].end(); it++)
			{
				int w = *it;

				if (distance[w] < 0)
				{
					q.push(w);
					distance[w] = distance[v] + 1;
				}

				if (distance[w] == distance[v] + 1)
				{
					sigma[w] += sigma[v];
					predecessor[w].push_back(v);
				}
			}
		}


		while (!st.empty())
		{
			int w = st.top();
			st.pop();

			for (const int& v : predecessor[w])
			{
				if (sigma[w] != 0)
					dependency[v] += (sigma[v] * 1.0 / sigma[w]) * (1 + dependency[w]);
			}
			if (w != s)
			{

				bwCentrality[w] += dependency[w];

			}
		}
		for (int i = 0; i < nodeCount; ++i) {
			predecessor[i].clear();
		}
	}

	delete[] predecessor, sigma, dependency, distance;

	for (int i = 0; i < 20; i++) {
		cout << i << " : " << bwCentrality[i] << endl;
	}
	return bwCentrality;
}



int main()
{
	Graph G(20);
	G.add_edge(0, 2);
	G.add_edge(1, 2);
	G.add_edge(2, 3);
	G.add_edge(3, 4);
	G.add_edge(3, 10);
	G.add_edge(4, 7);
	G.add_edge(4, 5);
	G.add_edge(4, 11);
	G.add_edge(5, 7);
	G.add_edge(6, 12);
	G.add_edge(6, 18);
	G.add_edge(7, 8);
	G.add_edge(7, 9);
	G.add_edge(10, 15);
	G.add_edge(10, 11);
	G.add_edge(10, 13);
	G.add_edge(11, 13);
	G.add_edge(11, 12);
	G.add_edge(12, 14);
	G.add_edge(12, 19);
	G.add_edge(13, 14);
	G.add_edge(13, 17);
	G.add_edge(15, 16);
	G.add_edge(16, 17);
	G.add_edge(18, 19);

	G.betweennessCentrality();


	return 0;
}
