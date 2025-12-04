#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <string>
#include <set>
#include <fstream>
#include "node.h"

using namespace std;


class Graph
{
	std::set<Node*> nodes;
	typedef std::set<Node*>::const_iterator node_iterator;

public:
	Graph(const string& filename, bool head = false);
	Graph() {};
    ~Graph();
	Node* addNode(const string& name);
	Node* findNode(const string& name) const;
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end, int w);
	void removeEdge(Node* begin, Node* end);
	node_iterator end() const { return nodes.end(); }
	int node_count();
	int edges();
	set<Node*> get_nodes() const { return nodes; }
	friend ostream& operator << (ostream& out, const Graph& graph);
};

class GraphReadError {};

#endif // !_GRAPH_H_
