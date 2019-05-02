#include<iostream>
#include<vector>
#include<string>

using namespace std;

class PoI{
    int id;
    string name;
    PoI(int id, string name) { this->id=id; this->name=name;};
    int getId() { return id; };
    string getName() { return name; };
}