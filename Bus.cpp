#include "Bus.h"

Bus::Bus(int id, int capacidade, vector<Tourist*> t = {})
{
    this->id=id;
    this->capacidade=capacidade;
    this->tourists=t;
}

void Bus::addTourist(Tourist* t)
{
    tourists.push_back(t);
}

void Bus::removeTourist(Tourist * t)
{
    for (auto it=tourists.begin(); it!=tourists.end(); it++)
    {
        if (*it == t)
        {
            tourists.erase(it);
            break;
        }
    }
}