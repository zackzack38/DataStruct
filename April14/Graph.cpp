#include "Graph.hpp"
/*
 * Deletes edges and vertex
 * for(std::deque<E*>::iterator i = list.begin(); i != list.end(); ++i) { delete *i;};
 * (*i)->thingy
 */

Graph::~Graph()
{
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        delete *i;
    }
    for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        delete *i;
    }
}
void Graph::addVertex(std::string label)
{
    Vertex *v = new Vertex(label, numVertex);
    numVertex++;
    VList.push_front(v);
}
void Graph::removeVertex(std::string label)
{
    Vertex *v;
    int found = 0;
    // Removes the vertex with label from the graph
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if (found == 1)
        {
            (*i)->node = (*i)->node - 1;
        }

        if ((*i)->vertices == label)
        {
            v = *i;
            VList.erase(i);
            numVertex--;
            found = 1;
        }
    }
    // removes the edges between that vertex and the other vertices of the graph
    for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        if (((*i)->a == v) || ((*i)->b == v))
        {
            EList.erase(i);
        }
    }
}
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    adj_list[findVertex(label1)->node].push_back(findVertex(label2)->node);
    adj_list[findVertex(label2)->node].push_back(findVertex(label1)->node);

    Edge *x = new Edge(findVertex(label1), findVertex(label2), weight);
    Edge *y = new Edge(findVertex(label2), findVertex(label1), weight);
    EList.push_front(x);
    EList.push_front(y);
}
void Graph::removeEdge(std::string label1, std::string label2)
{
    // Same as for remove vertex but this one is a tad more specific about postition
    for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
    {
        if (((*i)->a == findVertex(label1)) && ((*i)->b == findVertex(label2)))
        {
            EList.erase(i);
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
    int D[numVertex];
    std::priority_queue<std::pair<std::string, int>> Q;
    for (int i = 0; i < numVertex; i++)
    {
        if (findVertex(startLabel)->position != i)
        {
            D[i] = INT_MAX;
        }
        else
        {
            D[i] = 0; // Start node
        }
        Q.push(make_pair(findVertex(i)->vertices, D[i]));
    }
    std::string u;
    // int ud;
    while (!Q.empty())
    {
        u = Q.top().first;
        // ud = Q.top().second;
        Q.pop();
        for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
        {
            if ((*i)->as == u)
            {
                // b and bs are adjacent to u
                if ((int)(D[findVertex(u)->node] + (*i)->w) < D[findVertex((*i)->bs)->node])
                {
                    D[(*i)->b->node] = D[findVertex(u)->node] + (*i)->w;
                    Q.push(make_pair((*i)->bs, D[(*i)->b->node]));
                    // pred[(*i)->b->node] = findVertex(u)->node; //Change to D[z] the key of vertex z in Q. ???????
                }
            }
        }
    }
    return D[findVertex(u)->node];
}
/*
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
    // Textbook implementation PG 640
    int D[numVertex];
    for (int i = 0; i < numVertex; i++)
    {
        D[i] = INT_MAX;
    }
    D[findVertex(startLabel)->node] = 0;
    auto cmp = [](int left, int right)
    { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<std::string, std::vector<int>> Q;
    for (int i = 0; i < numVertex; i++)
    {
        //Q.push(make_pair(findVertex(i)->vertices, D[i]))
    }

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, std::greater<std::pair<std::string, int>>> PList;
    // 1. Mark all nodes as unvisited.
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        (*i)->visitCheck = 0;
        // 2. Mark the initially selected node with the current distance of 0 and the rest with infinity.
        if (findVertex(startLabel) != (*i))
        {
            (*i)->distance = INT_MAX;
        }
        else
        {
            (*i)->distance = 0; // Start node
        }
    }
    PList.push(make_pair(findVertex(startLabel)->vertices, findVertex(startLabel)->distance));
    std::string minVertex;
    int alt;
    std::vector<std::string> prev;
    while (!PList.empty()) // The main loop
    {
        minVertex = PList.top().first; // Remove and return best vertex
        PList.pop();
        for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
        {
            if ((*i)->as == minVertex)
            {
                alt = (*i)->a->distance + (*i)->w;
                //Relaxation???
                if (alt < (*i)->b->distance)
                {
                    (*i)->b->distance = alt;
                    PList.push(make_pair((*i)->bs, (*i)->b->distance));
                    prev.push_back((*i)->bs);
                }
            }
        }
    }

    // 3. Set the inital node as the current node.
    std::string cur = startLabel;

    while (allNodesVisit())
    {
        // 4. For the current node, consider all of its unvisited neighbors and calculate their distances by adding the
        // current distance of the current node ot the weight of the edge that conencts the current node to the neighboring node.
        for (std::deque<Edge *>::iterator i = EList.begin(); i != EList.end(); ++i)
        {
            if ((*i)->as == cur && findVertex((*i)->bs)->visitCheck == 0)
            {
                findVertex((*i)->bs)->visitCheck = 1;
                // 5. Compare the newly calculated distance to the current distance assigned to the neighboring node. If it is smaller,
                // set it as the new current distance of the neighboring node otherwise, keep the previous weight.
                if ((findVertex(cur)->distance + (*i)->w) < findVertex((*i)->bs)->distance)
                {
                    findVertex((*i)->bs)->distance = findVertex(cur)->distance + (*i)->w;
                }
                else
                {
                    findVertex((*i)->bs)->distance = (*i)->w;
                }
            }
        }
        // 6. When you're done considering all of the unvisited neighbors of the current node, mark the current node as visited.
        findVertex(cur)->visitCheck = 1;

        // 7. Select the unvisited node that is marked with the smallest distance, set it as the new current node, and go back to step 4.
        for (int i = 0; i < numVertex; i++)
        {
            int min = INT_MAX;
            for (int ii = 0; ii < numVertex; ii++)
            {
                if (findVertex(ii)->visitCheck == 0 && findVertex(ii)->distance <= min)
                {
                    min = findVertex(ii)->distance;
                    cur = findVertex(ii)->vertices;
                }
            }
        }
        // Now repeat this process, untill all the nodes are marked as visited
    }

    int distance[numVertex];
    Vertex *prev[numVertex];
    // Q == VList
    std::deque<Vertex *, int> Q;

    int check_visit[numVertex];
    for (int i = 0; i < numVertex; i++) // Initialize Signe Souce (G, s)
    {
        if (findVertex(i)->vertices != startLabel)
        {
            distance[i] = INT_MAX; // d[v] <- inf
            check_visit[i] = 0;    // pi[v] <- nil
        }
        //Q.push_back(VList[i], distance[i]);
        prev[i] = nullptr;
    }

    distance[findVertex(startLabel)->node] = 0; // d[s] <- 0

    // Adjacency List used for subset of vertices for which the true shortest distance is known

    for (int i = 0; i < numVertex; i++)
    {
        int min = INT_MAX;
        int min_index;
        for (int ii = 0; ii < numVertex; ii++)
        {
            if (check_visit[ii] == 0 && distance[ii] <= min)
            {
                min = distance[ii];
                min_index = ii;
            }
        }
        check_visit[min_index] = 1;
    }
    // Calculates the shortest path between the vertex with startLabel and the vertex with endLabel using Dijkstra's Algorithm. A vector is passed into the method that stores the shortest path between the vertices. The return value is the sum of the edges between the start and end vertices on the shortest path.
    std::vector<std::vector<std::string>> PList;
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i)->vertices == startLabel)
        {
            (*i)->position = 0;
            path.push_back(startLabel); // Path must start, at the start
        }
    }
}
*/
Vertex *Graph::findVertex(std::string label)
{
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i)->vertices == label)
        {
            return (*i);
        }
    }
    // If it gets to here then the vertex is not in the list
    return nullptr;
}

