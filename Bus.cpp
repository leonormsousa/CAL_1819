#include "Bus.h"

Bus::Bus(int id, int capacity, vector<Tourist*> t)
{
    this->id=id;
    this->capacity=capacity;
    this->tourists=t;
}

int Bus::getId()
{
    return id;
}

int Bus::getCapacity()
{
    return capacity;
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
    if (id == b.getId())
        return true;
    return false;
}