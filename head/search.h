#ifndef _SEARH_H_
#define _SEARH_H_
#include "graph.h"
#include "node.h"
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

// информация об узле в процессе поиска пути
struct MarkedNode {
    Node* node; 
    int mark;
    Node* prev;
    MarkedNode(Node* anode=0, int amark=0, Node* aprev=0): 
    node(anode), mark(amark), prev(aprev) {}
};

// очередь с приоритетами
class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};

// структура пути
struct Way
{
    std::vector<Node*> nodes;
    int length;
    Way() : length(-1) {}
};

//  вывод пути
ostream& operator<<(ostream& out, const Way& way);

// алгоритм Дейкстры
class Dijkstra
{
	// храним адрес графа
    const Graph& graph;
    // раскрутка пути
    Way unroll(std::map<Node*, MarkedNode>& visited,
    Node* begin, Node* curr);
public:
	// инициализация алгоритма
    Dijkstra(const Graph& agraph) : graph(agraph) {}
    // поиск кратчайшего пути
    Way shortestWay(Node* begin, Node* end);
};

set<Node*> getConnectedComponent(Node* target);
bool isWay(Node* begin, Node* end);

#endif
