#include "Company.h"

Company::Company(vector<Tourist> t = {}, vector<Bus> b = {})
{
	tourists = t;
	buses = b;
}
    
void Company::addBus(int id, int capacity)
{
    buses.push_back(Bus(id, capacity));
}
    
void Company::removeBus(int id)
{
    auto it = find(buses.begin(), buses.end(), Bus(id, 0));
    buses.erase(it);
}

void Company::addTourist(int id, string name)
{
    tourists.push_back(Tourist(id, name));
}
    
void Company::removeTourist(int id)
{
    auto it=find(tourists.begin(), tourists.end(), Tourist(id, ""));
    tourists.erase(it);
}

int Company::findPoI(int id)
{
    for(int i=0; i<pois.size();i++)
    {
        if(pois[i].getId()==id)
            return i;
    }
    return -1;
}
void Company::initializeGraph(char* edgesFile, char* vertexFile, char* tagFile){
    fstream edges(edgesFile);
    fstream vertex(vertexFile);
    fstream tags(tagFile);
    if (!edges || !vertex || !tags) {
        //ocorreu um erro
        return;
    }

    string word, line;
    int i;
    
    getline(vertex, line);
    for(int i=0; i< stoi(line);i++)
    {
        getline(vertex, word);
        string id = word.substr(1,word.find_first_not_of("0123456789",1));        
        string src= word.substr(id.size()+3,word.find_first_not_of("0123456789.",id.size()+3));
        string dest = word.substr(id.size()+src.size()+5,word.find_first_not_of("0123456789.",id.size()+src.size()+5));

        PoI vertex(stoi(id),stof(src),stof(dest));
        pois.push_back(vertex);
        map.addVertex(&vertex);
    }

    getline(edges, line);
    for(int i=0; i< stoi(line);i++)
    {
        PoI source(0,0,0); 
        PoI destination(0,0,0);
        getline(edges, word);
        string src = word.substr(1,word.find_first_not_of("0123456789",1));
        string dest= word.substr(src.size()+3,word.find_first_not_of("0123456789",src.size()+3));
        for(int j=0; j<pois.size();j++)
        {
            if(stoi(src)==pois[j].getId())
            {
                source.setID(pois[j].getId());
                source.setX(pois[j].getX());
                source.setY(pois[j].getY());
            }
    
            if(stoi(dest)==pois[j].getId())
            {
                destination.setID(pois[j].getId());
                destination.setX(pois[j].getX());
                destination.setY(pois[j].getY());
            }
        }
        float distance= sqrt(pow(destination.getX()-source.getX(),2)+ pow(destination.getY()-source.getY(),2));
        map.addEdge(&source, &destination, distance);
    }

    getline(tags, line);
    for(int i=0; i<stoi(line);i++)
    {
        getline(tags,word);
        for(int j=0; j<stoi(word);j++)
        {
            string poi;
            getline(tags, poi);
            int PoI = findPoI(stoi(poi));
            if(PoI<0)
            {
                printf("POI doesnt exist");
                return;
            }
            pois[PoI].setType(word);
        }
    }

}
vector<PoI*> Company::calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2)
{
    map.dijkstraShortestPath(point1);
    return map.getPath(point1, point2);
}

vector<PoI*> Company::calculateRouteWithOrderedPoints(vector<PoI*> points)
{
    vector<vector<PoI*> > auxVector;
    vector<PoI*> resp;
    for (int i=0; i<points.size()-1; i++)
        auxVector.push_back(calculateRouteBetweenTwoPoints(points[i], points[i+1]));
    if (auxVector.size()==0)
        return resp;
    resp=auxVector[0];
    for (int i=0; i<auxVector.size(); i++)
    {
        auxVector[i].erase(auxVector[i].begin());
        resp.insert(resp.end(), auxVector[i].begin(), auxVector[i].end());
    }
    return resp;
}