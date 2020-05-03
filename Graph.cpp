//Defualt constructor
template<class T>
Graph<T>::Graph(bool d){
	dir = d;
}
template<class T>
Graph<T>::Graph(){
}

template<class T>
void Graph<T>::initDIR(bool d){
	dir = d;
}

//Prints back what type of a graph the current session is set to
template<class T>
void Graph<T>::graphType(){
	if(dir){
		std::cout<<"Dirrected"<<std::endl;
	}else{
		std::cout<<"Undirrected"<<std::endl;
	}
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
		DFSneeded=true;
		v.insert(std::make_pair(ID, VertexStuff(newData, price, ID)));//Makes a new element in the v map with the given properties (newData and price)
		ID++;//Sets up the ID for the next vertex to be added
}

//addEdge : Adds edge based on index

template<class T>
void Graph<T>::PaddEdge(int Parent, int child){
	if(Parent>=ID || child>=ID || Parent<=0 || child<=0){//Is parent or child invalid?
		std::cout<<"Parent or child invalid/too big!"<<std::endl;// "<<Parent<<" "<<child
		return;
	}

	DFSneeded=true;


	for(auto i=v[Parent].vertices.begin(); i!=v[Parent].vertices.end(); ++i){
		if(*i == child){//Proves that parent and child already havea  connection
			return;
		}
	}
	DFSneeded=true;
	v[Parent].vertices.push_back(child);
	v[child].verticesParent.push_back(Parent);
	if(!dir){
		v[child].vertices.push_back(Parent);
		v[Parent].verticesParent.push_back(child);
	}
}

//addEdge : adds edge by value
template<class T>//TODO fix this stuff (5,5)edge case
void Graph<T>::addEdge(T Parent, T child){
	int p=-1, c=-1;
	 //std::cout<<"Parent/child "<<Parent<<" "<<child<<"\n";
	for(auto i=v.begin(); i!=v.end(); ++i){
		// std::cout<<"i->second.data "<<i->first<<" "<<i->second.data<<std::endl;
		if(i->second.data == Parent)
			p=i->first;
		if(i->second.data == child)
			c=i->first;
	}
	PaddEdge(p,c);
}

//print : prints out all verticies and where they point
template<class T>
void Graph<T>::print(){
	DFS();
	std::cout<<"The graph is ";
	if(!Acyclic)
		std::cout<<"NOT ";
	std::cout<<"Acyclic and is ";
	if(!DAG)
		std::cout<<"NOT ";
	std::cout<<"a DAG and is ";
	graphType();

	std::cout<<std::endl;

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

	for (auto i = v.begin(); i != v.end(); ++i) {
		std::cout << "Vector: " << v[i->first].data << std::endl;
		std::cout << "T-Level: " << v[i->first].tLevel << std::endl;
		std::cout << "B-Level: " << v[i->first].bLevel << std::endl;
	}
}

template<class T>
void Graph<T>::DFS(){
	if(DFSneeded){
		for(auto i=v.begin(); i!=v.end(); ++i){
			v[i->first].color=WHITE;
		}
		time=0;
		for(auto i=v.begin(); i!=v.end(); ++i){
			if(v[i->first].color == WHITE)
				DFS_Visit(i->first);
		}
		DFSneeded=false;
		if(!dir){
			DAG=false;
			return;
		}
		if(!Acyclic){
			DAG=false;
		}else{
			DAG=true;
		}

	}
}

template<class T>
void Graph<T>::DFS_Visit(int node){
	time++;
	//std::cout<<"time: "<<time<<" node: "<<node<<" "<<v[node].data<<std::endl;
	v[node].start=time;
	v[node].color=GREY;
	for(auto i=v[node].vertices.begin(); i!=v[node].vertices.end(); ++i){
		//std::cout<<"!!!!"<<v[node].color<<" node: "<<node<<" "<<v[node].data<<std::endl;
		if(v[*i].color == GREY)
			Acyclic=false;
		if(v[*i].color == WHITE){
			v[*i].P=node;
			DFS_Visit(*i);
		}
	}
	v[node].color=BLACK;
	time++;
	//std::cout<<"====time: "<<time<<" node: "<<node<<" "<<v[node].data<<std::endl;
	v[node].finish=time;
}

