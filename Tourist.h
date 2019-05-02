#include<iostream>
#include<vector>
#include<string>
#include"PoI.h"

using namespace std;

class Tourist{
    int id;
    string name;
    vector<PoI> poIs;
    Tourist(int id, string name, vector<PoI> poIs);
    void addPoI(PoI n);
    void removePoI(PoI n);
    int getId(); 
    string getName();
    vector<PoI> getPoIs();
}