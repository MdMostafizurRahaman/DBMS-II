#include <bits/stdc++.h>

using namespace std;

class Graph
{
	int V;												// No. of vertices
	list<int> *adj;										// Pointer to an array containing adjacency lists
	bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic()
public:
	Graph(int V);				// Constructor
	void addEdge(int v, int w); // to add an edge to graph
	bool isCyclic();			// returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
				return true;
			else if (recStack[*i])
				return true;
		}
	}
	recStack[v] = false; // remove the vertex from recursion stack
	return false;
}

bool Graph::isCyclic()
{
	bool *visited = new bool[V];
	bool *recStack = new bool[V];
	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int i = 0; i < V; i++)
		if (!visited[i] && isCyclicUtil(i, visited, recStack))
			return true;

	return false;
}

int main()
{
	freopen("input.txt", "r", stdin);
	vector<string> trans;
	string t;
	cin >> t;
	while (t != "end")
	{
		trans.push_back(t);
		cin >> t;
	}

	set<char> s;
	for (int i = 0; i < trans.size(); i++)
	{
		s.insert(trans[i][1]);
	}
	Graph g(s.size() + 1);

	for (int i = 0; i < trans.size(); i++)
	{
		string base = trans[i];
		for (int j = i + 1; j < trans.size(); j++)
		{
			string comp = trans[j];
			if (base[2] != comp[2])
			{
				continue;
			}
			else
			{
				if (base[0] == 'r' && comp[0] == 'r')
				{
					continue;
				}
				else
				{
					char c1 = base[1];
					char c2 = comp[1];
					int i1 = int(c1 - '0');
					int i2 = int(c2 - '0');
					if (i1 == i2)
						continue;
					g.addEdge(i1, i2);
				}
			}
		}
	}

	if (g.isCyclic())
		cout << "Graph contains cycle!\nThis transitions can't be conflict serializable\n";
	else
		cout << "Graph doesn't contain cycle\nThis transitions can conflict serializable\n";
	return 0;
}
