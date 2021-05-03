#include "Graph.h"

template <class KeyType, class WeightType>
template <typename ItType>
Graph<KeyType, WeightType>::Graph(ItType lnBegin, const ItType& lnEnd)
{
    vertices.push_back(Vertex(lnBegin->keyPair.first));

    cout << " Adding links:" << endl;
    for (; lnBegin != lnEnd; ++lnBegin)
    {
        if (addLink(*lnBegin) == true)
        {
            cout << " Adding  ";
        }
        else
        {
            cout << " Skiping ";
        }
        cout << lnBegin->keyPair.first
             << "<-" << lnBegin->weight << "->"
             << lnBegin->keyPair.second
             << endl;
    }
}

template <class KeyType, class WeightType>
Graph<KeyType, WeightType>::~Graph()
{
    //dtor
}

template <class KeyType, class WeightType>
bool Graph<KeyType, WeightType>::addLink(const Link& ln)
{
    VertexIt fKey = findVertex(ln.keyPair.first);
    VertexIt sKey = findVertex(ln.keyPair.second);
    VertexIt missing = vertices.end();

    if (fKey != missing || sKey != missing)
    {
        if (fKey == missing)
        {
            vertices.push_back(Vertex(ln.keyPair.first));
            fKey = --vertices.end();
        }
        if (sKey == missing)
        {
            vertices.push_back(Vertex(ln.keyPair.second));
            sKey = --vertices.end();
        }

        edges.push_back(Edge(make_pair(fKey, sKey), ln.weight));

        fKey->addLink(--edges.end());
        sKey->addLink(--edges.end());
        return true;
    }

    return false;
}

template <class KeyType, class WeightType>
typename Graph<KeyType, WeightType>::VertexIt
Graph<KeyType, WeightType>::findVertex(const KeyType& k)
{
    VertexIt it = vertices.begin();
    VertexIt itEnd = vertices.end();

    for (; it != itEnd; ++it)
    {
        if (it->key == k)
        {
            return it;
        }
    }
    return itEnd;
}

template <class KeyType, class WeightType>
Graph<KeyType, WeightType>::Vertex::Vertex(const KeyType& k)
{
    key = k;
}

template <class KeyType, class WeightType>
bool Graph<KeyType, WeightType>::Vertex::addLink(const EdgeIt& e)
{
    incEdges.push_back(e);
    return true;
}

template <class KeyType, class WeightType>
Graph<KeyType, WeightType>::Edge::Edge(const pair<VertexIt, VertexIt>& vp, const WeightType& w) :
    incVertices(vp), weight(w) { }

template <class KeyType, class WeightType>
Graph<KeyType, WeightType>::Link::Link(const pair<KeyType, KeyType>& kp, const WeightType& w) :
    keyPair(kp), weight(w) { }


template <class KeyType, class WeightType>
typename Graph<KeyType, WeightType>::VertexIt
Graph<KeyType, WeightType>::Edge::adjVertexTo(const VertexIt& v)
{
    if (incVertices.first == v)
    {
        return incVertices.second;
    }
    return incVertices.first;

}

template <class KeyType, class WeightType>
void Graph<KeyType, WeightType>::dfs()
{
    map<KeyType, bool> visited;
    dfs(vertices.begin(), visited);
}

template <class KeyType, class WeightType>
void Graph<KeyType, WeightType>::dfs(const VertexIt& v, map<KeyType, bool>& visited)
{
    visited[v->key] = true;
    cout << " " << v->key;

    typename list<EdgeIt>::iterator it = v->incEdges.begin();
    typename list<EdgeIt>::iterator itEnd = v->incEdges.end();

    for (; it != itEnd; ++it)
    {
        VertexIt w = (*it)->adjVertexTo(v);
        if (!visited[w->key])
        {
            dfs(w, visited);
        }
    }
}

template <class KeyType, class WeightType>
void Graph<KeyType, WeightType>::bfs()
{
    map<KeyType, bool> visited;
    queue<VertexIt> q;

    VertexIt v = vertices.begin();
    q.push(v);
    visited[v->key] = true;
    cout << " " << v->key;

    typename list<EdgeIt>::iterator it;
    typename list<EdgeIt>::iterator itEnd;

    while (!q.empty())
    {
        v = q.front();
        q.pop();

        it = v->incEdges.begin();
        itEnd = v->incEdges.end();

        for (; it != itEnd; ++it)
        {
            VertexIt w = (*it)->adjVertexTo(v);
            if (!visited[w->key])
            {
                cout << " " << w->key;
                q.push(w);
                visited[w->key] = true;
            }
        }
    }
}
