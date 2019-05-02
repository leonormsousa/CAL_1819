
#include"Tourist.h"
#include<algorithm>

using namespace std;

Tourist::Tourist(int id, string name, vector<PoI> pois ={}){
    this->id=id;
    this->name=name;
    this->poIs=pois;
}

void Tourist::addPoI(PoI n){
    poIs.push_back(n);
}

void Tourist::removePoI(PoI n){
    vector<PoI>::iterator it;
    it=find(poIs.begin(),poIs.end(),n);
    poIs.erase(it);
}

 int Tourist::getId(){
     return id;
 }

string Tourist::getName(){
    return name;
}

vector<PoI> Tourist::getPoIs(){
    return poIs;
}
