#include "Bus.h"
#include "Graph.h"
#include <fstream>

class Company{
private:
    Graph<PoI*> map;
    vector<Bus> buses;
    vector<Tourist> tourists;
    vector<PoI> pois;
    vector<Edge<PoI*>> unavailableRoads;
    vector <vector <PoI*> > routes;
    vector <vector <Tourist *> > tourist_groups;
    int busesCapacity;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {}, int capacity = 20);
    vector<PoI> getPois();
    void addBus(int id);
    void removeBus(int id);
    void addTourist(int id, string nome);
    void removeTourist(int id);
    vector<Tourist> getTourists();
    bool addUnavailableRoad(Edge<PoI*>);
    bool removeUnavailableRoad(Edge<PoI*>);
    void initializeGraph(string edgeFile, string vertexFile, string tagFile);
    vector<PoI*> calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2);
    int findPoI(int id);
    vector<PoI*> calculateRouteWithOrderedPoints(vector<PoI*> points);
	void dfs(int depth, int s, int i, vector<PoI*>& c, const vector<PoI*>& v, vector<vector<PoI*> > &res);
	double getWeight(vector<PoI*> pois);
    vector<PoI*> calculateRouteWithUnorderedPoints (vector<PoI*> points);
    vector<vector<Tourist*> > createTouristGroups(unsigned int tolerance, vector<vector <PoI*> > &routes);
    void createGroupsBasedOnBuses(unsigned int tolerance);
};
