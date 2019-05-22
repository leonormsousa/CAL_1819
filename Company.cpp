#include "Company.h"
#include <iterator>

Company::Company(vector<Tourist> t, vector<Bus> b, int capacity)
{
	tourists = t;
	buses = b;
	busesCapacity = capacity;
}
    
void Company::addBus(int id)
{
    buses.push_back(Bus(id));
}
    
void Company::removeBus(int id)
{
    auto it = find(buses.begin(), buses.end(), Bus(id));
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

int Company::findPoIindex(int id)
{
    for(size_t i=0; i<pois.size();i++)
    {
        if(pois[i].getId()==id)
            return i;
    }
    return -1;
}

vector<PoI> Company::getPois(){
    return pois;
}

vector<Tourist> Company::getTourists(){
    return tourists;
}


void Company::initializeGraph(string edgesFile, string vertexFile, string tagFile){
    ifstream edges;
    edges.open(edgesFile);
    ifstream vertex;
    vertex.open(vertexFile);
    ifstream tags;
    tags.open(tagFile);
    if (edges.fail() || vertex.fail() || tags.fail()) {
        //ocorreu um erro
        return;
    }

    string word, line;
	cout << "Reading poi..." << endl;
    getline(vertex, line);
    for(int i=0; i< stoi(line);i++)
    {
        getline(vertex, word);
		word = word.substr(1);
        string id = word.substr(0,word.find_first_not_of("0123456789",1));
		word = word.substr(id.size()+2);
        string src= word.substr(0,word.find_first_of(","));
		word = word.substr(src.size()+2);
        string dest = word.substr(0,word.find_first_not_of("0123456789.",0));

        PoI vertex(stoi(id),stod(src),stod(dest));
        pois.push_back(vertex);
        map.addVertex(&vertex);
    }

	cout << "Reading edges..." << endl;
    getline(edges, line);
    for(int i=0; i< stoi(line);i++)
    {
		PoI source =PoI(0, 0, 0);

        PoI destination(0,0,0);
        getline(edges, word);
		word = word.substr(1);
        string src = word.substr(0,word.find_first_not_of("0123456789",0));
		word = word.substr(src.size()+2);
        string dest= word.substr(0,word.find_first_not_of("0123456789",0));

		source.setID(stoi(src));
		vector<PoI>::iterator it = find(pois.begin(), pois.end(), source);
		
		destination.setID(stoi(src));
		vector<PoI>::iterator it2 = find(pois.begin(), pois.end(), destination);

		double distance = sqrt(pow(it2->getX() - it->getX(), 2) + pow(it2->getY() - it->getY(), 2));

		map.addEdge(&(*it), &(*it2), distance);

    }

	cout << "Reading tags..." << endl;
    getline(tags, line);
	string numLines;
    for(int i=0; i<stoi(line);i++)
    {	
        getline(tags,word);
		getline(tags, numLines);
        for(int j=0; j<stoi(numLines);j++)
        {
            string poi;
            getline(tags, poi);
            int PoI = findPoIindex(stoi(poi));
            if(PoI<0)
            {
                cout << "POI doesnt exist"<< endl;
                return;
            }
            pois[PoI].setType(word);
        }
    }
}

vector<PoI*> Company::calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2)
{
    map.dijkstraShortestPath(point1);
    return map.getPath(point1, point2);
}

vector<PoI*> Company::calculateRouteWithOrderedPoints(vector<PoI*> points)
{
    vector<vector<PoI*> > auxVector;
    vector<PoI*> resp;
    if (points.size()<=2)
        return points;
    for (size_t i=0; i<points.size()-1; i++)
        auxVector.push_back(calculateRouteBetweenTwoPoints(points[i], points[i+1]));
    resp=auxVector[0];
    for (size_t i=0; i<auxVector.size(); i++)
    {
        auxVector[i].erase(auxVector[i].begin());
        resp.insert(resp.end(), auxVector[i].begin(), auxVector[i].end());
    }
    return resp;
}

double Company::getWeight(vector<PoI*> pois)
{
    double resp=0;
    for (size_t i=0; i<pois.size()-1;i++)
    {
        double aux=map.getEdgeWeight((pois[i]), (pois[i+1]));
		if (aux == -1)
			return -1;
        resp+=aux;
    }
	return resp;
}

