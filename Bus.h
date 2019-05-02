#include <iostream>
#include <vector>
#include <string>
#include "Tourist.h"

using namespace std;

class Bus{
private:
    int id;
    int capacidade;
    vector<Tourist*> tourists;
public:
    Bus(int id, int capacidade, vector<Tourist*> t);
    void addTourist(Tourist* t);
    void removeTourist(Tourist * t);
}