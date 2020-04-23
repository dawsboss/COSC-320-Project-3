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
			int id;
			T data;
			double cost;
			std::vector<int> vertices;
			std::vector<int> verticesParent;

			VertexStuff(T d, double c, int i){
				id = i;
				data = d;
				cost = c;
				vertices = std::vector<int>();
				verticesParent = std::vector<int>();
			}
			VertexStuff(){
				//oof
				// vertices = std::vector<int>();
				// verticesParent = std::vector<int>();
			}
		};
		int ID = 1;

		std::map<int, VertexStuff> v;
		//std::vector<VertexStuff> v;
		//std::map<int, std::vector<int>> vertices;
		//std::map<int, std::vector<int>> verticesParent;

	public:
		Graph();
		//Graph(Graph&);
		//Graph& operator=(Graph&);
		//~Graph();

		std::vector<T> findStarts();//Finds all vertices that are starting points/dont have anything pointing to it
		std::vector<T> findEnd(); //Finds the end of the jobs/where to stop

		//void addData(std::string);//takes in file name and adds all the data from the file into the map

		//std::map<int, std::vector<T>> findPath();//TODO This is the hard part bois, we fins all paths and rank them 1 being the best and n being the worst

		void addVertex(T,double);
		void addEdge(T,T);
		void print();
		// void printBfs(T);
};

#include "Graph.cpp"
#endif
