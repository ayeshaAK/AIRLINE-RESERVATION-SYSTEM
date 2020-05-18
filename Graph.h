#pragma once

#include "ArrayBasedSet.h"
#include "ListBasedSet.h"

template <typename T/*type of data stored by each vertex*/, typename S/*weight of each edge*/>
class Graph
{
	struct Vertex;
	struct NeighbourNode;
	struct Vertex
	{
		T data;
		ListBasedSet<NeighbourNode> neighbours;
		Vertex()
		{
			neighbours.clear();
		}
		Vertex(T d) :data(d) {}
		Vertex(T x, ListBasedSet<NeighbourNode> n)
		{
			neighbours.clear();
			neighbours = n;
			data = x;
		}
		Vertex(const Vertex & v)
		{
			*this = v;
		}
		const Vertex & operator = (const Vertex & obj)
		{
			if (this == &obj)
				return *this;
			neighbours = obj.neighbours;
			data = obj.data;
			return *this;
		}
		void display()
		{
			data.display();
			cout << " ";
			neighbours.display();
			cout << "\n-----------------------------------------------------------------------------------------" << endl;
		}
		bool operator==(const Vertex& obj)
		{
			return data == obj.data;
		}
		bool addNeighbour(T neighbour, S weight/*,int add*/)
		{//returns false if neighbor already exists
			if (neighbours.insert(NeighbourNode(neighbour, weight/*,add*/)))
				return true;
			else
			{
				NeighbourNode* n = neighbours.getNodeAddress(NeighbourNode(neighbour, weight/*,add*/));
				//n->weight = std::min(n->weight, weight);
				if (weight < n->weight)
					n->weight = weight;
				return false;
			}
		}
		bool removeNeighbour(T neighbour)
		{//returns false if neighbor doesn't exists
			return neighbours.removeElement(NeighbourNode(neighbour));
		}
		S getWeight(T destination)
		{
			NeighbourNode* add = neighbours.getNodeAddress(NeighbourNode(destination));
			if (add)
				return add->weight;
		}
		~Vertex() {}
	};
	struct NeighbourNode
	{
		T data;
		S weight;
		//int address;
		NeighbourNode()/*:address(NULL)*/ {}
		NeighbourNode(T x) :data(x)/*,address(0)*/ {}
		NeighbourNode(T x, S w/*, int add*/)
		{
			data = x;
			weight = w;
			//address=add;
		}
		NeighbourNode(const NeighbourNode & n)
		{
			*this = n;
		}
		const NeighbourNode & operator = (const NeighbourNode & obj)
		{
			if (this == &obj)
				return *this;
			data = obj.data;
			weight = obj.weight;
			//address=obj.address;
			return *this;
		}
		void display()
		{
			data.display();cout << "(";weight.display();cout << ") ";
		}
		bool operator==(const NeighbourNode& obj)
		{
			return data == obj.data;
		}
		~NeighbourNode() {};
	};
	ArrayBasedSet <Vertex> vertices;
public:
	Graph() {}
	void insertVertex(T vertexData)
	{
		vertices.addElement(Vertex(vertexData));
		cout << "Vertex added ";
		vertexData.display();
		cout << endl;
	}
	bool insertEdge(const T& source, const T& destination, const S& weight)
	{
	here:
		if (vertices.presentAt(destination) + 1/*destination index contains -1*/)
		{
			int s = vertices.presentAt(source);
			if (s + 1) //source doesnt exist
			{
				if (!vertices[s].addNeighbour(destination, weight/*,s*/))
				{
					cout << "neighbour already exists but smaller weight retained\n";
				}
			}
			else
			{
				cout << "source not present in graph, it is now added\n";
				insertVertex(source);
				goto here;
				return false;
			}
			source.display();destination.display();weight.display();cout << endl;
			return true;
		}
		cout << "destination not present in graph, it is now added\n";
		insertVertex(destination);
		goto here;
		return false;
	}
	bool removeEdge(T source, T destination)
	{
		if (vertices.presentAt(destination) + 1/*destination index contains -1*/)
		{
			int s = vertices.presentAt(source);
			if (s + 1) //source doesnt exist
			{
				if (!vertices[s].removeNeighbour(destination))
				{
					cout << "neighbour doesnt exist\n";
					return false;
				}
			}
			else
			{
				return false;
			}
			return true;
		}
		return false;
	}
	int removeVertex(T vertexData)
	{
		//find index of vertex
		int index = -1;
		for (unsigned int i = 0; i < vertices.getSize(); i++)
		{
			if (vertices[i] == vertexData)
			{
				index = i;
				break;
			}
		}
		if (index + 1)
		{//the vertex exists
			int edgesRemoved = 0;
			for (unsigned int i = 0; i < vertices.getSize(); i++)
			{
				if (removeEdge(vertices[i].data, index))
					edgesRemoved++;
			}
			vertices[index].neighbours.clear();
			vertices.removeByIndex(index);
			return edgesRemoved;
		}
		return 0;
	} //returns the number of edges removed to remove this vertex

	void display()
	{
		vertices.display();
	}

	S getWeight(const T& source, const T& destination)
	{
		if (vertices.presentAt(destination) + 1)
		{
			//reach node of source
			int s = vertices.presentAt(source);
			if (s + 1)
			{
				return vertices[s].getWeight(destination);
			}
		}
		return S();
	}
	Vector<T> getAllVertex()
	{
		Vector<T> arr;
		for (int i = 0; i < vertices.getSize(); i++)
		{
			arr.addAtEnd(vertices[i].data);
		}
		return arr;
	}

	Vector<Vector<S>> getAllPaths(T start, T end) {
		bool* visited = new bool[vertices.getSize()];
		for (int i = 0; i < vertices.getSize(); i++)
			visited[i] = false;
		Vector<Vector<S>> all;
		visited[vertices.presentAt(start)] = true;
		print(start, end, Vector<S>(), visited, all);
		return all;
	}



	void print(T start, T end, Vector<S>& path, bool visited[], Vector<Vector<S>>& allPaths) {
		int startVertexIndex = vertices.presentAt(start);
		Vector<S> newPath = path;
		//newPath.addAtEnd(start);
		visited[startVertexIndex] = true;
		ListBasedSet<NeighbourNode> list = vertices[startVertexIndex].neighbours;
		for (int i = 0; i < list.size(); i++) {
			NeighbourNode node = *(list.getAtIndex(i));
			//ensure that all returned paths are such that one flight is after the other in terms of date and time
			if (newPath.getSize() > 0)
			{
				if (!(newPath[newPath.getSize() - 1] < node.weight))
				{
					continue;
				}
			}
			newPath.addAtEnd(node.weight);
			if (!(node.data == end)) 
			{
				if (visited[vertices.presentAt(node.data)] == false) {
					visited[vertices.presentAt(node.data)] = true;
					print(node.data, end, newPath, visited, allPaths);
				}
			}
			else if (node.data == end) {
				allPaths.addAtEnd(newPath);
				for (int i = 0; i < newPath.getSize(); i++)
				{
					newPath[i].display();
					cout << " -> ";
				}
				cout << endl;
			}
			newPath.removeLast();
		}
		//remove from path

		visited[startVertexIndex] = false;
	}

	~Graph() {}
};
