#include "Company.h"

Company::Company(vector<Tourist> t = {}, vector<Bus> b = {})
{
	tourists = t;
	buses = b;
}
    
void Company::addBus(int id, int capacity)
{
    buses.push_back(Bus(id, capacity));
}
    
void Company::removeBus(int id)
{
    auto it = find(buses.begin(), buses.end(), Bus(id, 0));
    buses.erase(it);
}

void Company::addTourist(int id, string name)
{
    tourists.push_back(Tourist(id, name));
}
    
void Company::removeTourist(int id)
{
    auto it=find(tourists.begin(), tourists.end(), Tourist(id, ""));
    tourists.erase(it);
}

void Company::initializeGraph(char* edgesFile){
    fstream edges(edgesFile);

    if (!edges) {
        //ocorreu um erro
        return;
    }

    string word, line;
    int i;

    getline(edges, line);

    for(int i=0; i< stoi(line);i++)
    {
        getline(edges, word);
        string src = word.substr(1,word.find_first_not_of("0123456789",1));
        string destination= word.substr(src.size()+3,word.find_first_not_of("0123456789",1));
        for(int j=0; j<pois.size();j++)
            if(pois[j].)
        map.addEdge()
    }

}