#include<iostream>
#include<vector>
#include<string>

using namespace std;

class PoI{
    int id;
    double x;
    double y;
    string tipo;
public:
    PoI(int id, double x, double y) { this->id=id; this->x=x; this->y=y;}
    int getId(){return id;}
    double getX() {  return x;}
    double getY() {  return y;}
    void setX(double x) { this->x=x;}
    void setY(double y) { this->y=y;}
    void setID(int id) {this->id=id;}
    void setType(string type) {tipo = type;}
    bool operator==(PoI p){return id == p.getId();}
};
