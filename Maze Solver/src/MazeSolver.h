#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include "graph.h"
class MazeSolver
{
private:
	Graph<unsigned long> g;								//Graph ds, its a specific type of the graph which is an unsigned long graph where the ID are unsigned 64bit numbers
	unsigned long startID, endID;					//Start node[Maze entrance] and end node[maze exit]
public:
	void parseFile(std::string fileName);	//Interface to convert a txt file encoded maze into a connected graph
	MazeSolver() { startID = -1; endID = -1; }
																				//Default constructor
	void dijkstra();											//Implements dijkstra shortest path algorithm

	std::string answer();									//Returns the path from the starting node till the end node
	unsigned long getNumNodes() { return g.getNodeCount(); }
																				//Interface to get how many nodes created by the parseFile method

	struct cmp														//Functor used to compare the set of pairs by distance from start node
	{
		bool operator() (const std::pair<unsigned long, unsigned long> &lhs, const std::pair<unsigned long, unsigned long> &rhs) const
		{
			return lhs.second < rhs.second;
		}
	};
};

void MazeSolver::parseFile(std::string fileName)
{
	std::ifstream in(fileName);
	std::cin.rdbuf(in.rdbuf());			//for debugging only, can be removed
	std::string upperLine, currentLine, lowerLine;
	std::map<unsigned int, unsigned int> depthBackup;
	unsigned int lineSize = 0;
	unsigned int currentY = 0;
	upperLine = "";
	std::getline(in, currentLine);
	lineSize = currentLine.length();
	unsigned long leftNodeID;
	unsigned long w;
	bool leftWallRightRoad, rightWallLeftRoad, downRoadUpWall, upRoadDownWall, allRoads;
	unsigned long id;

	while (std::getline(in, lowerLine))
	{
		leftNodeID = -1;
		w = 0;
		for (unsigned int i = 0; i < lineSize; i++)
		{
			id = currentY*lineSize + i;
			if (currentLine[i] != ' ')
			{
				leftNodeID = -1;
				depthBackup.erase(i);
			}
			else if (i == 0 || currentY == 0 || i == lineSize - 1)
			{
				if (i == 0)
					startID = id;
				else if (i == lineSize - 1)
					endID = id;

				g.addNode(id);
				if (leftNodeID != -1)
					g.addEdge(id, leftNodeID, id - leftNodeID);
				leftNodeID = id;

			}
			else if (i > 0 && i < lineSize - 1 && currentY>0)
			{
				leftWallRightRoad = (currentLine[i - 1] != ' ' && currentLine[i + 1] == ' ');
				rightWallLeftRoad = (currentLine[i - 1] == ' ' && currentLine[i + 1] != ' ');
				downRoadUpWall = (lowerLine[i] == ' ' && upperLine[i] != ' ');
				upRoadDownWall = (lowerLine[i] != ' ' && upperLine[i] == ' ');
				allRoads = lowerLine[i] == ' ' && upperLine[i] == ' ' &&currentLine[i - 1] == ' ' && currentLine[i + 1] == ' ';
				//NEW
				if (leftWallRightRoad)
				{
					g.addNode(id);
					leftNodeID = id;
					w = depthBackup[i];
					if (lowerLine[i] == ' '&&upperLine[i] == ' ')
					{
						depthBackup[i] = id;
						g.addEdge(id, w, currentY - (w / lineSize));
					}

				}
				else if (rightWallLeftRoad || allRoads)
				{
					g.addNode(id);
					g.addEdge(id, leftNodeID, id - leftNodeID);
					leftNodeID = id;
					w = depthBackup[i];
					if (lowerLine[i] == ' '&&upperLine[i] == ' ')
					{
						depthBackup[i] = id;
						g.addEdge(id, w, currentY - (w / lineSize));
					}
				}
				if (downRoadUpWall)
				{
					if (leftNodeID != id)
					{
						g.addNode(id);
						if (leftNodeID != -1)
							g.addEdge(id, leftNodeID, id - leftNodeID);

						leftNodeID = id;
					}
					depthBackup[i] = id;
					leftNodeID = id;
				}
				else if (upRoadDownWall)
				{
					if (leftNodeID != id)
					{
						g.addNode(id);
						if (leftNodeID != -1)
							g.addEdge(id, leftNodeID, id - leftNodeID);
						leftNodeID = id;
					}
					w = depthBackup[i];
					if (w != 0)
						g.addEdge(id, w, currentY - (w / lineSize));
				}
			}
		}
		currentY++;
		upperLine = currentLine;
		currentLine = lowerLine;
	}
	upperLine = currentLine;
	currentLine = lowerLine;
	leftNodeID = -1;
	//Ignores the final line, the current maze generator produces a frame, i might consider this later
	in.close();
}



void MazeSolver::dijkstra()
{
	std::multiset<std::pair<unsigned long, unsigned long>, cmp> semiHeap;

	std::map<unsigned long, GraphNode<unsigned long>*>::iterator it;
	std::map<unsigned long, unsigned long>::iterator it1;
	GraphNode<unsigned long> *selectedNode = g.nodes[startID];
	int soFar = 0;
	int dbgVar = 0;		//for debugging only, can be removed
	selectedNode->pv = 0;
	selectedNode->dv = 0;
	selectedNode->known = true;
	for (it = g.nodes.begin(); it != g.nodes.end(); it++)
	{
		semiHeap.insert(std::make_pair(it->second->nodeID, it->second->dv));
	}
	semiHeap.erase(std::make_pair(selectedNode->nodeID, selectedNode->dv));
	while (semiHeap.size() != 0)
	{
		for (it1 = selectedNode->adjacencyList.begin(); it1 != selectedNode->adjacencyList.end(); it1++)
		{
			unsigned long adjNodeId = it1->first;
			unsigned long adjNodeWeight = it1->second;
			GraphNode<unsigned long> *adjNodePtr = g.nodes[adjNodeId];
			if(adjNodeId==50)
				adjNodeId=50;
			if (((adjNodePtr->dv > (soFar + adjNodeWeight)) || adjNodePtr->dv == -1) && adjNodePtr->known == false)
			{
				unsigned long oldDv = adjNodePtr->dv;
				adjNodePtr->dv = soFar + adjNodeWeight;
				adjNodePtr->pv = selectedNode->nodeID;
				semiHeap.erase(semiHeap.find(std::make_pair(adjNodePtr->nodeID, oldDv)));
				semiHeap.insert(std::make_pair(adjNodePtr->nodeID, adjNodePtr->dv));
			}
		}
		selectedNode = g.nodes[(*semiHeap.begin()).first];
		if (selectedNode->nodeID == 50)
			semiHeap.erase(semiHeap.begin());
		selectedNode->known = true;

		dbgVar++;
		semiHeap.erase(semiHeap.begin());
		soFar = selectedNode->dv;
	}
	dbgVar = dbgVar;	//Dummy assignment, can be ignored/removed just made for debugging
}

std::string MazeSolver::answer()
{
	unsigned long path = endID;
	unsigned long debugPast;
	std::string ret = std::to_string(endID) + " ";
	while (path != startID)
	{
		if (path == 0)
			throw;
			//Maze is represented by a non connected graph, throw exception
		debugPast = path;
		path = g.nodes[path]->pv;
		ret += std::to_string(path) + " ";
	}
	return ret;
}
#endif
