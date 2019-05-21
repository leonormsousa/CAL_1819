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
    for (int i=0; i<points.size()-1; i++)
        auxVector.push_back(calculateRouteBetweenTwoPoints(points[i], points[i+1]));
    resp=auxVector[0];
    for (int i=0; i<auxVector.size(); i++)
    {
        auxVector[i].erase(auxVector[i].begin());
        resp.insert(resp.end(), auxVector[i].begin(), auxVector[i].end());
    }
    return resp;
}

vector<PoI*> Company::calculateRouteWithUnorderedPoints (vector<PoI*> points)
{
    vector<vector<PoI*> > vectorAux;
    if (points.size()<=2)
        return points;
    PoI* point1= points[0];
    PoI* point2 = points[points.size()-1];

}

int C(vector<PoI*> pois, PoI* point1)
{
    for (int s=1; s<pois.size(); s++)
    {
        vector<PoI*> aux=pois;
        aux.resize(s+1);
        //for (auto it=)

    }
}