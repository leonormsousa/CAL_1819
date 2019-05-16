#include "Bus.h"
#include "Graph.h"
#include <fstream>

class Company{
private:
    Graph<PoI> map;
    vector<Bus> buses;
    vector<Tourist> tourists;
    vector<PoI> pois;
    vector <vector <PoI*> > routes;
public:
	Company(vector<Tourist> t = {}, vector<Bus> b = {});
    void addBus(int id, int capacidade);
    void removeBus(int id);
    void addTourist(int id, string nome);
    void removeTourist(int id);
    void initializeGraph(char* filename);
};