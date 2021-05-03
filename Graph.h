#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

template <class KeyType, class WeightType>
class Graph
{
public:
    class Edge;
    class Vertex;
    typedef typename list<Vertex>::iterator VertexIt;
    typedef typename list<Edge>::iterator EdgeIt;

    class Vertex
    {
        friend class Graph;

        Vertex(const KeyType& k);
        bool addLink(const EdgeIt& e);

        list<EdgeIt> incEdges;
        KeyType key;
    };

    class Edge
    {
        friend class Graph;

        Edge(const pair<VertexIt, VertexIt>& vp, const WeightType& w);
        VertexIt adjVertexTo(const VertexIt& v);

        pair<VertexIt, VertexIt> incVertices;
        WeightType weight;
    };

    struct Link
    {
        Link(const pair<KeyType, KeyType>& kp, const WeightType& w);
        pair<KeyType, KeyType> keyPair;
        WeightType weight;
    };

    template <typename ItType> Graph(ItType lnBegin, const ItType& lnEnd);
    ~Graph();

    bool addLink(const Link& ln);
    VertexIt findVertex(const KeyType& k);
    void dfs(const VertexIt& v, map<KeyType, bool>& visited);
    void dfs();
    void bfs();

    list<Vertex> vertices;
    list<Edge> edges;
};

#endif // GRAPH_H