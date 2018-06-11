# Minimum Spanning Tree Problem
Problem definition:

Give two programs that implement Kruskal’s and Prim’s algorithm to find minimum spanning tree.

Input:

First line is N, denotes the amount of test case, then there are Ns graph data with an option number (determine whether output the selected edges or not).

Each graph is undirected and connected, it is composed of V (the number of vertices, <= 1000), E (the number of edges, <=10000), then followed by Es edges which are denoted by pair of vertex and weight (e.g., 2  4  10 means an edge connecting vertices 2 and 4, and its weight is 10).

The first data of each graph are vertex number, edge number and option number, respectively. Option number could be 1 or 2, output the selected edge and the sum of all minimum spanning tree’s weight if it is 1, or only the sum if it is 2.

We restrict that selected node of Prim always start from 0, and there is no “tree edge” with same weight.

Output:

If option is 1:

1.    The selected edges which forms the spanning tree. Order is important!

2.    The sum of all edges weight in minimum spanning tree.

3.    Note that the edge should put smaller node first, e.g., if the edge (4, 2) is selected, it should be output by 2 4, not 4 2.

If option is 2:

The sum of all edges weight in minimum spanning tree.

Example:

Input:

2

5 7 1

0 2 1

2 1 6

4 2 7

1 4 2

1 3 5

3 0 3

3 2 4


6 12 2

1 0 5

0 4 1

4 5 10

4 3 4

3 0 9

0 5 2

2 0 8

2 1 3

5 2 11

2 3 6

3 5 7

1 5 12

Output: (Kruskal’s algorithm)

0 2

1 4

0 3

1 3

11

15

Output: (Prim’s algorithm)

0 2

0 3

1 3

1 4

11

15