void Company::dfs(int depth, int s, int i, vector<PoI*>& c, const vector<PoI*>& v, vector<vector<PoI*> > &res)
{
    if (depth == s)
    {
        do
        {
            res.push_back(c);
        }
        while (next_permutation(c.begin(), c.end()));
    }
    else
    {
        for (int j = i + 1; j < (int)v.size(); ++j)
        {
            c.push_back(v[j]);
            dfs(depth + 1, s, j, c, v, res);
            c.pop_back();
        }
    }
}

vector<PoI*> Company::calculateRouteWithUnorderedPoints (const vector<PoI*> points)
{
    vector<vector<PoI*> > vectorAux;
    vector<vector<PoI*> > resps;
    vector<PoI*> resp;
    vector<PoI*> auxp=points;
    if (points.size()<=2)
        return points;
    PoI* point1= points[0];
    PoI* point2 = points[points.size()-1];
    auxp.erase(points.begin());
    auxp.erase(points.begin()+points.size()-1);
    vector<PoI*> aux;
    dfs(0, points.size()-2, -1, aux, points, vectorAux);
    for (size_t i=0; i<vectorAux.size(); i++)
    {
        vectorAux[i].insert(vectorAux[i].begin(), point1);
        vectorAux[i].insert(vectorAux[i].end(), point2);
        resps.push_back(calculateRouteWithOrderedPoints(vectorAux[i]));
    }
    resp=resps[0];
    for (size_t i=0; i<resps.size(); i++)
    {
        if (getWeight(resps[i])<getWeight(resp))
            resp=resps[i];
    }
    return resp;
}

vector<vector<Tourist*> > Company::createTouristGroups(unsigned int tolerance, vector<vector <PoI*> > &routes){
    vector<Tourist> tous=tourists;
    vector<vector<Tourist*> > touristGroups;
	auto it = tous.begin();
    while (it!=tous.end())
    {
        vector<PoI*> auxp;
        vector<Tourist*> auxt;
        auxt.push_back(&(*find(tourists.begin(), tourists.end(), *it)));
		auxp = it->getPoIs();
		auto itt = it;
		while(itt != tous.end())
		{
            vector<PoI*> difference;
            set_difference(itt->getPoIs().begin(), itt->getPoIs().end(), it->getPoIs().begin(), it->getPoIs().end(), inserter(difference, difference.begin()));
			if (difference.size() <= tolerance)
			{
				tolerance -= difference.size();
				auxt.push_back(&(*find(tourists.begin(), tourists.end(), *itt)));
				auxp.insert(auxp.end(), difference.begin(), difference.end());
				itt++;
				tous.erase(itt-1);
				continue;
			}
			itt++;
		}
		routes.push_back(auxp);
		touristGroups.push_back(auxt);
		it++;
    }
	return touristGroups;
}

void Company::createGroupsBasedOnBuses(unsigned int initialTolerance){
    vector<vector<Tourist*> > touristGroups, oldTouristGroups;
    vector<vector <PoI*> > routess, oldRoutes;
    oldTouristGroups = createTouristGroups(initialTolerance, oldRoutes);
    do
    {
        initialTolerance--;
        touristGroups=createTouristGroups(initialTolerance, routess);
        if (routess.size()>buses.size())
            break;
        if (touristGroups.size()>busesCapacity)
            break;   
    }while (touristGroups.size()>buses.size());
    do
    {
        initialTolerance++;
        touristGroups=createTouristGroups(initialTolerance, routess);
        if (routess.size()>buses.size())
            break;
        if (touristGroups.size()>busesCapacity)
            break;   
    }while (touristGroups.size()<oldTouristGroups.size());
    routes=oldRoutes;
    tourist_groups=oldTouristGroups;
    for (size_t i=0; i<routes.size(); i++)
    {
        routes[i]=calculateRouteWithUnorderedPoints(routes[i]);
    }
}

PoI* Company::findPoI(int id)
{
	PoI poi = PoI(id, 0, 0);
	return find(pois.begin(), pois.end(), poi);
}
