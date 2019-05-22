#include "Company.h"

Company::Company(vector<Tourist> t, vector<Bus> b)
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
    for(size_t i=0; i<pois.size();i++)
    {
        if(pois[i].getId()==id)
            return i;
    }
    return -1;
}

vector<PoI> Company::getPois(){
    return pois;
}
void Company::initializeGraph(string edgesFile, string vertexFile, string tagFile){
    ifstream edges;
    edges.open(edgesFile);
    ifstream vertex;
    vertex.open(vertexFile);
    ifstream tags;
    tags.open(tagFile);
    if (edges.fail() || vertex.fail() || tags.fail()) {
        //ocorreu um erro
        return;
    }

    string word, line;
    
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
        for(size_t j=0; j<pois.size();j++)
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
    if (points.size()<=2)
        return points;
    for (size_t i=0; i<points.size()-1; i++)
        auxVector.push_back(calculateRouteBetweenTwoPoints(points[i], points[i+1]));
    resp=auxVector[0];
    for (size_t i=0; i<auxVector.size(); i++)
    {
        auxVector[i].erase(auxVector[i].begin());
        resp.insert(resp.end(), auxVector[i].begin(), auxVector[i].end());
    }
    return resp;
}

double Company::getWeight(vector<PoI*> pois)
{
    double resp=0;
    for (size_t i=0; i<pois.size()-1;i++)
    {
        double aux=map.getEdgeWeight((pois[i]), (pois[i+1]));
		if (aux == -1)
			return -1;
        resp+=aux;
    }
	return resp;
}

void Company::dfs(int depth, int s, int i, vector<PoI*>& c, const vector<PoI*>& v, vector<vector<PoI*> > &res)
{
    if (depth == s)
    {
        do
        {
            res.push_back(c);
        }
        while (next_permutation(c.begin(), c.end()));
    }
    else
    {
        for (int j = i + 1; j < (int)v.size(); ++j)
        {
            c.push_back(v[j]);
            dfs(depth + 1, s, j, c, v, res);
            c.pop_back();
        }
    }
}

vector<PoI*> Company::calculateRouteWithUnorderedPoints (const vector<PoI*> points)
{
    vector<vector<PoI*> > vectorAux;
    vector<vector<PoI*> > resps;
    vector<PoI*> resp;
    vector<PoI*> auxp=points;
    if (points.size()<=2)
        return points;
    PoI* point1= points[0];
    PoI* point2 = points[points.size()-1];
    auxp.erase(points.begin());
    auxp.erase(points.begin()+points.size()-1);
    vector<PoI*> aux;
    dfs(0, points.size()-2, -1, aux, points, vectorAux);
    for (size_t i=0; i<vectorAux.size(); i++)
    {
        vectorAux[i].insert(vectorAux[i].begin(), point1);
        vectorAux[i].insert(vectorAux[i].end(), point2);
        resps.push_back(calculateRouteWithOrderedPoints(vectorAux[i]));
    }
    resp=resps[0];
    for (size_t i=0; i<resps.size(); i++)
    {
        if (getWeight(resps[i])<getWeight(resp))
            resp=resps[i];
    }
    return resp;
}