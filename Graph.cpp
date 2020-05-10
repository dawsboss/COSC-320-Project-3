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
std::vector<int> Graph<T>::findStarts(){
	std::vector<int> rtn;
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
std::vector<int> Graph<T>::findEnd(){
	std::vector<int> rtn;
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
	for(auto i=v.begin(); i!=v.end(); ++i){
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
	v[node].start=time;
	v[node].color=GREY;
	for(auto i=v[node].vertices.begin(); i!=v[node].vertices.end(); ++i){
		if(v[*i].color == GREY)
			Acyclic=false;
		if(v[*i].color == WHITE){
			v[*i].P=node;
			DFS_Visit(*i);
		}
	}
	v[node].color=BLACK;
	time++;
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
	CP_Length = 0;
	for (std::vector<std::pair<int, int>>::iterator it = TopList.begin(); it != TopList.end(); ++it) {
		max = 0;
		for (std::vector<int>::iterator i = v[it->second].verticesParent.begin(); i != v[it->second].verticesParent.end(); ++i) {
			if ((v[*i].tLevel + v[*i].cost) > max) {
				max = v[*i].tLevel + v[*i].cost;
			}
		}
		v[it->second].tLevel = max;
		if (max > CP_Length) {
			CP_Length = max + v[it->second].cost;
		}
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

/*
   computeALAP Function:
   Computes the As Late As Possible metadate for each node in the graph
*/
template<class T>
void Graph<T>::computeALAP() {
	std::vector<std::pair<int, int>> RevTopList = reverseTopoSort();
	int min_ft;
	for (std::vector<std::pair<int, int>>::iterator it = RevTopList.begin(); it != RevTopList.end(); ++it) {
		min_ft = CP_Length;
		for (std::vector<int>::iterator i = v[it->second].vertices.begin(); i != v[it->second].vertices.end(); ++i) {
			if ((v[*i].ALAPLevel) < min_ft) {
				min_ft = v[*i].ALAPLevel;
			}
		}
		v[it->second].ALAPLevel = min_ft - v[it->second].cost;
	}
}

/*
   printAnalytics Function:
   Prints the Analytics of the graph into a data table structure
*/
template<class T>
void Graph<T>::printAnalytics() {
	computeTLevel();
	computeBLevel();
	computeALAP();
	std::cout << "Id\t" << "Data\t" << "t-level\t" << "b-level\t" << "ALAP\t" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << it->second.id << "\t" << it->second.data << "\t" << it->second.tLevel << "\t";
		std::cout << it->second.bLevel << "\t" << it->second.ALAPLevel << std::endl;
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



//BFS : This will return the BFS levels starting from the B node, a index for each level of the BFS with a voector for each level to hold all the indexs for that level
template<class T>
void Graph<T>::JobLevelBFS(){
	jobs.clear();
	int farthest=0;
	std::vector<int> start = findStarts();
	for(auto i=v.begin(); i!=v.end(); ++i){
		v[i->first].distanceBFS = 2147483646;
	}
	for(auto st = start.begin(); st!=start.end(); ++st){
		for(auto i=v.begin(); i!=v.end(); ++i){
			v[i->first].colorBFS = WHITE;
			v[i->first].P=-1;
		}
		auto S=v.end();
		for(auto i=v.begin(); i!=v.end(); ++i){//change this to stwitch back to parameters as indexs
			if(i->first == *st){
				S = i;
				break;
			}
		}
		if(S==v.end()){
			std::string s = "Entered node not valid";
			throw s;
		}

		v[S->first].colorBFS = GREY;
		v[S->first].distanceBFS = 0;

		std::queue<int> q;
		q.push(S->first);
		while(!q.empty()){
			int U = q.front();q.pop();
			for(auto j=v[U].vertices.begin(); j!=v[U].vertices.end(); ++j){
				if(v[*j].colorBFS == WHITE){
					v[*j].colorBFS = GREY;
					if(v[*j].distanceBFS > v[U].distanceBFS+1)
						v[*j].distanceBFS = v[U].distanceBFS+1;
					if(farthest < v[*j].distanceBFS)
						farthest = v[*j].distanceBFS;
					v[*j].P = U;
					q.push(*j);
				}
				v[*j].colorBFS = BLACK;
			}
		}
	}

	for(int i=0; i<=farthest; i++){//Takes all calulated data and saves what nodes were in what level of distance form the starting node and returns them in a map listed above
		jobs.insert(std::pair<int, std::vector<int>>(i, std::vector<int>()));
	}
	for(auto i=v.begin(); i!=v.end(); ++i){
		std::cout<<"Distance: "<<v[i->first].distanceBFS<<" at i->first: "<<i->first<<std::endl;
		jobs[v[i->first].distanceBFS].push_back(i->first);
	}
}


template<class T>
void Graph<T>::driver(int numofCPU){//This will take the new jobs listing and divide it to the number of CPU/Workers we have that the user tell us in the paremeter
	time1=0;
	time2=0;
	computeTLevel();
	for(auto i=v.begin(); i!=v.end(); ++i){//Assume everyhting from begfore was wrong
		v[i->first].done = false;
	}
	JobLevelBFS();
	CPUs.clear();//Assume all old CPU lists are longer valid
	for(int i=1; i<=2; i++){
		CPUs.insert(std::pair<int, std::vector<CPUStruct>>(i,std::vector<CPUStruct>()));// or get rid of this second loine and just make the first into:
		//                               CPUs.insert(std::pair<int, std::vector<CPUStruct>>(i,std::vector<CPUStruct>({CPUStruct()})));
	}
	for(auto i=CPUs.begin(); i!=CPUs.end(); ++i){
		CPUs[i->first].push_back(CPUStruct());
	}
	for(auto i =jobs.begin(); i!=jobs.end(); ++i){
		for(auto j=jobs[i->first].begin(); j!=jobs[i->first].end(); ++j){
				int min = findMinTlvl(jobs[i->first]);//Finds the next node that shound be done in the current level
				int cpu = NextCPU();//Finds the index to the next available CPU
				if(cpu == 1){//if CPU 1 is doing the job
					CPUs[cpu].push_back(CPUStruct(time1, time1+v[min].cost, min));
					time1+=v[min].cost;
				}else if(cpu == 2){//If cpu 2 is doing the job
					CPUs[cpu].push_back(CPUStruct(time2, time2+v[min].cost, min));
					time2+=v[min].cost;
				}else{
					std::cout<<"WARNING REEEEEEE"<<std::endl;
				}
				v[min].done = true;
			}
			if(time1 <= time2){
				time1=time2;
			}else{
				time2=time1;
			}

		}
		for(auto j=CPUs.begin(); j!=CPUs.end(); ++j){//Get rid of the inital s:0 f:0 times
			CPUs[j->first].erase(CPUs[j->first].begin());
		}
		for(auto i=CPUs.begin(); i!=CPUs.end(); ++i){
			std::cout<<"CPU "<<i->first<<" Completed: ";
			for(auto j=CPUs[i->first].begin(); j!=CPUs[i->first].end(); ++j){
				std::cout<<j->IDdone<<" ";
			}
			std::cout<<std::endl;
		}
	}


template<class T>
int Graph<T>::findMinTlvl(std::vector<int> vect){//std::vector<int>::iterator
	if(vect.begin() == vect.end()){
		std::string s = "Nothing vector";
		throw s;
	}
	auto minIndex = vect.end();

	for(auto i=vect.begin(); i!=vect.end(); ++i){
		if(!v[*i].done){
			minIndex = i;
			break;
		}
	}
	if(minIndex == vect.end()){
		std::string s = "Nothing in vector";
		std::cout<<"===================================================================================================================================="<<std::endl;
		throw s;
	}


	for(auto i=vect.begin(); i!=vect.end(); ++i){
		if(v[*minIndex].tLevel > v[*i].tLevel && !v[*i].done){
			minIndex = i;
		}
	}
	//std::cout<<"minIndex: "<<*minIndex<<std::endl;
	return *minIndex;
}

template<class T>
int Graph<T>::NextCPU(){
	int nextOpenCPU = CPUs.begin()->first;
	for(auto j=CPUs.begin(); j!=CPUs.end(); ++j){
		//std::cout<<"	CPUs[nextOpenCPU].back().finish "<<CPUs[nextOpenCPU].back().finish<<" | CPUs[j->first].back().finish "<<CPUs[j->first].back().finish<<std::endl;
		if(CPUs[nextOpenCPU].back().finish > CPUs[j->first].back().finish){
			nextOpenCPU = j->first;
		}
	}
	return nextOpenCPU;
}

template<class T>
void Graph<T>::printAnaCPU(){
	driver(1);
	std::cout << "Id\t" << "Data\t" << "CPU#\t" << "Start\t" << "Finish\t" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	for (auto it = CPUs.begin(); it != CPUs.end(); ++it) {
		for(auto i = CPUs[it->first].begin(); i!=CPUs[it->first].end(); ++i){
			std::cout << i->IDdone << "\t" << v[i->IDdone].data << "\t" << it->first << "\t";
			std::cout << i->start << "\t" << i->finish << std::endl;
		}
	}
}


//Here a below i scurrently broken
//This si the attempt to clean up the edge cases of CPUs having to wait

// template<class T>
// void Graph<T>::driverV2(int numofCPU){//This will take the new jobs listing and divide it to the number of CPU/Workers we have that the user tell us in the paremeter
// 	time1=0;
// 	time2=0;
// 	computeTLevel();
// 	for(auto i=v.begin(); i!=v.end(); ++i){//Assume everyhting from begfore was wrong
// 		v[i->first].done = false;
// 	}
// 	JobLevelBFS();
// 	CPUs.clear();//Assume all old CPU lists are longer valid
// 	for(int i=1; i<=2; i++){
// 		CPUs.insert(std::pair<int, std::vector<CPUStruct>>(i,std::vector<CPUStruct>()));// or get rid of this second loine and just make the first into:
// 		//                               CPUs.insert(std::pair<int, std::vector<CPUStruct>>(i,std::vector<CPUStruct>({CPUStruct()})));
// 	}
// 	for(auto i=CPUs.begin(); i!=CPUs.end(); ++i){
// 		CPUs[i->first].push_back(CPUStruct());
// 	}
//
//
// 	for(int i =0; i<jobs.size()-1; ++i){
// 		for(auto j=jobs[i].begin(); j!=jobs[i].end(); ++j){
// 			for(auto j=jobs[i+1].begin(); j!=jobs[i+1].end(); ++j){
// 				int min = findMinTlvlV2(jobs[i], jobs[i+1]);
// 				int cpu = NextCPU();
// 				if(cpu == 1){//if CPU 1 is doing the job
// 					CPUs[cpu].push_back(CPUStruct(time1, time1+v[min].cost, min));
// 					time1+=v[min].cost;
// 				}else{//If cpu 2 is doing the job
// 					CPUs[cpu].push_back(CPUStruct(time2, time2+v[min].cost, min));
// 					time2+=v[min].cost;
// 				}
// 				v[min].done = true;
// 			}
// 		}
// 		if(time1 <= time2){
// 			time1=time2;
// 		}else{
// 			time2=time1;
// 		}
// 	}
//
//
// 	for(auto j=CPUs.begin(); j!=CPUs.end(); ++j){//Get rid of the inital s:0 f:0 times
// 		CPUs[j->first].erase(CPUs[j->first].begin());
// 	}
// }
//
// 	template<class T>
// 	bool Graph<T>::canBeDone(int index){//Checks to see if a give node is able ot be completed yet
// 		for(auto i=v[index].verticesParent.begin(); i!=v[index].verticesParent.end(); ++i){
// 			if(!i.done){
// 				return false;
// 			}
// 		}
// 		return true;
// 	}
//
//
// 	template<class T>
// 	int Graph<T>::findMinTlvlV2(std::vector<int> vect, std::vector<int> vect2){//std::vector<int>::iterator
// 		if(vect.begin() == vect.end() || vect2.begin() == vect2.end()){
// 			std::string s = "Nothing vector";
// 			throw s;
// 		}
// 		auto minIndex = vect.end();
//
// 		for(auto i=vect.begin(); i!=vect.end(); ++i){
// 			if(!v[*i].done){
// 				minIndex = i;
// 				break;
// 			}
// 		}
// 		if(minIndex == vect.end()){//There is nothing to do lef inside of vect1
// 			minIndex = vect2.end();
// 			for(auto i=vect2.begin(); i!=vect2.end(); ++i){
// 				if(!v[*i].done && canBeDone(*i)){
// 					minIndex = i;
// 					break;
// 				}
// 			}
// 			if(minIndex == vect2.end()){
// 				std::string s = "There were no nodes left to check";
// 				throw s;
// 			}
// 			for(auto i=vect2.begin(); i!=vect2.end(); ++i){
// 				if(v[*minIndex].tLevel > v[*i].tLevel && !v[*i].done && canBeDone(*i)){
// 					minIndex = i;
// 				}
// 			}
// 			return *minIndex;
// 		}
//
//
// 		for(auto i=vect.begin(); i!=vect.end(); ++i){
// 			if(v[*minIndex].tLevel > v[*i].tLevel && !v[*i].done){
// 				minIndex = i;
// 			}
// 		}
// 		//std::cout<<"minIndex: "<<*minIndex<<std::endl;
// 		return *minIndex;
// 	}
//
// 	template<class T>
// 	void Graph<T>::printAnaCPUV2(){
// 		driver(1);
// 		std::cout << "Id\t" << "Data\t" << "CPU#\t" << "Start\t" << "Finish\t" << std::endl;
// 		std::cout << "-----------------------------------------" << std::endl;
// 		for (auto it = CPUs.begin(); it != CPUs.end(); ++it) {
// 			for(auto i = CPUs[it->first].begin(); i!=CPUs[it->first].end(); ++i){
// 				std::cout << i->IDdone << "\t" << v[i->IDdone].data << "\t" << it->first << "\t";
// 				std::cout << i->start << "\t" << i->finish << std::endl;
// 			}
// 		}
// 	}
