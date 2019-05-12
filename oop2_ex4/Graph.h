#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

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
	class Vertex {
		public:
			// adjacency list
			using AdjList = std::unordered_set<Graph<T>::Vertex*>;
			// constructor
			explicit Vertex(Graph<T>& graph, const std::shared_ptr<T>& value, int index) : m_graph(graph), m_index(index), m_value(value) { }
			// get adjacency list
			const AdjList& getAdjacencyList() const { return m_adjs; }
			// add adjacent
			void addAdjacent(Vertex* adjVertex);
			// get value
			T& getValue() const { return *m_value; }
			// convert to string
			virtual string toString() const;
		private:
			// graph
			Graph<T>& m_graph;
			// adjacency list
			AdjList m_adjs;
			// index of vertex at graph
			int m_index;
			// my value
			std::shared_ptr<T> m_value;
			// get index
			int getIndex() const { return m_index; }
	};
	
	// constructor
	Graph() = default;
	// get vertex at position
	Vertex* getVertex(int index) const;
	// add vertex
	void addVertex(const std::shared_ptr<T>& value);
	// get number of vertices
	int getNumOfVertices() const { return static_cast<int>(m_vertices.size()); }
	// clear
	void clear();
	// convert to string
	virtual string toString() const;

	// TODO add: remove vertex, for each
private:
	// vertices
	std::vector<std::unique_ptr<Vertex>> m_vertices;
	// check if have vertex at position
	bool isHaveVertex(int index) const { return ((index >= 0) && (index < getNumOfVertices())); }

friend class Vertex;
};

template<class T>
void Graph<T>::addVertex(const std::shared_ptr<T>& value)
{
	// create new vertex
	int index = static_cast<int>(m_vertices.size());
	std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>(*this, value, index);
	// add vertex to vector
	m_vertices.push_back(std::move(vertex));
}

template<class T>
typename Graph<T>::Vertex* Graph<T>::getVertex(int index) const
{
	if (!isHaveVertex(index))
		throw std::out_of_range("Cannot find vertex at " + std::to_string(index));
	return m_vertices[index].get();
}

template<class T>
void Graph<T>::clear()
{
	m_vertices.clear();
}

template<class T>
string Graph<T>::toString() const
{
	return "Graph: { numOfVertices=" + std::to_string(getNumOfVertices()) + " }"; 
}

template<class T>
void Graph<T>::Vertex::addAdjacent(Vertex* adjVertex)
{
	// add vertex to my adjacency list 
	m_adjs.insert(adjVertex);
	// add my self to adjVertex adjacency list 
	adjVertex->m_adjs.insert(this);

	if (adjVertex->m_adjs.size() == 5) {
		int d = 5;
	}
}

template<class T>
inline string Graph<T>::Vertex::toString() const
{
	return "Vertex: { index=" + std::to_string(getIndex()) + ", numOfAdjs=" + std::to_string(m_adjs.size()) + " }";
}
