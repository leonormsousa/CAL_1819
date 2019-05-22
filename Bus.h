#include "Tourist.h"

using namespace std;

class Bus{
private:
    int id;
    vector<Tourist*> tourists;
public:
    Bus(int id, vector<Tourist*> t = {});
    int getId();
    void addTourist(Tourist* t);
    void removeTourist(Tourist * t);
    bool operator==(Bus b);
};
