#include"Tourist.h"

using namespace std;

//Contructor for Tourist
Tourist::Tourist(int id, string name, vector<PoI*> pois){
    this->id=id;
    this->name=name;
    poIs=pois;
}

//adds a PoI to a Tourist
bool Tourist::addPoI(PoI* n){
	vector<PoI*>::iterator it=find(poIs.begin(),poIs.end(),n);
	if(it == poIs.end())
	{
		poIs.push_back(n);
		return true;
	}
	return false;
}

//removes a PoI from a Tourist
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

//getter for the Tourist ID
int Tourist::getId(){
     return id;
}

//getter for the Tourist name
string Tourist::getName(){
    return name;
}

//getter for the Tourist PoIs
vector<PoI*>* Tourist::getPoIs(){
    return &poIs;
}

//operator == for class Tourist
bool Tourist::operator==(Tourist t){
    return id == t.getId();
}
