#include "Company.h"
#include <iterator>

//Company constructor
Company::Company(vector<Tourist> t, vector<Bus> b, unsigned int capacity)
{
	tourists = t;
	buses = b;
	busesCapacity = capacity;
}

//returns a vector containing all the unavailable roads/edges    
vector<Edge<PoI*>> Company::getUnavailableRoads(){
	return unavailableRoads;
}

//adds a Bus with the ID id to the vector of buses of the company
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
    
//removes the bus with the ID id from the vector of buses of the company
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

//adds a Tourist with the ID id and the Name name to the vector of tourists of the company
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

//adds the Tourist t to the vector of tourists of the company
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
    
//removes the tourist with the ID id from the vector of tourists of the company
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

//returns the index (from the vector pois) of the PoI with the ID id
int Company::findPoIindex(int id)
{
    for(size_t i=0; i<pois.size();i++)
    {
        if(pois[i].getId()==id)
            return i;
    }
    return -1;
}

//return the vector of PoIs of the company
vector<PoI> Company::getPois(){
    return pois;
}

//return the vector of tourist of the company
vector<Tourist>* Company::getTourists(){
    return &tourists;
}

//initializes the graph map and the vector pois of the company and the vector pois
//using the data stored in the edgesFile, vertexFile and tagFile
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
                cout << "PoI " << stoi(poi)<< " nao existe"<< endl;
                return;
            }
            pois[PoI].setType(word.substr(8));
        }
    }
}

//calculates the route between two points
//uses AStar or Dijkstra depending on aStar being true or false
vector<PoI*> Company::calculateRouteBetweenTwoPoints(PoI *point1, PoI *point2, bool aStar)
{
	if(aStar)
		map.AStarShortestPath(point1, point2);
	else
		map.dijkstraShortestPath(point1);
    return map.getPath(point1, point2);
}

