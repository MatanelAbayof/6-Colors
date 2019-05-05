#pragma once
#include <string>
#include <list>
#include <vector>

//---- using section --------
using std::string;

/*
 * undirected Graph class
 */
template <class T>
class Graph
{
public:
	// vertex of graph
	template <class T>
	class Vertex {
		public:
			// constructor
			Vertex(Graph<T>& graph, const T& value, int index) : m_graph(graph), m_index(index) { m_value = std::make_unique<T>(value); }
			// get adjacency list
			const std::list<Vertex<T>*>& getAdjacencyList() const { return m_graph.m_adjs[m_index]; }
			// add adjacent
			//void addAdjacent(Vertex<T>* adjVertex) { m_graph.m_adjs[m_index].push_front(adjVertex); }     // TODO add this to adj.      adjVertex->addAdjacent(this);
			// get value
			T& getValue() const { return *m_value; }
			// get index
			int getIndex() const { return m_index; }
			// convert to string
			//virtual string toString() const;
		private:
			// graph
			Graph<T>& m_graph;
			// index of vertex at graph
			int m_index;
			// my value
			std::unique_ptr<T> m_value;
	};

	// adjacency list
	using AdjList = std::list<Vertex<T>*>;

	// constructor
	Graph() = default;
	// get vertex at position
	Vertex<T>* getVertex(int index) const;
	// add vertex
	void addVertex(const T& value);
	// get number of vertices
	int getNumOfVertices() const { return static_cast<int>(m_vertices.size()); }
	// clear
	void clear();
	// convert to string
	virtual string toString() const;

	// TODO add: remove vertex, for each
private:
	// vertices
	std::vector<std::unique_ptr<Vertex<T>>> m_vertices;
	// adjacency list
	std::vector<AdjList> m_adjs;
	// check if have vertex at position
	bool isHaveVertex(int index) const { return ((index >= 0) && (index < getNumOfVertices())); }

	friend class Vertex<T>;
};


template<class T>
Graph<T>::Vertex<T>* Graph<T>::getVertex(int index) const
{
	if (!isHaveVertex(index))
		throw std::out_of_range("Cannot find vertex at " + std::to_string(index));
	return m_vertices[index].get();
}

template<class T>
void Graph<T>::addVertex(const T& value)
{
	// create new vertex
	int index = m_vertices.size();
	std::unique_ptr<Vertex<T>> vertex = std::make_unique<Vertex<T>>(*this, value, index);
	// add vertex to vector
	m_vertices.push_back(std::move(vertex));
	// add new element to adjacency list
	AdjList adjs;
	m_adjs.push_back(adjs);
}

template<class T>
void Graph<T>::clear()
{
	m_vertices.clear();
	m_adjs.clear();
}

template<class T>
string Graph<T>::toString() const
{
	return "Graph: { numOfVertices=" + std::to_string(getNumOfVertices()) + " }"; 
}
