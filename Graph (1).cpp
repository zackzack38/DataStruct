#include "Graph.hpp"

Vertex::Vertex()
{
  
}

Vertex:: ~Vertex()
{

}

Edge::Edge()
{
  
}

Edge::~Edge()
{

}

Graph::Graph()
{

}

Graph::~Graph()
{
  for(auto& x : vList)
  {
    delete x;
  }
}

void Graph::addVertex(std::string label)
{
  /*for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == label)
    {
      throw("Vertex already created");
    }
  }*/

  Vertex* newVertex = new Vertex;
  newVertex->name = label;
  newVertex->pos = vList.size() - 1;
  newVertex->checked = false;
  vList.push_back(newVertex);
  delete newVertex;
}

void Graph::removeVertex(std::string label)
{
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == label)
    {
      vList.erase(vItor);
    }
  }
  
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    (*vItor)->pos = (*vItor)->pos - 1;
  }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == label1)
    {
      Edge* newEdge = new Edge;
      newEdge->pos = newEdge->pos + 1;
      newEdge->a->name = label1;
      newEdge->b->name = label2;
      (*vItor)->edges.push_back(newEdge);
      delete newEdge;
    }
  }
    
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == label2)
    {
      Edge* newEdge = new Edge;
      newEdge->pos = newEdge->pos + 1;
      newEdge->a->name = label2;
      newEdge->b->name = label1;
      (*vItor)->edges.push_back(newEdge);
      delete newEdge;
    }
  }
}

void Graph::removeEdge(std::string label1, std::string label2)
{
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    for(std::vector<Edge*>::iterator eItor = (*vItor)->edges.begin(); eItor != (*vItor)->edges.end(); eItor++)
    {
      if((*eItor)->a->name == label1 && (*eItor)->b->name == label2)
      {
        (*vItor)->edges.erase(eItor);
      }
    }
  }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
  unsigned long shortestPath = ULONG_MAX;
  Vertex* curPoint;
  Vertex* endPoint;
  std::vector<unsigned long> distance(vList.size(), ULONG_MAX);
  std::vector<Vertex*> testPath(vList.size(), NULL);
  
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == startLabel)
    {
      curPoint = *vItor;
      distance.at((*vItor)->pos) = 0;
    }
  }
  
  for(std::vector<Vertex*>::iterator vItor = vList.begin(); vItor != vList.end(); vItor++)
  {
    if((*vItor)->name == endLabel)
    {
      endPoint = *vItor;
    }
  }
  
  while(!endPoint->checked)
  {
    for(std::vector<Edge*>::iterator eItor = (curPoint)->edges.begin(); eItor != (curPoint)->edges.end(); eItor++)
    {
      if(!(*eItor)->checked)
      {
        (*eItor)->checked = true;
        if(distance.at((*eItor)->pos) < distance.at(curPoint->pos))
        {
          curPoint = (*eItor)->a;
        }
      }
    }
    if(curPoint->name == endPoint->name)
    {
      Vertex* temp = endPoint;
      path.push_back(endPoint->name);
      while(testPath.at(temp->pos) != NULL)
      {
        path.push_back(testPath.at(temp->pos)->name);
        temp = testPath.at(temp->pos);
      }
      
      reverse(path.begin(),path.end());
      
      endPoint->checked = true;
      break;
    }
    
    curPoint->checked = true;
    
    for(std::vector<Edge*>::iterator eItor = (curPoint)->edges.begin(); eItor != (curPoint)->edges.end(); eItor++)
    {
      unsigned int dist = distance.at(curPoint->pos) + (*eItor)->weight;
      if(dist < distance.at((*eItor)->b->pos))
      {
        distance.at((*eItor)->b->pos) = dist;
        testPath.at((*eItor)->b->pos) = curPoint;
      }
     
    } 
    
  }
  return shortestPath;
}