//calculates a route between several points in the given order
vector<PoI*> Company::calculateRouteWithOrderedPoints(vector<PoI*> points, bool aStar)
{
    vector<vector<PoI*> > auxVector;
    vector<PoI*> resp;
    if (points.size()<2)
        return points;
    for (size_t i=0; i<points.size()-1; i++)
    {
    	vector<PoI*> poi =calculateRouteBetweenTwoPoints(points[i], points[i+1], aStar);
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

//calculates a Weigth of a (ordered) route (pois)
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

//calculates every combination using all the points in v, returning the answer via res
void Company::getPaths(const vector<PoI*>& v, vector<vector<PoI*> > &res)
{
	vector<PoI*> aux = v;
	sort(aux.begin(), aux.end());
	do
	{
		res.push_back(aux);
	}
	while (next_permutation(aux.begin(), aux.end()));
}

//calculates the route between several unordered points using a combinatorial algorithm
vector<PoI*> Company::calculateRouteWithUnorderedPoints (const vector<PoI*> points, bool aStar)
{
    //initializing variables
    vector<vector<PoI*> > vectorAux;
    vector<vector<PoI*> > resps;
    vector<PoI*> resp;
    vector<PoI*> auxp=points;
    if (points.size()<2)
        return points;

    PoI* point1= points[0];
    PoI* point2 = points[points.size()-1];

    //geting every combination of points
    vector<PoI*> aux;
    auxp.erase(auxp.begin());
    auxp.erase(auxp.end()-1);
    getPaths(auxp, vectorAux);
    //calculating for every combination the best route
    for (size_t i=0; i<vectorAux.size(); i++)
    {
    	vectorAux[i].insert(vectorAux[i].begin(), point1);
    	vectorAux[i].insert(vectorAux[i].end(), point2);
		vector<PoI*> p= calculateRouteWithOrderedPoints(vectorAux[i], aStar);
		if(p.size()>0)
			resps.push_back(p);
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

//calculates the route between several unordered points using a dynamic programming and a greedy algorithm
vector<PoI*> Company::calculateRouteWithUnorderedPointsDynamic (const vector<PoI*> points, bool aStar)
{
    //initializing variables
    vector <vector<double> > weigths;
    vector <vector <vector <PoI*> > > routes;
    vector <PoI*> resp;
    vector<double> aux;
    vector <vector <PoI*> > auxx;

    for (size_t i=0; i<points.size(); i++)
    {
        aux.push_back(0);
        auxx.push_back({});
    }
    for (size_t i=0; i<points.size(); i++)
    { 
        weigths.push_back(aux); 
        routes.push_back(auxx);
    }

    //calculating results for every pair of points
    for (size_t i=0; i<points.size(); i++)
    {
        for (size_t j=0; j<=i; j++)
        {

        	vector<PoI*> poi =calculateRouteBetweenTwoPoints(points[i], points[j], aStar);
        	if(poi.size()!=0)
        	{
        		routes[i][j] = poi;
                weigths[i][j]=getWeight(routes[i][j]);
        	}

    		vector<PoI*> p2 = calculateRouteBetweenTwoPoints(points[j], points[i], aStar);
    		if(p2.size()!=0)
    		{
    			routes[j][i]=p2;
    			weigths[j][i]=getWeight(routes[j][i]);
    		}

        }
    }


    resp.push_back(points[0]);
    size_t starting_point=0;
    vector<PoI*> auxr;
    //calculating best route using a greedy strategy
    for (size_t i=0; i<points.size()-2; i++)
    {
        double min_weigth=INF;
        size_t min_choice=0;
        for (size_t k=0; k<points.size(); k++)
            weigths[k][starting_point]=0;
        for (size_t j=1; j<points.size()-1; j++)
        {
            double weigth=weigths[starting_point][j];
            if (weigth!=0 && weigth<min_weigth)
            {
                min_weigth=weigth;
                min_choice=j;
            }
        }
        if (min_choice == 0)
        	return {};
        auxr = routes[starting_point][min_choice];
        auxr.erase(auxr.begin());
        resp.insert(resp.end(),auxr.begin(), auxr.end());
        starting_point=min_choice;
    }
    auxr = routes[starting_point][points.size()-1];
    auxr.erase(auxr.begin());
    resp.insert(resp.end(),auxr.begin(), auxr.end());
    return resp;
}

//creates groups of tourists based on the tolerance value; uses a greedy strategy
vector<vector<Tourist*> > Company::createTouristGroups(unsigned int tolerance, vector<vector <PoI*> > &routes, bool aStar){
    vector<Tourist> tous=tourists;
    vector<vector<Tourist*> > touristGroups;
	auto it = tous.begin();
    while (it!=tous.end())
    {
        vector<PoI*> auxp;
        vector<Tourist*> auxt;
        auxt.push_back(&(*find(tourists.begin(), tourists.end(), *it)));
		auxp = *(it->getPoIs());
		auto itt = it+1;
		while(itt != tous.end())
		{
            vector<PoI*> difference;
            set_difference((*(itt->getPoIs())).begin(), (*(itt->getPoIs())).end(), (*(it->getPoIs())).begin(),(*(it->getPoIs())).end(), inserter(difference, difference.begin()));
			if (difference.size() <= tolerance)
			{
				tolerance -= difference.size();
				auxt.push_back(&(*find(tourists.begin(), tourists.end(), *itt)));
				auxp.insert(auxp.end(), difference.begin(), difference.end());
				tous.erase(itt);
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

//creates groups of tourist, improving the groups based on the result of 
//calling createTouristGroups with different tolerances
vector< vector<PoI*> > Company::createGroupsBasedOnBuses(unsigned int initialTolerance, PoI* initial, PoI* final, bool aStar){
    vector<vector<Tourist*> > touristGroups, oldTouristGroups;
    vector<vector <PoI*> > oldRoutes, routes;
    oldTouristGroups = createTouristGroups(initialTolerance, oldRoutes, aStar);
    bool breakCycle=false;
    //decreasing tolerance to garantee the groups fit in the buses
    do
    {
        initialTolerance--;
        touristGroups=createTouristGroups(initialTolerance, routes, aStar);
        if (routes.size()>buses.size())
            break;
        for(size_t i=0; i<touristGroups.size();i++)
        	if (touristGroups[i].size()>busesCapacity)
        		breakCycle=true;
    }while (touristGroups.size()>buses.size() && (!breakCycle));
   breakCycle=false;
   oldTouristGroups= touristGroups;
   oldRoutes=routes;
   routes.clear();
   //increasing tolerance to garantee we don't get almost empty buses
    do
    {
        initialTolerance++;
        touristGroups=createTouristGroups(initialTolerance, routes, aStar);
        if (routes.size()>buses.size())
            break;
        for(size_t i=0; i<touristGroups.size();i++)
            if (touristGroups[i].size()>busesCapacity || touristGroups[i].size()==tourists.size())
                breakCycle=true;
    }while ((touristGroups.size()<oldTouristGroups.size()) && (!breakCycle));

    //calculating the routes for the tourist groups
    for (size_t i=0; i<routes.size(); i++)
    {
    	sort(routes[i].begin(), routes[i].end());
    	routes[i].erase( unique(routes[i].begin(), routes[i].end()), routes[i].end());
    	routes[i].insert(routes[i].begin(), initial);
    	routes[i].insert(routes[i].end(), final);
        routes[i]=calculateRouteWithUnorderedPoints(routes[i], aStar);

    }
    return routes;
}

//adds the Edge edge to the unavailableRoads vector
bool Company::addUnavailableRoad(Edge<PoI*> edge){
	vector<Edge<PoI*>>::iterator it = find(unavailableRoads.begin(), unavailableRoads.end(), edge);
	if(it==unavailableRoads.end()){
		unavailableRoads.push_back(edge);
		map.removeEdge(edge);
		return true;
	}
	return false;
}

//removes the Edge edge from the unavailableRoads vector
bool Company::removeUnavailableRoad(Edge<PoI*> edge){
	 vector<Edge<PoI*>>::iterator it = find(unavailableRoads.begin(), unavailableRoads.end(), edge);
	 	if(it!=unavailableRoads.end()){
	 		map.addEdge(edge);
	 		unavailableRoads.erase(it);
	 		return true;
	 	}
	 	return false;
}

//returns a pointer to the PoI with the ID id
PoI* Company::findPoI(int id)
{
	PoI poi = PoI(id, 0, 0);
	vector<PoI>::iterator it = find(pois.begin(), pois.end(), poi);
	if(it == pois.end())
		return NULL;
    return &(*it);
}

//return a pointer to the vertex wich PoI as the ID id
Vertex<PoI*>* Company::findVertex(int id){
	PoI* p1 = findPoI(id);
	if(p1==nullptr)
		return nullptr;
	return (map.findVertex(p1));
}
