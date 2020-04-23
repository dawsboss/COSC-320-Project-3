#include "Graph.h"


int main(){
	Graph<int> t;
	t.addVertex(5,1);
	t.addEdge(5,5);
	t.print();

	std::cout<<std::endl;

	t.addVertex(10,1);
	t.print();

	std::cout<<std::endl;

	t.addVertex(7,1);
	//t.addEdge(7,7);
	t.addEdge(7,5);
	t.addEdge(7,10);
	t.print();

	t.addVertex(11,1);
	t.addEdge(11,10);

	t.addVertex(15,1);
	t.addEdge(7,15);
	t.addEdge(15,1);


	std::vector<int> re= t.findEnd();
	for(auto i=re.begin(); i!=re.end(); ++i){
		std::cout<<*i<<std::endl;
	}

	std::vector<int> r= t.findStarts();
	for(auto i=r.begin(); i!=r.end(); ++i){
		std::cout<<*i<<std::endl;
	}

	std::cout<<std::endl;

	//t.printBfs(7);




	Graph<char> d;
	d.addVertex('a',1);
	d.addVertex('b',1);
	d.addVertex('c',1);
	d.addVertex('d',1);
	d.addVertex('e',2);
	d.addVertex('f',1);
	d.addVertex('g',1);
	d.addVertex('h',1);
	d.addVertex('i',1);
	d.addVertex('j',1);
	d.addVertex('k',1);
	d.addVertex('l',1);

	//not dirrected graph
//a
	d.addEdge('a','e');
	d.addEdge('a','f');
	d.addEdge('e','a');
	d.addEdge('f','a');
//b
	d.addEdge('b','e');
	d.addEdge('b','j');
	d.addEdge('e','b');
	d.addEdge('j','b');
//c
	d.addEdge('c','d');
	d.addEdge('c','g');
	d.addEdge('g','c');
	d.addEdge('d','c');
//d
	d.addEdge('d','c');
	d.addEdge('d','k');
	d.addEdge('c','d');
	d.addEdge('k','d');
//e
	d.addEdge('e','a');
	d.addEdge('e','b');
	d.addEdge('e','f');
	d.addEdge('e','i');
	d.addEdge('i','e');
	d.addEdge('f','e');
	d.addEdge('b','e');
	d.addEdge('a','e');
//f
	d.addEdge('f','a');
	d.addEdge('f','e');
	d.addEdge('f','g');
	d.addEdge('f','i');
	d.addEdge('f','j');
	d.addEdge('a','f');
	d.addEdge('e','f');
	d.addEdge('g','f');
	d.addEdge('i','f');
	d.addEdge('j','f');
//g
	d.addEdge('g','c');
	d.addEdge('g','h');
	d.addEdge('g','f');
	d.addEdge('g','j');
	d.addEdge('c','g');
	d.addEdge('h','g');
	d.addEdge('f','g');
	d.addEdge('j','g');
//h
	d.addEdge('h','g');
	d.addEdge('h','k');
	d.addEdge('g','h');
	d.addEdge('k','h');
//i
	d.addEdge('i','e');
	d.addEdge('i','f');
	d.addEdge('e','i');
	d.addEdge('f','i');
//j
	d.addEdge('j','f');
	d.addEdge('j','g');
	d.addEdge('j','b');
	d.addEdge('j','k');
	d.addEdge('f','j');
	d.addEdge('g','j');
	d.addEdge('b','j');
	d.addEdge('k','j');
//k
	d.addEdge('k','j');
	d.addEdge('k','d');
	d.addEdge('k','h');
	d.addEdge('k','l');
	d.addEdge('d','k');
	d.addEdge('h','k');
	d.addEdge('j','k');
	d.addEdge('l','k');
//l
	d.addEdge('l','k');
	d.addEdge('k','l');

	//d.addVertex('t'); edge case

	d.print();

	std::cout<<std::endl;
	std::cout<<"New stuff"<<std::endl;
	std::cout<<std::endl;

	std::vector<char> reee= d.findEnd();
	for(auto i=reee.begin(); i!=reee.end(); ++i){
		std::cout<<*i<<std::endl;
	}

	std::vector<char> ree= d.findStarts();
	for(auto i=ree.begin(); i!=ree.end(); ++i){
		std::cout<<*i<<std::endl;
	}

	std::cout<<"End"<<std::endl;

	//Graph<int> tester;
	//tester.addData("data.txt");










	return 0;
}
