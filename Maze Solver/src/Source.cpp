#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <ctime>
#include "graph.h"
#include "MazeSolver.h"


int main(int argc, char *argv[])
{
	clock_t begin = clock();
	MazeSolver uut;
	uut.parseFile(argv[1]);
	uut.dijkstra();
	std::cout << "Solving maze\n" ;
	std::ofstream out("ans.txt");
	out << uut.answer();
	out.close();
	clock_t end = clock();
	std::cout <<"Created : "<< uut.getNumNodes()<<" Nodes\n"<< "Time taken to solve Maze is\n"<< double(end - begin) / CLOCKS_PER_SEC<< " Seconds\n";
}
