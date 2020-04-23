#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>

template<class T>
class Graph{
	private:
		struct VertexStuff{
			int id; //the index it is held at in the map
			T data; //data given to us by the user
			double cost; //cost in time give from user
			std::vector<int> vertices; //where this node points out ot list
			std::vector<int> verticesParent; //what points at this node list

			VertexStuff(T d, double c, int i){//constructor for new edges
				id = i;
				data = d;
				cost = c;
				vertices = std::vector<int>();
				verticesParent = std::vector<int>();
			}
			VertexStuff(){//Needed for map RB_tree
			}
		};
		int ID = 1;//ID couinter that the add vertex uses

		std::map<int, VertexStuff> v;//main map that holds all nodes with their meta data

	public:
		Graph();

		std::vector<T> findStarts();//Finds all vertices that are starting points/dont have anything pointing to it
		std::vector<T> findEnd(); //Finds the end of the jobs/where to stop

		void addVertex(T,double);
		void addEdge(T,T);
		void print();
};

#include "Graph.cpp"
#endif
