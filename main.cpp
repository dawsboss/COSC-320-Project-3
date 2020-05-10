#include "Graph.h"


int main(){

std::cout<<std::endl;
std::cout<<"Test1: "<<std::endl;
std::cout<<std::endl;

	Graph<int> i;
	i.addVertex(2, 4);
	i.addVertex(3, 8);
	i.addVertex(5, 30);
	i.addVertex(1, 9);
	i.addVertex(6, 1);
	i.addVertex(7, 2);
	i.addVertex(8,11);
	i.addEdge(7, 8);
	i.addEdge(8, 5);
	i.addEdge(5, 6);
	i.addEdge(2, 3);
	i.addEdge(2, 5);
	i.addEdge(2, 1);
	i.addEdge(5, 3);
	i.addEdge(1, 6);
	i.addEdge(8, 6);

	i.printAnalytics();
	std::cout<<std::endl;
	//i.JobLevelBFS();


	std::cout<<std::endl;
	//i.JobLevelBFS();

	std::cout<<std::endl;

	i.printAnaCPU();



	std::cout<<std::endl;
	std::cout<<"Test2: "<<std::endl;
	std::cout<<std::endl;





	Graph<char> test1;
	test1.addVertex('a', 4);
	test1.addVertex('b', 7);
	test1.addVertex('c', 9);
	test1.addVertex('d', 9);
	test1.addVertex('e', 3);
	test1.addVertex('f', 10);
	test1.addVertex('g', 8);
	test1.addEdge('a', 'c');
	test1.addEdge('b', 'c');
	test1.addEdge('d', 'g');
	test1.addEdge('e', 'g');
	test1.addEdge('e', 'f');
	test1.addEdge('f', 'g');
	test1.addEdge('f', 'c');
	test1.addEdge('b', 'g');
	test1.addEdge('a', 'b');
	test1.addEdge('a', 'f');

	test1.printAnalytics();
	std::cout<<std::endl;
	//i.JobLevelBFS();


	std::cout<<std::endl;
	//i.JobLevelBFS();

	std::cout<<std::endl;

	test1.printAnaCPU();






	std::cout<<std::endl;
	std::cout<<"Test3: "<<std::endl;
	std::cout<<std::endl;





	Graph<std::string> test2;
	test2.addVertex("Foundation", 7);
	test2.addVertex("Walls", 3);
	test2.addVertex("Roof trusses", 1);
	test2.addVertex("Electric", 5);
	test2.addVertex("Interior", 10);
	test2.addVertex("Plumbing", 4);
	test2.addVertex("Driveway", 3);
	test2.addVertex("Clear land", 2);
	test2.addVertex("Permits",1);
	test2.addEdge("Foundation","Walls");
	test2.addEdge("Clear land","Foundation");
	test2.addEdge("Clear land","Driveway");
	test2.addEdge("Walls","Electric");
	test2.addEdge("Walls","Roof trusses");
	test2.addEdge("Walls","Interior");
	test2.addEdge("Walls","Plumbing");
	test2.addEdge("Electric","Plumbing");


	test2.printAnalytics();
	std::cout<<std::endl;
	//i.JobLevelBFS();


	std::cout<<std::endl;
	//i.JobLevelBFS();

	std::cout<<std::endl;

	test2.printAnaCPU();








	return 0;
}
