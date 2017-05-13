# Shortest path finder and maze solver written in `C++`

The code implements the Graph data structure, the ds uses the standared library `Set` to represent the edges [Adjacency relation] with other nodes in the graph.

The code also implements the method `void MazeSolver :: dijkstra()` that implements Dijkstra greedy algorithm.

The code is memory efficient when it comes to solving the maze by making sure that it does not create too much nodes, instead it only create nodes at the corners/end points with the proper weight between nodes.

### Example

Non efficient implementation

![](assets/markdown-img-paste-20170507131249612.png)

Where the **Orange** nodes are all the available nodes on the path, and the **Black** nodes are all the walls

An efficient implementation [Used by the code]

![](assets/markdown-img-paste-20170507133301678.png)

In a map with **1,000,000** white blocks the code only created almost **350,000** node instead of using them all in the graph this also leads to a smaller running time.

## Screenshots

A very big maze with almost **1,000,000** white nodes

![](assets/markdown-img-paste-20170507133646544.png)

The software solved this with only creating **350,000** nodes and in a time less than a second

![](assets/markdown-img-paste-20170507133421894.png)

A maze with **22,000** white nodes

![](assets/markdown-img-paste-20170507133936472.png)

The software solved this with only creating **8,000** nodes and in a time less than **0.02** second

![](assets/markdown-img-paste-2017050713405236.png)


## How to use

First thing you must create a text file representation of the maze, in case you have an image you can use the python script `image2text.py` to convert a PNG maze representation into a text file.

 `python image2text.py maze1`

 where maze1 is the png maze file name

 Once the maze image is converted, a text file `i2t.txt` will be generated, then the maze executable should be called and be given this text file name as an argument

 `./a.out i2t.txt`

 The code will attemp to solve this maze and the answer will be generated in a text file called `ans.txt`. In order to view the result, another script is called to show the image after solving the maze

 `python v.py i2t.txt`

 