Vertex *Graph::findVertex(int label)
{
    for (std::deque<Vertex *>::iterator i = VList.begin(); i != VList.end(); ++i)
    {
        if ((*i)->node == label)
        {
            return (*i);
        }
    }
    // If it gets to here then the vertex is not in the list
    return nullptr;
}
// Used as the loop for shortestPath()
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
/*
int main(void)
{
    Graph g;
    struct EdgeStruct
    {
        std::string a;
        std::string b;
        unsigned long w;
    };
    std::vector<std::string> vertices1{"1", "2", "3", "4", "5", "6"};
    std::vector<EdgeStruct> edges1{
        {"1", "2", 7},
        {"1", "3", 9},
        {"1", "6", 14},
        {"2", "3", 10},
        {"2", "4", 15},
        {"3", "4", 11},
        {"3", "6", 2},
        {"4", "5", 6},
        {"5", "6", 9},
    };

    std::vector<std::string> vertices2{
        "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"};
    std::vector<EdgeStruct> edges2{
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265}, {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885}, {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}};

    std::vector<std::string> vertices3{
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    std::vector<EdgeStruct> edges3{
        {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1}, {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1}, {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}};

    for (const auto label : vertices1)
        g.addVertex(label);
    for (const auto &e : edges1)
        g.addEdge(e.a, e.b, e.w);
    std::vector<std::string> path;

    std::cout << g.shortestPath("1", "5", path);
    return 0;
}
*/