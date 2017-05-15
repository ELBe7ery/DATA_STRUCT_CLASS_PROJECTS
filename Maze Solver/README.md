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
+ You need visual c++ compiler
+ Make sure to include the path of the vc++ compiler in the environmental variables
+ You need Python with PIL installed library [Python 2.7]

Use `compile.bat` to obtain the executable

And then in order to solve any of the given mazes, the python script `image2text.py` needs to be called

`python image2text.py`

Once the script translates the image into a proper text file you can call

 `solve.bat`

 An example solving the 350x400 maze

 ![](assets/how2use.gif)
