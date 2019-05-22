#include "Company.h"
#include "graphviewer.h"
#include <string>
#include <unistd.h>

using namespace std;

int main(){
	/*
    Company p = Company();
    string edgeFile= "T03/Aveiro/T03_Edges_Aveiro.txt";
    string vertexFile= "T03/Aveiro/T03_Nodes_X_Y_Aveiro.txt";
    string tagsFile= "T03/Aveiro/T03_tags_Aveiro.txt";

    p.initializeGraph(edgeFile, vertexFile, tagsFile);
    */

	GraphViewer * gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	Company p = Company();
	string edgeFile= "T03/Aveiro/T03_Edges_Aveiro.txt";
	string vertexFile= "T03/Aveiro/T03_Nodes_X_Y_Aveiro.txt";
	string tagsFile= "T03/Aveiro/T03_tags_Aveiro.txt";

	p.initializeGraph(edgeFile, vertexFile, tagsFile);

	for(size_t i=0; i<p.getPois().size();i++)
	{
		gv->addNode(p.getPois()[i].getId());
		//gv->rearrange();
	}
	// gv->addEdge(0, 0, 1, EdgeType::DIRECTED);

	// gv->setVertexLabel(2, "This is a node");
	// gv->setEdgeLabel(0, "This an edge");
	// gv->setVertexColor(2, "green");
	// gv->setEdgeColor(0, "yellow");
	// gv->setBackground("image.png");
	gv->rearrange();
	sleep(5);
	gv->closeWindow();
  
    return 0;
}
