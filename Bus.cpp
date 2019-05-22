#include "Bus.h"

Bus::Bus(int id, vector<Tourist*> t)
{
    this->id=id;
    this->tourists=t;
}

int Bus::getId()
{
    return id;
}

void Bus::addTourist(Tourist* t)
{
    tourists.push_back(t);
}

void Bus::removeTourist(Tourist * t)
{
    auto it=find(tourists.begin(), tourists.end(), t);
    tourists.erase(it);
}

bool Bus::operator==(Bus b)
{
    return (id == b.getId());
}
