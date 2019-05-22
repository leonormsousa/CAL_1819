#include "Company.h"
#include <string>

using namespace std;

int main(){
    Company p = Company();
    string edgeFile= "T03/Aveiro/T03_Edges_Aveiro.txt";
    string vertexFile= "T03/Aveiro/T03_Nodes_X_Y_Aveiro.txt";
    string tagsFile= "T03/Aveiro/T03_tags_Aveiro.txt";

    p.initializeGraph(edgeFile, vertexFile, tagsFile);
  
    return 0;
}