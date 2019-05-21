#include "Bus.h"
#include "Graph.h"

class Company{
private:
    vector<Bus> buses;
    vector<Tourist> tourists;
    vector <vector <PoI*> > routes;
    Graph <PoI*> map;
    vector<PoI> pois;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {});
    void addBus(int id, int capacidade);
    void removeBus(int id);
    void addTourist(int id, string nome);
    void removeTourist(int id);
    vector<PoI*> calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2);
    vector<PoI*> calculateRouteWithOrderedPoints(vector<PoI*> points);
    vector<PoI*> calculateRouteWithUnorderedPoints (vector<PoI*> points);
};