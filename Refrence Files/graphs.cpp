#include "graphs.hpp"
#include <queue>

using namespace std;

Graph::Graph()
{
    
}

Graph::~Graph()
{
    
}

void Graph::addVertex(std::string cityName)
{
    vertex *newV = new vertex();
    newV->name = cityName;
    newV->visited = false;
    vertices.push_back(*newV);
}

void Graph::addEdge(std::string city1, std::string city2, int distance)
{
    vertex *temp1 = findVertex(city1);
    vertex *temp2 = findVertex(city2);
    Edge *newE = new Edge();

    newE->v = temp2;
    newE->distance = distance;

    temp1->Edges.push_back(*newE);
}

void Graph::displayEdges()
{
    for(int i=0; i<vertices.size(); i++){
        cout << vertices[i].name << "-->";
        if(!vertices[i].Edges.empty()){
            for(int j=0; j<vertices[i].Edges.size(); j++){
                Edge edge = vertices[i].Edges[j];
                if(edge.v->name != vertices[i].Edges.back().v->name)
                    cout << edge.v->name << " (" << edge.distance << " miles)***";
                else
                    cout << edge.v->name << " (" << edge.distance << " miles)" << endl;
            }
        }else{
            cout << endl;
        }
    }
}

void Graph::printDFT()
{
    for(int i=0; i<vertices.size(); i++){
        DFT_traversal(&vertices[i]);
    }
    setAllVerticesUnvisited();
}

void Graph::printBFT()
{
    for(int i=0; i<vertices.size(); i++){
        BFT_traversal(&vertices[i]);
    }
    setAllVerticesUnvisited();
}

void Graph::setAllVerticesUnvisited()
{
    for(int i=0; i<vertices.size(); i++){
        vertices[i].visited = false;
    }
}

vertex *Graph::findVertex(std::string name)
{
    for(int i=0; i<vertices.size(); i++){
        if(vertices[i].name == name)
            return &vertices[i];
    }
}

void Graph::DFT_traversal(vertex *v)
{
    if(!v->visited){
        cout << v->name << endl;
        v->visited = true;
        for(int i=0; i<v->Edges.size(); i++){
            DFT_traversal(v->Edges[i].v);
        }
    }
}


void Graph::BFT_traversal(vertex *v)
{
    std::queue<vertex*> vertexQueue;
    vertexQueue.push(v);

    while(!vertexQueue.empty()){
        v = vertexQueue.front();
        vertexQueue.pop();
        if(!v->visited){
            cout << v->name << endl;
            v->visited = true;
            for(int i=0; i<v->Edges.size(); i++){
                vertexQueue.push(v->Edges[i].v);
            }
        }
    }
}