#include "Bus.h"
#include "Graph.h"
#include <fstream>

class Company{
private:
    Graph<PoI*> map;
    vector<Bus> buses;
    vector<Tourist> tourists;
    vector<PoI> pois;
    vector <vector <PoI*> > routes;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {});
    vector<PoI> getPois();
    void addBus(int id, int capacidade);
    void removeBus(int id);
    void addTourist(int id, string nome);
    void removeTourist(int id);
    void initializeGraph(string edgeFile, string vertexFile, string tagFile);
    vector<PoI*> calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2);
    int findPoI(int id);
    vector<PoI*> calculateRouteWithOrderedPoints(vector<PoI*> points);
	void dfs(int depth, int s, int i, vector<PoI*>& c, const vector<PoI*>& v, vector<vector<PoI*> > &res);
	double getWeight(vector<PoI*> pois);
    vector<PoI*> calculateRouteWithUnorderedPoints (vector<PoI*> points);
};