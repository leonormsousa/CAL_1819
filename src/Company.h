#include "Bus.h"
#include "Graph.h"
#include <fstream>
#include <ctime>

class Company{
private:
    //graph containing all the interest points (vertex) and the streets connecting them (edges) 
    Graph<PoI*> map;
    //vector containing all of the company buses
    vector<Bus> buses;
    //vector containing all the tourist/clients
    vector<Tourist> tourists;
    //vector containing all the interest points
    vector<PoI> pois;
    //vector containing all the unavailableRoads (edges that must be removed)
    vector<Edge<PoI*>> unavailableRoads;
    //capacity of the company buses
    unsigned int busesCapacity;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {}, unsigned int capacity = 20);
    vector<PoI> getPois();
    bool addBus(int id);
    bool removeBus(int id);
    bool addTourist(int id, string nome);
    bool removeTourist(int id);
    vector<Tourist>* getTourists();
    bool addUnavailableRoad(Edge<PoI*>);
    bool removeUnavailableRoad(Edge<PoI*>);
    bool addTourist(Tourist t);

    void initializeGraph(string edgeFile, string vertexFile, string tagFile);
    vector<PoI*> calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2, bool aStar);
    int findPoIindex(int id);
    vector<PoI*> calculateRouteWithOrderedPoints(vector<PoI*> points, bool aStar);
	void getPaths(const vector<PoI*>& v, vector<vector<PoI*> > &res);
	double getWeight(vector<PoI*> pois);
    vector<PoI*> calculateRouteWithUnorderedPoints (vector<PoI*> points, bool aStar);
    vector<PoI*> calculateRouteWithUnorderedPointsDynamic (const vector<PoI*> points, bool aStar);
    vector<vector<Tourist*> > createTouristGroups(unsigned int tolerance, vector<vector <PoI*> > &routes, bool aStar);
    vector<vector <PoI*> > createGroupsBasedOnBuses(unsigned int tolerance, PoI* initial, PoI* final, bool aStar);
    PoI* findPoI(int id);
    Vertex<PoI*>* findVertex(int id);
    vector<Edge<PoI*>> getUnavailableRoads();
};
