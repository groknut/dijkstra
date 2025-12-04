#include "../head/search.h"

// методы приоритетной очереди
MarkedNode PriorityQueue::pop() {
    MarkedNode mn = nodes.back();
    nodes.pop_back();
    return mn;
}

// добавление элемента
void PriorityQueue::push(Node* node, int mark, Node* prev) {
    std::vector<MarkedNode>::iterator it = nodes.begin();
    MarkedNode mn(node, mark, prev);
    while (it != nodes.end() && mark < it->mark) 
        ++it;
    if (it == nodes.end()) 
        nodes.push_back(mn);
    else 
        nodes.insert(it, mn);
}

// ищем короткий путь
Way Dijkstra::shortestWay(Node* begin, Node* end) {

	if (!begin || !end)
	{
		Way way = Way(); 
		way.length = -2;
	 	return way;
	}

	else if (isWay(begin, end))
	{
		Way way = Way(); 
		way.length = -3;
	 	return way;	
	}

    PriorityQueue nodes; 
    nodes.push(begin, 0, nullptr);
    std::map<Node*, MarkedNode> visited;
	// пока у нас есть узлы для обработки
    while (!nodes.empty()) 
    {
    	// получаем последний узел нашей очереди
        MarkedNode next = nodes.pop();
		// если его уже посещали, то пропускаем
        if (visited.find(next.node) != visited.end())
            continue;
		// текущий узел добавляем в посещенные
        visited[next.node] = next;
        // если этот узел конечный, то возвращаем путь
        if (end==next.node) 
            return unroll(visited,begin,end);
		// иначе пробегаемся по соседям нашего узла
        for (auto it = next.node->nb_begin(); it!=next.node->nb_end(); it++)
        {
            int weight = next.mark + it->second;
            if (visited.find(it->first) == visited.end())
                nodes.push(it->first, weight, next.node);
        }
    }
    return Way();
}

Way Dijkstra::unroll(std::map<Node*, MarkedNode>& visited, 
    Node* begin, Node* curr)
{
    Way way;
    way.length = visited[curr].mark;

    while (curr != begin) {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
    }

    way.nodes.push_back(begin);

    return way;
}

ostream& operator<<(ostream& out, const Way& way)
{

    if (way.length == -1)
	    out << "Shortest way not find" << std::endl;
    else if (way.length == -2)
    	out << "One node or both nodes not found" << std::endl;
    else if (way.length == -3)
        	out << "Nodes not connected" << std::endl;
    else
    {
        for (int i = way.nodes.size() - 1; i >= 0; i--)
            out << way.nodes[i]->getName() << " ";
    }
    return out;
}


set<Node*> getConnectedComponent(Node* target)
{

	// set<Node*> nodes = graph.get_nodes();
	set<Node*> target_nodes;
	queue<Node*> visited;

	if (!target)
		return target_nodes;

	target_nodes.insert(target);
	visited.push(target);

	while (!visited.empty())
	{
		Node* curr = visited.front();
		visited.pop();

		for (auto it = curr->nb_begin(); it != curr->nb_end(); it++)
		{
			Node* neigh = it->first;

			if (target_nodes.find(neigh) == target_nodes.end())
			{
				target_nodes.insert(neigh);
				visited.push(neigh);
			}
			
		}		
	}
	return target_nodes;
}

bool isWay(Node* begin, Node* end)
{
	set<Node*> nodes = getConnectedComponent(begin);
	return nodes.find(end) == nodes.end();
}
