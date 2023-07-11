#include "Graph.hpp"

// Destructor.
Graph::~Graph()
{
    for(auto& x : vertexes) { delete x; }
    for(auto& x : edges) { delete x; }
    vertexes.clear();
    edges.clear();
}

// Throw if input string is null.
void Graph::check_single_str(std::string input_str) 
{
    if (input_str.empty()) 
    {
        throw input_str;
    }
}

// Throw if both input strings are null.
void Graph::check_two_str(std::string input_str1, std::string input_str2) 
{
    if (input_str1.empty()) 
    {
        throw input_str1;
    }

    else if (input_str2.empty()) 
    {
        throw input_str2;
    }

    else if (input_str1.empty() && input_str2.empty()) 
    {
        throw ("String arguments contain are empty.\n");
    }
}

// Creates a vertex and adds it to the graph with a different label.
void Graph::addVertex(std::string label)
{
        check_single_str(label);
        Vertex *new_vertex = new Vertex;
        // Set initial distance to infinite
        new_vertex->vertex = label;
        new_vertex->minimum_distance = std::numeric_limits<unsigned long>::max();
        new_vertex->shortest_path = { "" };
        new_vertex->seen = false;

        // Push back into the container.
        vertexes.push_back(new_vertex); 
}

/* This function removes the vertex and the edges from the graph and uses the iterator method to get the value at that label, and
   remove it.*/
void Graph::removeVertex(std::string label)
{
    check_single_str(label);
    // This for loop removes the vertex.
    for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
    {
        if ((*ver_itr)->vertex == label) 
        {
            vertexes.erase(ver_itr);
        }

        else {}
        ++ver_itr;
    }

    // This for loop removes the edges associated with the node.
    for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) 
    {
        if (((*edg_itr)->edge_a == label) || ((*edg_itr)->edge_b == label)) 
        {
            edges.erase(edg_itr);
        }
                
        else{}
        ++edg_itr;
    }
}

// This function adds an edge to the graph between the vertex label1 and the vertex label2.
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    check_two_str(label1, label2);
    Edge *newEdge1 = new Edge(label1, label2, weight);
    Edge* newEdge2 = new Edge(label2, label1, weight);
    edges.push_back(newEdge1);
    edges.push_back(newEdge2);
}

// This function removes the edge from the graph between vertices.
void Graph::removeEdge(std::string label1, std::string label2)
{
    check_two_str(label1, label2);
    // This for loop will erase if both labels match.
    for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) 
    {
        if (((*edg_itr)->edge_a == label1) && ((*edg_itr)->edge_b == label2)) 
        {
            edges.erase(edg_itr);
        }
                
        else{}
        ++edg_itr;
    }
}

/*This function calculates the shortest path between the startLabel vertex and the endLabel vertex using greedy Dijkstra's Algorithm. 
A vector is passed into the method that stores the shortest path between the vertices. 
The return value is the sum of the edges between the start and end vertices on the shortest path.*/
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
    check_two_str(startLabel, endLabel);
    path_start(startLabel);
    construct_path(startLabel);
    lay_path(endLabel, path);
    path_reset();
    return shortest_distance;
}

// This function begins the graph at A, initilizes its distance to 0, and pushes it into the string as the shortest path.
void Graph::path_start(std::string startLabel)
{
    for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
    {
        if ((*ver_itr)->vertex == startLabel)
        {
            (*ver_itr)->minimum_distance = 0;
            (*ver_itr)->shortest_path.clear();
            (*ver_itr)->shortest_path.push_back(startLabel);
        }

        else{}
        ++ver_itr;
    }

    list_of_paths.push(std::make_pair(0, startLabel));
}

// This function traverses through the vector deque and if the minimum element matches the vertex it gets its position.
void Graph::find_minimum_vertex_idx(std::string& minimum_element)
{
    int ver_idx = 0;
    for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
    {
        if ((*ver_itr)->vertex == minimum_element) 
        {
            minimum_vertex_idx = ver_idx;
        }

        else{ ++ver_idx;}
        ++ver_itr;
    }
}

// This function uses BFS to traverse through the edge and vertex containers to push possible paths into the priority queue.
void Graph::get_minimum_distance(std::string startLabel)
{
    for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) 
    {
        if ((*edg_itr)->edge_a == minimum_element) 
        {                        
            for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
            {
                if (((*edg_itr)->edge_b == (*ver_itr)->vertex) &&
                    ((vertexes.at(minimum_vertex_idx)->minimum_distance + (*edg_itr)->weight) < (*ver_itr)->minimum_distance) &&
                    ((*ver_itr)->seen == false))
                {
                    (*ver_itr)->minimum_distance = vertexes.at(minimum_vertex_idx)->minimum_distance + (*edg_itr)->weight;
                        
                    if (minimum_element == startLabel) 
                    {
                        (*ver_itr)->shortest_path.clear(); /*Clear the path, and push A*/
                        (*ver_itr)->shortest_path.push_back(startLabel);
                    }

                    else if (minimum_element != startLabel) 
                    {
                        (*ver_itr)->shortest_path.clear();
                        (*ver_itr)->shortest_path = vertexes.at(minimum_vertex_idx)->shortest_path;
                        (*ver_itr)->shortest_path.push_back(vertexes.at(minimum_vertex_idx)->vertex);
                    }
                    
                    list_of_paths.push(std::make_pair((*ver_itr)->minimum_distance, (*ver_itr)->vertex));
                }

                else {}
                ++ver_itr;
            }
        }

        else{}
        ++edg_itr;
    }
}

// This function visits all possible paths from A to B.
void Graph::construct_path(std::string startLabel)
{
    for (;!list_of_paths.empty();) 
    {
        minimum_element = list_of_paths.top().second;
        list_of_paths.pop();
        find_minimum_vertex_idx(minimum_element);
        get_minimum_distance(startLabel);
        vertexes.at(minimum_vertex_idx)->seen = true;
    }
}
// This function puts the nodes in the vector with minimum weight and get the shortest distances from A to B.
void Graph::lay_path(std::string endLabel, std::vector<std::string>& path)
{
    for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
    {
        if (endLabel == (*ver_itr)->vertex) 
        { 
            shortest_distance = (*ver_itr)->minimum_distance;
            (*ver_itr)->shortest_path.push_back(endLabel);
            path = (*ver_itr)->shortest_path;
        }
                
        else{}
        ++ver_itr;
    }

}

// This function defaults all of the verteces of the current graph.
void Graph::path_reset()
{
    // This for loop sets the distance back to infinite.
    for (std::deque<Vertex*>::iterator ver_itr = vertexes.begin(); ver_itr != vertexes.end();) 
    {
        (*ver_itr)->minimum_distance = std::numeric_limits<unsigned long>::max();;
        (*ver_itr)->shortest_path = { "" };
        (*ver_itr)->seen = false;
        ++ver_itr;
    }
}
