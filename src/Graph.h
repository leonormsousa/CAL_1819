/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	int queueIndex = 0; 		// required by MutablePriorityQueue
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	double dist = 0;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	void removeEdge(Vertex<T> *dest);
	bool visited = false;  // for path finding
	Vertex<T> *path = nullptr;

public:
	Vertex(T in);
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	double getDist() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
	bool operator<(Vertex<T> & vertex) const; //  required by MutablePriorityQueue

};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
void Vertex<T>::removeEdge(Vertex<T> *dest){
	for (auto it=dest->incoming.begin(); it!=dest->incoming.end(); it++)
	{
		if ((*it)->orig == this)
		{
			dest->incoming.erase(it);
			break;
		}
	}
	for (auto it=outgoing.begin(); it!=outgoing.end(); it++)
	{
		if ((*it)->dest == dest)
		{
			outgoing.erase(it);
			return;
		}
	}

}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return outgoing;
}

template <class T>
double Vertex<T>::getDist() const {
	return dist;
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return info < vertex.getInfo();
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
		Vertex<T> *orig; 
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
	bool selected; 

public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w, double f);
	friend class Graph<T>;
	friend class Vertex<T>;
	double getWeight() const;
	bool operator==(Edge<T> edge);
	Vertex<T>* getDest();
	Vertex<T>* getOrig();

};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f) : orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}
template <class T>
Vertex<T>* Edge<T>::getDest(){
	return dest;
}

template <class T>
Vertex<T>* Edge<T>::getOrig(){
	return orig;
}

template <class T>
bool Edge<T>::operator==(Edge<T> edge){
	return(orig==edge.getOrig() && dest==edge.getDest());
}



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	Vertex<T>* findVertex(const T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	double getEdgeWeight(const T &sourc, const T &dest);
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
	void addEdge(Edge<T> edge);
	void removeEdge(Edge<T> edge);
	void dijkstraShortestPath(const T &origin);
	void AStarShortestPath(const T &origin);
	float euclidiandistance(const T &origin, const T &destination);
	Vertex<T> * initSingleSource(const T &origin);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	vector<T> getPath(const T &origin, const T &dest) const;

};

template <class T>
double Graph<T>::getEdgeWeight(const T &sourc, const T &dest)
{
	auto s = findVertex(sourc);
	for(size_t i = 0; i < s->getAdj().size(); i++)
	{
		if(s->getAdj()[i]->getDest()->getInfo() == dest)
			return s->getAdj()[i]->getWeight();
	}
	return -1;
}

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template<class T>
void Graph<T>::addEdge(Edge<T> edge){
	double f=0;
	addEdge(edge.orig->getInfo(), edge.dest->getInfo(), edge.weight, f);
}

template<class T>
void Graph<T>::removeEdge(Edge<T> edge){
	auto s = findVertex(edge.orig->getInfo());
	auto d = findVertex(edge.dest->getInfo());
	if (s == nullptr || d == nullptr)
		return;
	s->removeEdge(edge.dest);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
	{
		if (*(v->info) == *inf)
				return v;
	}

	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
* Initializes single-source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {

	for (unsigned int i=0; i< vertexSet.size(); i++){
		vertexSet[i]->dist = INF;
		vertexSet[i]->path = nullptr;
	}
	Vertex<T>* s = findVertex(origin);

	if(s!=nullptr)
		s->dist = 0;
	return s;
}

/**
* Analyzes an edge in single-source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

/**
* Dijkstra algorithm.
*/
template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	//cout<< "id dijkstra: " << origin->getId() << endl;

	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);

	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->outgoing) {
			auto oldDist = e->dest->dist;
			if (relax(v, e->dest, e->weight)) {
				if (oldDist == INF)
					q.insert(e->dest);
				else
					q.decreaseKey(e->dest);
			}
		}
	}
}

/**
* A* algorithm.
*/
template<class T>
void Graph<T>::AStarShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->outgoing) {
			auto oldDist = e.dest->dist + euclidiandistance(v, e);
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

/**
* Euclidian distance between two nodes
*/
template<class T>
float Graph<T>::euclidiandistance(const T &origin, const T &destination) {
	return sqrt(pow(destination.getX() - origin.getX(), 2) + pow(destination.getX() - origin.getY(), 2));
}

/**
* Get path from vertex origin to vertex dest
*/
template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	cout << "ola7" << endl;

	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF)
		 return res;


	while(v != nullptr)
	{
		res.push_back(v->info);
		if(v->path != nullptr )
			v = v->path;
		else
			break;
	}

	reverse(res.begin(), res.end());
	return res;
}

#endif /* GRAPH_H_ */