/*
   reverseTopoSort Function:
   Returns a topological sort of the current graph
*/
template<class T>
std::vector<std::pair<int, int>> Graph<T>::reverseTopoSort() {
	DFS();
	if(!DAG){
		throw std::runtime_error("Graph is not a DAG! Can't topologicalSort...");
	}

	std::vector<std::pair<int,int>> topoList;

	for(auto i=v.begin(); i!=v.end(); ++i){
		topoList.push_back(std::pair<int,int>(i->second.finish,i->second.id));
	}
	std::sort(topoList.begin(), topoList.end());
	
	return topoList;
}

/*
   topoSort Function:
   Returns a reverse topological sort of the current graph
*/
template<class T>
std::vector<std::pair<int, int>> Graph<T>::topoSort(){
	DFS();
	if(!DAG){
		throw std::runtime_error("Graph is not a DAG! Can't topologicalSort...");
	}

	std::vector<std::pair<int,int>> topoList;

	for(auto i=v.begin(); i!=v.end(); ++i){
		topoList.push_back(std::pair<int,int>(i->second.finish,i->second.id));
	}

	/*
	for(auto i=topolist.rbegin(); i!=topolist.rend(); ++i){
		std::cout<<i->second<<" time "<<i->first<<"| ";
	}
	std::cout<<std::endl;
	*/
	std::sort(topoList.begin(), topoList.end());
	std::reverse(topoList.begin(), topoList.end());

	return topoList;
}

/*
   computeTLevel Function:
   Computes the T level of the graph 
*/
template<class T>
void Graph<T>::computeTLevel() {
	std::vector<std::pair<int, int>> TopList = topoSort();
	int max;
	for (std::vector<std::pair<int, int>>::iterator it = TopList.begin(); it != TopList.end(); ++it) {
		max = 0;
		for (std::vector<int>::iterator i = v[it->second].verticesParent.begin(); i != v[it->second].verticesParent.end(); ++i) {
			if ((v[*i].tLevel + v[*i].cost) > max) {
				max = v[*i].tLevel + v[*i].cost;
			}
		}
		v[it->second].tLevel = max;
	}
}

/*
   computeBLevel Function:
   Computes the B level of the graph
*/
template<class T>
void Graph<T>::computeBLevel() {
	std::vector<std::pair<int, int>> RevTopList = reverseTopoSort();
	int max;
	for (auto it = RevTopList.begin(); it != RevTopList.end(); ++it) {
		std::cout << "Vector ID: " << v[it->second].data << " Finish Time: " << it->first << std::endl;
	}
	for (std::vector<std::pair<int, int>>::iterator it = RevTopList.begin(); it != RevTopList.end(); ++it) {
		max = 0;
		for (std::vector<int>::iterator i = v[it->second].vertices.begin(); i != v[it->second].vertices.end(); ++i) {
			if (v[*i].bLevel > max) {
				max = v[*i].bLevel;
			}
		}
		v[it->second].bLevel = v[it->second].cost + max;
	}
}

template<class T>
void Graph<T>::SCC(){
	DFS();
	std::map<int,int> topolist;
	for(auto i=v.begin(); i!=v.end(); ++i){
		topolist.insert(std::pair<int,int>(i->second.finish,i->first));
		v[i->first].color=WHITE;
	}
	time=0;
	for(auto i=topolist.rbegin(); i!=topolist.rend(); ++i){
		//std::cout<<"Checking: "<<i->second<<std::endl;
		if(v[i->second].color == WHITE){
			SCCDFS_Visit(i->second);
		}
		std::cout<<std::endl;
	}
}

template<class T>
void Graph<T>::SCCDFS_Visit(int node){
	time++;
	v[node].color=GREY;
	for(auto i=v[node].verticesParent.begin(); i!=v[node].verticesParent.end(); ++i){
		if(v[*i].color == WHITE){
			v[*i].P=node;
			SCCDFS_Visit(*i);
		}
	}
	v[node].color=BLACK;
	time++;
	std::cout<<v[node].data<<" ";
}


