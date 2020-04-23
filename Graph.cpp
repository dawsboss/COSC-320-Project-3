//Defualt constructor
template<class T>
Graph<T>::Graph(){

}

//Finds all vertices that are starting points/dont have anything pointing to it
template<class T>
std::vector<T> Graph<T>::findStarts(){
	std::vector<T> rtn;
	for( auto i=v.begin(); i!=v.end(); ++i){
		if(i->second.verticesParent.empty()){
			rtn.push_back(i->first);
			std::cout<<"start: "<<i->first<<std::endl;
		}
	}
	return rtn;
}

//Finds the end of the jobs/where to stop
template<class T>
std::vector<T> Graph<T>::findEnd(){
	std::vector<T> rtn;
	for( auto i=v.begin(); i!=v.end(); ++i){
		if(i->second.vertices.empty()){
			rtn.push_back(i->first);
			std::cout<<"end: "<<i->first<<std::endl;
		}
	}
	return rtn;
}

//addVertex : adds a new vertex to the map - starts with no edges
template<class T>
void Graph<T>::addVertex(T newData, double price){
		v.insert(std::make_pair(ID, VertexStuff(newData, price, ID)));
		ID++;
		// vertices.insert(std::make_pair(ID, std::vector<int>()));
		// verticesParent.insert(std::make_pair(ID++, std::vector<int>));
}

//addEdge : This will give the parent node a edge to the child node
template<class T>
void Graph<T>::addEdge(T Parent, T child){
	int p=-1, c=-1;
	bool haveP = false, haveC = true;
	for(auto i=v.begin(); i!=v.end(); ++i){
		if(v[i->first].data == Parent){
			p = i->first;
			haveP = true;
		}
		if(v[i->first].data == child){
			c = i->first;
			haveC = true;
		}
		if(haveP && haveC){
			v[p].vertices.push_back(c);
			v[c].verticesParent.push_back(p);
			return;
		}
	}

		std::cout<<"Couldn't add edge, parent or child invalid"<<std::endl;
		return;








	// if(vertices.find(Parent) != vertices.end()){ //if there is an element to point from
	// 	if(vertices.find(child) != vertices.end()){ //if there is an element to point too
	// 		bool inAlready = false;
	// 		for(auto j=vertices[Parent].begin(); j!=vertices[Parent].end(); ++j){
	// 			//std::cout<<*j<<" ";
	// 			if((*j).data==child){
	// 				//std::cout<<" REE ";
	// 				inAlready=true;
	// 				break;
	// 			}
	// 		}
	// 		if(!inAlready){
	// 			std::cout<<Parent<<" points to "<<child<<std::endl;
	// 			vertices[Parent].push_back(VertexStuff(child, price));
	// 			std::cout<<child<<" is pointed to by "<<Parent<<std::endl;
	// 			verticesParent[child].push_back(Parent);
	// 		}else{
	// 			std::cout<<"Edge already included!"<<std::endl;
	// 		}
	// 	}else{
	// 			std::cout<<"There is no "<<child<<" to point too!"<<std::endl;
	// 	}
	// }else{
	// 	std::cout<<"There is no "<<Parent<<" to point from!"<<std::endl;
	// }

}

//print : prints out all verticies and where they point
template<class T>
void Graph<T>::print(){
	for(auto i=v.begin(); i!=v.end(); ++i){
		std::cout<<"Vector: "<<v[i->first].data<<" points to: ";
		for(auto j=v[i->first].vertices.begin(); j!=v[i->first].vertices.end(); ++j){
			std::cout<<v[*j].data<<" cost: "<<v[*j].cost<<" ID: "<<i->first<<" | ";
		}
		std::cout<<std::endl;
	}

	std::cout<<std::endl;
	std::cout<<"parents: "<<std::endl;
	std::cout<<std::endl;

	for(auto i=v.begin(); i!=v.end(); ++i){
		std::cout<<"Vector: "<<v[i->first].data<<" is pointed to by: ";
		for(auto j=v[i->first].verticesParent.begin(); j!=v[i->first].verticesParent.end(); ++j){
			std::cout<<v[*j].data<<"'s' cost: "<<v[*j].cost<<" ID: "<<i->first<<" | ";
		}
		std::cout<<std::endl;
	}


	// for( auto i=vertices.begin(); i!=vertices.end(); ++i){
	// 	std::cout<<"Vector: "<<i->first<<" | Point to: ";
	//
	// 		for(auto j=i->second.begin(); j!=i->second.end(); ++j){
	// 			std::cout<<(*j).data<<"'s' cost: "<<(*j).cost<<" | ";
	// 		}
	// 		std::cout<<std::endl;
	// }
	//
	// std::cout<<std::endl
	// std::cout<<"parents: "<<std::endl;
	// std::cout<<std::endl
	//
	// for( auto i=verticesParent.begin(); i!=verticesParent.end(); ++i){
	// 	std::cout<<"Vector: "<<i->first<<" | Is pointed to by: ";
	//
	// 		for(auto j=i->second.begin(); j!=i->second.end(); ++j){
	// 			std::cout<<(*j)<<" | ";
	// 		}
	// 		std::cout<<std::endl;
	// }
}


















//takes in file name and adds all the data from the file into the map
// template<class T>
// void Graph<T>::addData(std::string s){
// 	std::fstream readIn;
// 	std::string holder;
//
// //Catch if the string was given bad
// 	try{
// 		readIn.open(s);
// 		if(!readIn.is_open()){
// 			std::cout<<"File couldn't open/doesn't exist! \n";
// 			return;
// 		}
// 	}catch(...){
// 		//errors out if we have nothing to open
// 		std::cout<<"File couldn't open/doesn't exist! \n";
// 		return;
// 	}
//
// //The readIn is open and good
// 	for(int i=0; readIn.peek() != '-'; i++){//Reads in the vertices
// 		readIn >> holder;
// 		addVertex(holder);
// 	}
//
// 	readIn.ignore(5,'\n');//Get out of vertices section
//
// 	T parent;
// 	T child;
// 	int cost;
// 	while(readIn >> holder){//Runs through edge stuff
// 		parent = holder[1];
// 		child = holder[3];
// 		cost = holder[5];
// 		// for(int i=0; i<holder.length(); i++){
// 		// 	if(holder[i]=='('||holder[i]==','||holder[i]==')'||holder[i]==' '){
// 		// 		continue;
// 		// 	}
// 		// 	parent=child;
// 		// 	child=holder[i];
// 		// }
// 		addEdge(parent, child, cost);
// 	}
// }



//gamer
