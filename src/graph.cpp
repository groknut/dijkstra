#include "../head/graph.h"

int Graph::node_count()
{
	return (int)nodes.size();
}

int Graph::edges()
{
	int cnt = 0;
	for (Node* node : nodes)
		cnt += (int)node->neighbours.size();
	return cnt / 2;
}

Graph::Graph(const string& filename, bool head)
{
    ifstream in(filename);

    if (!in.is_open())
        throw GraphReadError();

    if (head)
    {
        string s;
        getline(in, s);
    }
  
    int a, b, c;
    while (in >> a >> b >> c)
    {
        Node* node_a = addNode(to_string(a));
		Node* node_b = addNode(to_string(b));
		addEdge(node_a, node_b, c);
    }
}

void Graph::removeNode(Node* node)
{
	nodes.erase(node);

	for (std::set<Node*>::iterator it = nodes.begin();
		it != nodes.end(); it++)
		(*it)->removeNeighbour(node);
}

Node* Graph::addNode(const string& name)
{

	for (Node* node : nodes)
	{
		if (node->getName() == name)
			return node;
	}
	Node* node_1 = new Node(name);
	nodes.insert(node_1);
	return node_1;
}

void Graph::addEdge(Node* begin, Node* end, int w)
{
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addneighbour(end, w);
	end->addneighbour(begin, w);
}

Node* Graph::findNode(const string& name) const
{
	for (Node* node : nodes)
	{
		if (node->getName() == name)
			return node;
	}
	return nullptr;
}

void Graph::removeEdge(Node* begin, Node* end)
{
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}

ostream& operator << (ostream& out, const Graph& graph) 
{
    out << "Node: countWay" << std::endl;
	for (Node* node : graph.get_nodes())
	{
		out << node->getName() << ": " << node->countWay() << std::endl;
	}
	return out;

}

Graph::~Graph()
{
    for (auto node: nodes)
        delete node;
    nodes.clear();
}
