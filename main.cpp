#include <iostream> 
#include <locale.h> 
#include <fstream>
#include "graph.h"
#include "node.h"
#include "search.h"

using namespace std;

void write(const string& filename, bool head, const string& start_name, const string& end_name);
void helper(const string& program);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

    if (argc == 4)
        write(argv[1], false, argv[2], argv[3]);

    else if (argc == 5 && argv[1] == string("-h"))
        write(argv[2], true, argv[3], argv[4]);
    
    else
    {
        helper(argv[0]);
        return 0;
    }

	return 0;
}

void write(const string& filename, bool head, const string& start_name, const string& end_name)
{
    Graph graph(filename, head);
    Node* start = graph.findNode(start_name);
    Node* end = graph.findNode(end_name); 

    Dijkstra dijkstra(graph);
    Way way = dijkstra.shortestWay(start, end);

    if (way.length < 0)
    	cout << way << std::endl;
    else
   	{
		cout << "Shortest way: " << way << std::endl;
 		cout << "Length way: " << way.length << std::endl;     		 		
   	}

}

void helper(const string& program)
{

	cout << "Example:" << std::endl;
	cout << program << "<file> <startNode> <endNode>: standard file reading" << std::endl;

	cout << program << "-h <file> <startNode> <endNode>: standard file reading without taking into account the header" << std::endl;

	cout << "The file is accepted in the following format: Source, Target, Weight" << std::endl;
}
