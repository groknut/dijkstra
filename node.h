#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <map>

using namespace std;

class Node
{
	typedef std::map<Node*, int>::const_iterator node_iterator;
	std::string name;
    std::map<Node*, int> neighbours;
	void addneighbour(Node* neighbour, int w);
	void removeNeighbour(Node* neighbour);
public:
	Node(const std::string& aname) : name(aname) {}
	const std::string& getName() const { return name; }
	node_iterator nb_begin() const { return neighbours.begin(); }
	node_iterator nb_end() const { return neighbours.end(); }
	friend class Graph;
	const std::map<Node*, int>& get_neighbours() const { return neighbours; }
    int getWeight(Node* node) const;
    int countWay() {return neighbours.size();}
};

#endif
