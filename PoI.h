#include<iostream>
#include<vector>
#include<string>

using namespace std;

class PoI{
    int id;
    int x;
    int y;
    string tipo;
public:
    PoI(int id, int x, int y) { this->id=id; this->x=x; this->y=y;}
    int getId(){return id;}
};