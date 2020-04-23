//Defualt constructor
template<class T>
Graph<T>::Graph(){

}

//Finds all vertices that are starting points/dont have anything pointing to it
template<class T>
std::vector<T> Graph<T>::findStarts(){
	std::vector<T> rtn;
	for( auto i=v.begin(); i!=v.end(); ++i){
		if(i->second.verticesParent.empty()){//If a node has nothing point to it as a vertex then it is a "start"
			rtn.push_back(i->first);
			std::cout<<"start: "<<i->second.data<<std::endl;
		}
	}
	return rtn;
}

//Finds the end of the jobs/where to stop
template<class T>
std::vector<T> Graph<T>::findEnd(){
	std::vector<T> rtn;
	for( auto i=v.begin(); i!=v.end(); ++i){
		if(i->second.vertices.empty()){//If a node doesn;t have any verteces then it is a "end"
			rtn.push_back(i->first);
			std::cout<<"end: "<<i->second.data<<std::endl;
		}
	}
	return rtn;
}

//addVertex : adds a new vertex to the map - starts with no edges
template<class T>
void Graph<T>::addVertex(T newData, double price){
		v.insert(std::make_pair(ID, VertexStuff(newData, price, ID)));//Makes a new element in the v map with the given properties (newData and price)
		ID++;//Sets up the ID for the next vertex to be added
}

//addEdge : This will give the parent node a edge to the child node
template<class T>
void Graph<T>::addEdge(T Parent, T child){
	int p=-1, c=-1;//p and c are parent and child indexs
	bool haveP = false, haveC = false;//Shows if the for loop can stop
	for(auto i=v.begin(); i!=v.end(); ++i){
		if(v[i->first].data == Parent){//if there is a parent save it's index
			p = i->first;
			haveP = true;
		}
		if(v[i->first].data == child){//if there is a child save it's index
			c = i->first;
			haveC = true;
		}
		if(haveP && haveC){//If both the parent and child were vcalid, add them
			v[p].vertices.push_back(c);
			v[c].verticesParent.push_back(p);
			return;
		}
	}

		std::cout<<"Couldn't add edge, parent or child invalid"<<std::endl;//Prints if it couldn't find the parent or child
		return;
}

//print : prints out all verticies and where they point
template<class T>
void Graph<T>::print(){
	for(auto i=v.begin(); i!=v.end(); ++i){//printsd where a node points // runs through all of the nodes
		std::cout<<"Vector: "<<v[i->first].data<<" points to: ";
		for(auto j=v[i->first].vertices.begin(); j!=v[i->first].vertices.end(); ++j){//takes each node's meta data to print
			std::cout<<v[*j].data<<" cost: "<<v[*j].cost<<" ID: "<<i->first<<" | ";
		}
		std::cout<<std::endl;
	}

	std::cout<<std::endl;
	std::cout<<"parents: "<<std::endl;
	std::cout<<std::endl;

	for(auto i=v.begin(); i!=v.end(); ++i){//Prints the same thing as above but what points to one node
		std::cout<<"Vector: "<<v[i->first].data<<" is pointed to by: ";
		for(auto j=v[i->first].verticesParent.begin(); j!=v[i->first].verticesParent.end(); ++j){
			std::cout<<v[*j].data<<"'s' cost: "<<v[*j].cost<<" ID: "<<i->first<<" | ";
		}
		std::cout<<std::endl;
	}
}
