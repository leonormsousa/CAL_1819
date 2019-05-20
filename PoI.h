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
    PoI(int id, float x, float y) { this->id=id; this->x=x; this->y=y;}
    int getId(){return id;}
    float getX() {  return x;}
    float getY() {  return y;}
    void setX(float x) { this->x=x;}
    void setY(float y) { this->y=y;}
    void setID(int id) {this->id=id;}
    void setType(string type) {tipo = type;}

};