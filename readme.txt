/-------------------------------------------------------------------------------\
|                       Network flow project from Jungang Wang                  |
|             Topic: Program for single-duty crew scheduling problem            |
|                                             2020.04.27                        |
\-------------------------------------------------------------------------------/


-----------------------------------------------------------------------------------
Background
-----------------------------------------------------------------------------------
This program aims at solving signal-duty crew scheduling problem. 

Basic definition of the problem is same as question 4.13 on book, while
in this program, you can customize the time period and costs. 

The program resolves the problem by formulate it into a shortest path 
problem, and resolve it with Dijkstra algorithm. 


-----------------------------------------------------------------------------------
User guide
-----------------------------------------------------------------------------------
Change the file name of "schedule_problem" into "schedule_problem.exe"
and open it, the program would first automatically output the answer of the 
question on book. Then you can follow the guide printed on screen to input 
your custom data for a question. 

Don't worry for typo, you would get notice if any data is illegal. But be 
aware that the sum of all drivers' cost shouldn't be larger than 2^31-2, 
otherwise the program may crash. It's acceptable since nobody on earth 
has that much money. (lol)


-----------------------------------------------------------------------------------
Code structure
-----------------------------------------------------------------------------------
The data structure and algorithm of network is defined distinctly, which 
makes them reusable for other questions. Below is brief introduce to soure 
code files.

graph_data.h

    This file implements data structure for a graph. Realization is stored in 
    graph_data.cpp and Dij.cpp

    class GraphNode
        GraphNode is basic component of a graph. Each GraphNode object 
        contains 2 data: unique key value and an adjacency list.

    class Graph
        The graph is implemented by class Graph, which is distinct from 
        problem itself. It's composed by GraphNode, and contains an hash 
        map for searching a specific GraphNode object by its key value. Dij 
        algorithm is also implemented as a member function of the class.

schedule_problem.h
    
    This file implements the problem. Realization is stored in 
    schedule_problem.cpp
	
test_main.cpp

    Entrance of the program.
	
-----------------------------------------------------------------------------------
Algorithm design
-----------------------------------------------------------------------------------
Dijkstra algorithm is implemented for solving the problem. The algorithm is 
implemented in a sliently different way in order to save time and space.

i) Instead of 2 lists of nodes (temporarily labeled & permanently labeled), 
   2 hash map is allocated for storing the nodes. One for the min cost, the 
   other one for their predecessors. This is due to the defined data stucture.
   Since the key value of a node can be customized, it's better to use hash 
   map to have O(1) complexicity on search of any node.

ii) A min heap is used to quickly sort the nodes in ascending order of their 
    costs.

For detail of realization, you can read the souce code.
