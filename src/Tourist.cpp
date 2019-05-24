#include"Tourist.h"

using namespace std;

Tourist::Tourist(int id, string name, vector<PoI*> pois){
    this->id=id;
    this->name=name;
    poIs=pois;
}

bool Tourist::addPoI(PoI* n){
	vector<PoI*>::iterator it=find(poIs.begin(),poIs.end(),n);
	if(it == poIs.end())
	{
		poIs.push_back(n);
		return true;
	}
	return false;
}

bool Tourist::removePoI(PoI* n){
    vector<PoI*>::iterator it;
    it=find(poIs.begin(),poIs.end(),n);
    if(it != poIs.end())
    {
    	poIs.erase(it);
    	return true;
    }
    else
    	return false;
}

 int Tourist::getId(){
     return id;
 }

string Tourist::getName(){
    return name;
}

vector<PoI*>* Tourist::getPoIs(){
    return &poIs;
}

bool Tourist::operator==(Tourist t){
    return id == t.getId();
}
