#include "Graph.hpp"
/*
 * Deletes edges and vertex
 * for(std::deque<E*>::iterator i = list.begin(); i != list.end(); ++i) { delete *i;};
 * (*i)->thingy
 */

Graph::~Graph()
{
    for (std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        delete *i;
    }
    for (std::vector<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        delete *i;
    }
    EList.clear();
    VList.clear();
}
void Graph::addVertex(std::string label)
{
    Vertex *v = new Vertex(label, numVertex);
    v->vectorPath = {""};
    v->visitCheck = 0;
    VList.push_back(v);
    numVertex++;
}
void Graph::removeVertex(std::string label)
{
    //Vertex *v;
    int found = 0;
    // Removes the vertex with label from the graph
    for (std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if (found == 1)
        {
            (*i)->node = (*i)->node - 1;
        }
        if ((*i)->vertices.compare(label) == 0)
        {
            //v = *i;
            VList.erase(i);
            numVertex--;
            found = 1;
        }
    }
    // removes the edges between that vertex and the other vertices of the graph
    for (std::vector<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        if (((*i)->as.compare(label) == 0) || ((*i)->bs.compare(label) == 0))
        {
            EList.erase(i);
        }
    }
}
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    Edge *x = new Edge(findVertex(label1), findVertex(label2), weight);
    Edge *y = new Edge(findVertex(label2), findVertex(label1), weight);
    EList.push_back(x);
    EList.push_back(y);
}
void Graph::removeEdge(std::string label1, std::string label2)
{
    // Same as for remove vertex but this one is a tad more specific about postition
    for (std::vector<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        if (((*i)->as.compare(label1) == 0) && ((*i)->bs.compare(label2) == 0))
        {
            EList.erase(i);
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, std::less<std::pair<std::string, int>>> Q;
    for(std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i)->vertices.compare(startLabel) != 0)
        {
            (*i)->distance = INT_MAX;
        }
        else
        {
            (*i)->distance = 0; // Start node
            (*i)->vectorPath.clear();
            (*i)->vectorPath.push_back((*i)->vertices);
        }
        (*i)->visitCheck = 0;
    }
    Q.push(std::make_pair(startLabel, 0));
    std::string u;
    while (!Q.empty())
    {
        u = Q.top().first;
        Q.pop();
        for (std::vector<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
        {
            if ((*i)->as.compare(u) == 0)
            {
                if ((((*i)->a->distance + (int)(*i)->w) < (*i)->b->distance) && (*i)->b->visitCheck == 0)
                {
                    (*i)->b->distance = (*i)->a->distance + (*i)->w; //Relax it's not like I'M LIVING IN YOUR WALLS
                    if(u.compare(startLabel) == 0)
                    {
                        (*i)->b->vectorPath.clear();
                        (*i)->b->vectorPath.push_back(startLabel);
                    }
                    else
                    {
                        (*i)->b->vectorPath.clear();
                        (*i)->b->vectorPath = (*i)->a->vectorPath;
                        (*i)->b->vectorPath.push_back(u);
                    }
                    Q.push(make_pair((*i)->bs, (*i)->b->distance));
                }
            }
        }
        if(findVertex(u) != nullptr)
        {
            findVertex(u)->visitCheck = 1;
        }
    }
    int evan; //Named after Evan, he was observed doing power poses while coding
    evan = findVertex(endLabel)->distance;
    findVertex(endLabel)->vectorPath.push_back(endLabel);
    path = findVertex(endLabel)->vectorPath;
    for(std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        (*i)->distance = INT_MAX;
        (*i)->visitCheck = 0;
        (*i)->vectorPath = {""};
    }
    return evan;
}
Vertex *Graph::findVertex(std::string label)
{
    for (std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i) != nullptr)
        {
            if ((*i)->vertices.compare(label) == 0)
            {
                return (*i);
            }
        }
    }
    // If it gets to here then the vertex is not in the list
    return nullptr;
}

Vertex *Graph::findVertex(int label)
{
    for (std::vector<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i) != nullptr)
        {
            if ((*i)->node == label)
            {
                return (*i);
            }
        }
    }
    // If it gets to here then the vertex is not in the list
    return nullptr;
}
Edge *Graph::findEdge(Vertex *u, Vertex *v)
{
    for (std::vector<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        if (((*i)->a == u) && ((*i)->b == v))
        {
            return (*i);
        }
    }
    return nullptr;
}
// Used as the loop for shortestPath(): did not actually use in the end, left in as a just in case.
int Graph::allNodesVisit()
{
    int value = 0;
    for (int i = 0; i < numVertex; i++)
    {
        if (VList[i]->visitCheck == 0)
        {
            value = 1;
        }
    }
    return value;
}