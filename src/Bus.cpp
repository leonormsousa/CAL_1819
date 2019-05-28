#include "Bus.h"

//Bus constructor
Bus::Bus(int id, vector<Tourist*> t)
{
    this->id=id;
    this->tourists=t;
}

//Id getter
int Bus::getId()
{
    return id;
}

//adds Tourist t (the pointer to the tourist) to the bus' vector of tourists
void Bus::addTourist(Tourist* t)
{
    tourists.push_back(t);
}

//removes tourist t from the bus' vector of tourist
void Bus::removeTourist(Tourist * t)
{
    auto it=find(tourists.begin(), tourists.end(), t);
    tourists.erase(it);
}

//operator == defined for class Bus
bool Bus::operator==(Bus b)
{
    return (id == b.getId());
}
