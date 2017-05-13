#include <map>
#include <set>
#ifndef GRAPH_H
#define GRAPH_H

//----------GraphNode DS-------------
template<typename userClass>
class GraphNode
{
public:
	userClass nodeID;					//Each node ds has an ID of whatever the user class template is defined
	unsigned long pv, dv;			//these variables exisit to support algorithms like dijkstra, prim, kruskal algorithms
	bool known;								//,, ,, ,,
	std::map<userClass, unsigned long> adjacencyList;
													//The ajdacency relation, such that the map holds each node id and the weight between them
													//(GraphNode) -> {Va:weight_a, Vb:weight_b, ...}
	GraphNode(const userClass &ID_arg) { nodeID = ID_arg; pv = 0; dv = -1; known = false; }
													//Construct a node given its ID
	//Class DESTRUCTOR is not defined yet.
};

template<typename userClass>
class Graph
{
	//TODO: define the DESTRUCTOR, Test memory leaks
	std::map<userClass, GraphNode<userClass>*> nodes;
													//A graph keeps track of all of its nodes via a map ds, each key returns a pointer to a graph object in the mem
	unsigned long nodesCount;
													//Holds the number of nodes inside the graph
public:
	Graph() { nodesCount = 0; }
													//Defult constructor
	void addNode(userClass newNodeID);
													//User can add node given only its unique ID
	void addEdge(userClass leftNodeID, userClass rightNodeID,userClass weight, bool directed = false);
													//User can connect two nodes given both of their unique ID, lhs->rhs, Throws exception if one of the nodes does not exisit
													//directed is set to true in case this edge is a directed edge

	unsigned long getNodeCount() { return nodesCount; }
													//interface to count how many nodes created in this graph
	friend class MazeSolver;
													//Maze solver class get to access any of the graph internal members
};
//-----------------------------------

template<typename userClass>
void Graph<userClass>::addNode(userClass  newNodeID)
{
	if (nodes[newNodeID] != 0)
		throw;
		//NODE ALREADY EXISIT

	//DEFINE DESTRUCTOR, WATCH MEMORY LEAKS
	nodes[newNodeID] = new GraphNode<userClass>(newNodeID);
	nodesCount++;
}

/*
If the edge is a directed edge then only LeftNode --w--> RightNode
Otherwise both nodes are connected to each other
*/
template<typename userClass>
void Graph<userClass>::addEdge(userClass  leftNodeID, userClass rightNodeID, userClass weight, bool directed)
{
	GraphNode<userClass> *lhsPtr = nodes[leftNodeID];
	GraphNode<userClass> *rhsPtr = nodes[rightNodeID];
	if (lhsPtr == 0 || rhsPtr == 0)
		throw;
		//ONE OF THE NODES DOES NOT EXISIT, THE METHOD DOES NOT AUTOMATICALLY CREATE NODE IN CASE THEY DONT EXISIT

	lhsPtr->adjacencyList[rightNodeID] = weight;
	if (!directed)
		rhsPtr->adjacencyList[leftNodeID] = weight;
}
#endif
