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