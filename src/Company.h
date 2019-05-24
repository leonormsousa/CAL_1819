#include "Bus.h"
#include "Graph.h"
#include <fstream>

class Company{
private:
    Graph<PoI*> map;
    PoI* initialPoint;
    vector<Bus> buses;
    vector<Tourist> tourists;
    vector<PoI> pois;
    vector<Edge<PoI*>> unavailableRoads;
    vector <vector <Tourist *> > tourist_groups;
    unsigned int busesCapacity;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {}, unsigned int capacity = 20);
    vector<PoI> getPois();
    bool addBus(int id);
    bool removeBus(int id);
    bool addTourist(int id, string nome);
    bool removeTourist(int id);
    PoI* getinitialPoint();
    vector<Tourist>* getTourists();
    bool addUnavailableRoad(Edge<PoI*>);
    bool removeUnavailableRoad(Edge<PoI*>);
    bool addTourist(Tourist t);

    void initializeGraph(string edgeFile, string vertexFile, string tagFile);
    vector<PoI*> calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2);
    int findPoIindex(int id);
    vector<PoI*> calculateRouteWithOrderedPoints(vector<PoI*> points);
	void dfs(const vector<PoI*>& v, vector<vector<PoI*> > &res);
	double getWeight(vector<PoI*> pois);
    vector<PoI*> calculateRouteWithUnorderedPoints (vector<PoI*> points);
    vector<vector<Tourist*> > createTouristGroups(unsigned int tolerance, vector<vector <PoI*> > &routes);
    vector<vector <PoI*> > createGroupsBasedOnBuses(unsigned int tolerance);
    PoI* findPoI(int id);
    Vertex<PoI*>* findVertex(int id);
    vector<Edge<PoI*>> getUnavailableRoads();
};
