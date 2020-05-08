#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>//stdmap
#include <vector>//std::vector
#include <queue>//std::queue
#include <algorithm>//std::sort
#include <fstream>//read in File

template<class T>
class Graph{
	private:
		bool dir=true;//T == Dirrected | F == UnDirrected
		bool DFSneeded=false;//If DFS saved it correct or not True == needs update/ False == all good
		int time=0;
		bool Acyclic=true;
		bool DAG;
		enum color_t{
			WHITE, GREY, BLACK
		};
		struct VertexStuff{
			int id; //the index it is held at in the map
			T data; //data given to us by the user
			double cost; //cost in time give from user
			std::vector<int> vertices; //where this node points out ot list
			std::vector<int> verticesParent; //what points at this node list
			color_t color;//DFS: color for current node
			color_t colorBFS;//BFS: color for cuurent node / Probabily could just be color instead of a new variable...
			int distanceBFS=-1;//BFS: distance form start node
			int P;//used as parent index place holder for BFs and DFS
			int start;//DFS: holds time when started in DFS algorithm
			int finish;//DFS: holdstime when finished in DFS algorithm
			int tLevel;
			int bLevel;
			int ALAPLevel;
			bool isChecked=false;//Used to check to see if a node has already been added to the jobs map

			VertexStuff(T d, double c, int i){//constructor for new edges
				id = i;
				data = d;
				cost = c;
				vertices = std::vector<int>();
				verticesParent = std::vector<int>();
				color = WHITE;
				colorBFS=WHITE;
				P=-1;
				tLevel = 0;
				bLevel = 0;
			}
			VertexStuff(){//Needed for map RB_tree
			}
		};
		int ID = 1;//ID couinter that the add vertex uses

		int CP_Length;

		std::map<int, VertexStuff> v;//main map that holds all nodes with their meta data
		std::map<int,std::vector<int>> jobs;//Map of <BFSlevels, nodes in level>

		void PaddEdge(int,int);//Private addition of adding edge

		std::vector<std::pair<int, int>> reverseTopoSort(); // Returns a reverse topological ordering of the graph as a vector
		std::vector<std::pair<int, int>> topoSort(); // Returns a topological sort of the graph as a vector
		void computeTLevel(); // Computes the T level of the graph
		void computeBLevel(); // Computes the B level of the graph
		void computeALAP(); // Computes the As Late As Possible level of the graph
		void driver();

	public:
		void JobLevelBFS();

		Graph();//This is the same as the Graph(bool) but it just doesn't init dir NOTE: This is extremely unsafe to use... if you do use it make sure you init bool dir
		void initDIR(bool);//This will init dir to give in bool
		Graph(bool);//T == Dirrected | F == UnDirrected

		void graphType();


		std::vector<int> findStarts();//Finds all vertices that are starting points/dont have anything pointing to it, returns the index of all starts in a vector
		std::vector<int> findEnd(); //Finds the end of the jobs/where to stop, returns the index of all ends in a vector

		void addVertex(T,double);
		void addEdge(T,T);
		void print();
		void DFS();
		void DFS_Visit(int);
		void SCCDFS_Visit(int node);
		void SCC();
		void printAnalytics(); // Prints the Analytics of the graph into a data table structure
};

#include "Graph.cpp"
#endif
