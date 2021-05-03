#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
    typedef Graph<char, int> Graph;
    typedef Graph::Link Link;

    vector<Link> links;
    links.push_back(Link(make_pair('A', 'B'), 2));
    links.push_back(Link(make_pair('A', 'C'), 2));
    links.push_back(Link(make_pair('A', 'E'), 2));
    links.push_back(Link(make_pair('B', 'D'), 7));
    links.push_back(Link(make_pair('B', 'F'), 7));
    links.push_back(Link(make_pair('C', 'G'), 7));
    links.push_back(Link(make_pair('E', 'F'), 5));

    Graph myGraph(links.begin(), links.end());
    myGraph.dfs();
    myGraph.bfs();

    return 0;
}