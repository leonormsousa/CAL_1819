#include<iostream>
#include<vector>
#include<string>

using namespace std;

class PoI{
    int id;
    float x;
    float y;
    string tipo;
public:
    PoI(int id, int x, int y) { this->id=id; this->x=x; this->y=y;}
    int getId(){return id;}
	float getX() { return x; }
	float getY() { return y; }

};