#include "Company.h"
#include <iterator>

Company::Company(vector<Tourist> t, vector<Bus> b, unsigned int capacity)
{
	tourists = t;
	buses = b;
	busesCapacity = capacity;
}
    
vector<Edge<PoI*>> Company::getUnavailableRoads(){
	return unavailableRoads;
}


bool Company::addBus(int id)
{
    Bus b(id);

	auto it = find(buses.begin(), buses.end(), b);
	if(it == buses.end())
	{
		buses.push_back(b);
		return true;
	}
	return false;
}
    
bool Company::removeBus(int id)
{
    auto it = find(buses.begin(), buses.end(), Bus(id));
	if(it!=buses.end())
	{
		buses.erase(it);
		return true;
	}
	return false;
}

bool Company::addTourist(int id, string name)
{
	Tourist t(id, name);

	auto it = find(tourists.begin(), tourists.end(), t);
	if(it == tourists.end())
	{
		tourists.push_back(t);
		return true;
	}
	return false;
}

bool Company::addTourist(Tourist t)
{
	auto it = find(tourists.begin(), tourists.end(), t);
	if(it == tourists.end())
	{
		tourists.push_back(t);
		return true;
	}
	return false;
}
    
bool Company::removeTourist(int id)
{
    auto it=find(tourists.begin(), tourists.end(), Tourist(id, ""));
    if(it!=tourists.end())
    {
    	tourists.erase(it);
    	return true;
    }
    return false;
}

PoI* Company::getinitialPoint(){
	return initialPoint;
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

vector<Tourist>* Company::getTourists(){
    return &tourists;
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


        PoI* vertex = new PoI(stoi(id),stod(src),stod(dest));
        pois.push_back(*vertex);
        if(i==0)
        	initialPoint=vertex;

        map.addVertex(vertex);
    }

	cout << "Reading edges..." << endl;
    getline(edges, line);
    for(int i=0; i< stoi(line);i++)
    {
        getline(edges, word);
		word = word.substr(1);
        string src = word.substr(0,word.find_first_not_of("0123456789",0));
		word = word.substr(src.size()+2);
        string dest= word.substr(0,word.find_first_not_of("0123456789",0));

		PoI* poi1 = findPoI(stoi(src));
		PoI* poi2 = findPoI(stoi(dest));


		double distance = sqrt(pow(poi2->getX() - poi1->getX(), 2) + pow(poi2->getY() - poi1->getY(), 2));

		map.addEdge(poi1, poi2, distance);

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
            pois[PoI].setType(word.substr(8));
        }
    }

    Vertex<PoI*>* v= findVertex(26018648);
    for(int i=0; i<v->getAdj().size(); i++)
    		cout << i << "  " << v->getAdj()[i]->getDest()->getInfo()->getId() << endl;
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
    {
    	vector<PoI*> poi =calculateRouteBetweenTwoPoints(points[i], points[i+1]);
    	if(poi.size()==0)
		{
    		vector<PoI*> p = {};
    		return p;
		}
    	else
    		auxVector.push_back(poi);
    }

    resp=auxVector[0];

    for (size_t i=1; i<auxVector.size(); i++)
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

void Company::dfs(const vector<PoI*>& v, vector<vector<PoI*> > &res)
{
vector<PoI*> aux = v;
	sort(aux.begin(), aux.end());
        do
        {
            res.push_back(aux);
        }
        while (next_permutation(aux.begin(), aux.end()));


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

    vector<PoI*> aux;

    dfs(points, vectorAux);
    for (size_t i=0; i<vectorAux.size(); i++)
    {
    	if(((*vectorAux[i][0])== (*point1)) && ((*vectorAux[i][vectorAux[i].size()-1]) == (*point2)))
    	{
    		vector<PoI*> p= calculateRouteWithOrderedPoints(vectorAux[i]);
    		if(p.size()>0)
    			resps.push_back(p);
    	}
    }
    if(resps.size()==0)
    {
    	vector<PoI*> p = {};
    	return p;
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
		auxp = *(it->getPoIs());
		auto itt = it;
		while(itt != tous.end())
		{
            vector<PoI*> difference;
            set_difference((*(itt->getPoIs())).begin(), (*(itt->getPoIs())).end(), (*(it->getPoIs())).begin(),(*(it->getPoIs())).end(), inserter(difference, difference.begin()));
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

vector< vector<PoI*> > Company::createGroupsBasedOnBuses(unsigned int initialTolerance){
    vector<vector<Tourist*> > touristGroups, oldTouristGroups;
    vector<vector <PoI*> > oldRoutes, routes;
    oldTouristGroups = createTouristGroups(initialTolerance, oldRoutes);
    do
    {
        initialTolerance--;
        touristGroups=createTouristGroups(initialTolerance, routes);
        if (routes.size()>buses.size())
            break;
        if (touristGroups.size()>busesCapacity)
            break;   
    }while (touristGroups.size()>buses.size());
    do
    {
        initialTolerance++;
        touristGroups=createTouristGroups(initialTolerance, routes);
        if (routes.size()>buses.size())
            break;
        if (touristGroups.size()>busesCapacity)
            break;   
    }while (touristGroups.size()<oldTouristGroups.size());
    routes=oldRoutes;
    tourist_groups=oldTouristGroups;

    for (size_t i=0; i<routes.size(); i++)
    {
    	auto it=find(routes[i].begin(), routes[i].end(),initialPoint);
		if (it!= routes[i].end())
			routes[i].erase(it);
		routes[i].insert(routes[i].begin(), initialPoint);
		routes[i].insert(routes[i].end(), initialPoint);
        routes[i]=calculateRouteWithUnorderedPoints(routes[i]);
    }
    return routes;
}

bool Company::addUnavailableRoad(Edge<PoI*> edge){
	vector<Edge<PoI*>>::iterator it = find(unavailableRoads.begin(), unavailableRoads.end(), edge);
	if(it==unavailableRoads.end()){
		unavailableRoads.push_back(edge);
		map.removeEdge(edge);
		return true;
	}
	return false;
}
 bool Company::removeUnavailableRoad(Edge<PoI*> edge){
	 vector<Edge<PoI*>>::iterator it = find(unavailableRoads.begin(), unavailableRoads.end(), edge);
	 	if(it!=unavailableRoads.end()){
	 		map.addEdge(edge);
	 		unavailableRoads.erase(it);
	 		return true;
	 	}
	 	return false;
 }
PoI* Company::findPoI(int id)
{
	PoI poi = PoI(id, 0, 0);
	vector<PoI>::iterator it = find(pois.begin(), pois.end(), poi);
	if(it == pois.end())
		return NULL;
    return &(*it);
}

Vertex<PoI*>* Company::findVertex(int id){
	PoI* p1 = findPoI(id);
	if(p1==nullptr)
	{
		cout << "didnt find poi" << endl;
		return nullptr;

	}
	cout << "p1 was found" << endl;

	return (map.findVertex(p1));
}
