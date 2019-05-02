#include "Tourist.h"

using namespace std;

class Bus{
private:
    int id;
    int capacity;
    vector<Tourist*> tourists;
public:
    Bus(int id, int capacity, vector<Tourist*> t = {});
    int getId();
    int getCapacity();
    void addTourist(Tourist* t);
    void removeTourist(Tourist * t);
    bool operator==(Bus b);
};