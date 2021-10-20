// Bellman-Ford using Adjacency list
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NODES 5
#define INF 10000

/*
ASSUMPTIONS:

1. Number of nodes is known.
2. Declared an array of objects for the bellman-ford nodes. 
3. Adjacency list using pointer of pointer. 
4. Max distance between any two nodes will not exceed INF
5. Source node is excluded from nodes "reachable" from source node
*/

// Structure for storing distance and predecessor fields of each node. Used in Bellman-Form algorithm
struct bellman_node 
{
	int d; // distance field of node
	int p; // predecessor
};

// Structure for every node in the adjacency list.
typedef struct node {
	int outNodeIndex;
	int edgeWeight;
	struct node * next;
} Node;

// Structure for Graph in adjacency list
typedef struct graph{

	int numNodes;
	struct node** alists; // Basically, this is the adjacency list. Number of nodes connect to a particular node can be variable.

} Graph;

// Adjacency list related functions
Graph* InitializeGraph(int myNodes); 
void MakeConnections(Graph * mygraph);
Node* InitializeNode(int myoutNodeIndex, int myedgeWeight);
int addEdge(Graph* mygraph, int node1, int node2, int myedgeweight);
int getEdgeweight(Graph * mygraph, int node1, int node2);
void printGraph(Graph* mygraph);
int deleteGraph(Graph* mygraph);


// Bellman-Ford related functions
void initialize_nodes_bellman(struct bellman_node graph_nodes[], int source);
void display_nodes_bellman(struct bellman_node graph_nodes[]);
int relax(struct bellman_node graph_nodes[], Graph * mygraph, int x, int y);
int display_path_bellman(struct bellman_node graph_nodes[], int node);
void Bellman_Ford(struct bellman_node graph_nodes[], Graph * mygraph);

// stack-related functions (to print from source -> target)
int Push(int stack[], int * size_ptr, int val);
int Pop(int stack[], int * size_ptr);
int PrintPath(int stack[], int * size_ptr, int target);


int main()
{

	Graph* mygraph = InitializeGraph(NODES);

	// Make weighted connections in the graph
	MakeConnections(mygraph);

	// Display the graph as an adjacency list
	printGraph(mygraph);

	// Nodes needed for the bellman algorithm
	struct bellman_node graph_nodes[NODES];
			  
	// declare and initialize source node
	int source = 0;

	// initialize the node fields
	initialize_nodes_bellman(graph_nodes, source);

	// run the bellman ford
	Bellman_Ford(graph_nodes, mygraph);

	// Display updated node fields after running Bellman-ford
	display_nodes_bellman(graph_nodes);

	// Free memory used in the adjacency list
	deleteGraph(mygraph);

	return 0;
}

// Adjacency list related function definitions
/*
Function to Initialize Graph with number of nodes. Adjacency list elements should point to NULL initially
input: 
myNodes - number of nodes in the graph

returns:
mygraph - Pointer to Graph structure
*/
Graph* InitializeGraph(int myNodes)
{
	Graph* mygraph = malloc(sizeof(Graph));
	mygraph->numNodes = myNodes;						
	// sets up the space for the array of nodes
	mygraph->alists = malloc(myNodes * sizeof(Node*));
	for (int i=0; i<myNodes; i++)
	{
		mygraph->alists[i] = NULL;				
	}
	return mygraph ;								
}

/*
Function to make weighted connections in the graph between nodes
input: 
mygraph - Pointer to Graph structure

returns:
void
*/
void MakeConnections(Graph * mygraph)
{
	// Example undirected graph
	addEdge(mygraph, 0, 1, 3);
	addEdge(mygraph, 1, 0, 3);
	addEdge(mygraph, 1, 2, 8);
	addEdge(mygraph, 2, 1, 8);
	addEdge(mygraph, 0, 2, 7);
	addEdge(mygraph, 2, 0, 7);
	addEdge(mygraph, 3, 4, 2);
	addEdge(mygraph, 4, 3, 2);
}

/*
Function to create and initialize individual nodes in the adjacency list
input: 
myoutNodeIndex - Target node index
edgeWeight - weight of the edge

returns:
newnode - Pointer to the newly created node
*/
Node* InitializeNode(int myoutNodeIndex, int myedgeWeight)
{
	Node* newnode = malloc(sizeof(Node));
	newnode->outNodeIndex = myoutNodeIndex;
	newnode->edgeWeight = myedgeWeight;	
	newnode->next = NULL;
	return newnode;
}

/*
Function to make single weighted connections between two nodes (Directed edges)
input: 
mygraph - Pointer to Graph structure
node1 - Source node
node2 - Target node
myedgeweight - Weight of the edge

returns:
int
*/
int addEdge(Graph* mygraph, int node1, int node2, int myedgeweight)
{
	Node* newnode = InitializeNode(node2, myedgeweight);		
	newnode->next = mygraph->alists[node1];
	mygraph->alists[node1] = newnode;			
	return 0;
}

/*
Function to return edge-weight between 2 nodes. 
input: 
mygraph - Pointer to Graph structure
node1 - Source node
node2 - Target node

returns:
weight - Edge-weight between the two nodes. Returns 0 if no edge between them
*/
int getEdgeweight(Graph * mygraph, int node1, int node2)
{
	int weight = 0;

	Node * temp = mygraph->alists[node1];

	while(temp != NULL)
	{
		if (temp->outNodeIndex == node2)
		{
			weight = temp->edgeWeight;
			break;
		}
		temp = temp->next;

	}

	return weight;
}

/*
Function to print the adjacency list
input: 
mygraph - Pointer to Graph structure

returns:
void
*/
void printGraph(Graph* mygraph)
{
	// print out for each vertex the list of vertices with an incoming edge, 
	//   along with their edge weights in ()
	for (int i=0; i<mygraph->numNodes; i++)
	{
		Node* temp = mygraph->alists[i];
		printf("There are edges from node %d to: ",i);
		while(temp!=NULL)
		{
			printf("%d (%d)  ", temp->outNodeIndex, temp->edgeWeight);			
			temp = temp->next;						
		}
		printf("\n");
	}
}

/*
Function to delete the Graph structure
input: 
mygraph - Pointer to Graph structure

returns:
int
*/
int deleteGraph(Graph* mygraph)
{
	// first, loop over all entries and free the space for each linked list
	for (int i=0; i<mygraph->numNodes; i++)
	{
		Node* temp = mygraph->alists[i];
		Node * tempnext; 
		while (temp != NULL)
		{
			tempnext = temp->next;						
			free(temp); 						
			temp = tempnext;							
		}
	}
	// then, free the space for the Graph
	free(mygraph);								
}

// Bellman function definitions
/*
Function to initialize bellman-node fields. Sets the distance of source node as 0 and its predecessor to -1.
input: 
graph_nodes - Array of bellman-node objects
source - Source node

returns:
void
*/
void initialize_nodes_bellman(struct bellman_node graph_nodes[], int source)
{
	for(int i = 0; i < NODES; i++)
	{
		graph_nodes[i].d = INF;
		graph_nodes[i].p = -1;
	}

	graph_nodes[source].d = 0;
}

/*
Function to display bellman-node fields
input: 
graph_nodes - Array of bellman-node objects

returns:
void
*/
void display_nodes_bellman(struct bellman_node graph_nodes[])
{
	printf("\nNode properties: \n");
	for(int i = 0; i < NODES; i++)
	{
		printf("\nNode %d: \n", i);
		printf("d -> %d\n", graph_nodes[i].d);
		printf("p -> %d\n", graph_nodes[i].p);
	}
}

/*
Function to Perform relax operation. If distance to node y from source is closer through x, then set that as distance of y. Set predecessor of y as x
input: 
graph_nodes - Array of bellman-node objects
x - source node
y - target node

returns:
1 if the operation was performed, 0 otherwise
*/
int relax(struct bellman_node graph_nodes[], Graph * mygraph, int x, int y)
{
	if (graph_nodes[x].d + getEdgeweight(mygraph, x, y) < graph_nodes[y].d)
	{
		graph_nodes[y].d = graph_nodes[x].d + getEdgeweight(mygraph, x, y);
		graph_nodes[y].p = x;

		return 1;
	}
	else
	{
		return 0;
	}
}


/*
Function to display the path from source to target node
input:
graph_nodes - Array of bellman-node objects
u - target node

returns:
path_len - Length of path between source and node u
*/
int display_path_bellman(struct bellman_node graph_nodes[], int u)
{
	int target = u;
	int stack[NODES], size=0;

	int path_len = -1; 
	
	while(u != -1)
	{
		Push(stack, &size, u);
		u = graph_nodes[u].p;

		path_len++;
	}

	printf("Path to node: %d\n", target);
	PrintPath(stack, &size, target);

	return path_len;
}


/*
Function to perform the Bellman-Form Algorithm
input:
graph_nodes - Array of bellman-node objects
mygraph - Pointer to graph structure

returns:
void
*/
void Bellman_Ford(struct bellman_node graph_nodes[], Graph * mygraph)
{
	int flag = 1;
	int iter = 0;

	while(flag)
	{
		iter++;
		flag = 0;

		for(int node1 = 0; node1 < mygraph->numNodes; node1++)
		{
			Node * curr_node = mygraph->alists[node1];

			while(curr_node != NULL)
			{
				int node2 = curr_node->outNodeIndex;

				if(relax(graph_nodes, mygraph, node1, node2) || relax(graph_nodes, mygraph, node2, node1))
				{
					flag = 1;
				}

				curr_node = curr_node->next;
			}
		}
	}

	printf("\nNumber of iterations: %d\n", iter);

	int reachable_nodes = 0; // Number of reachable nodes from source
	double avg_transform_len = 0.0; // Avg. transformation length

	for(int u = 0; u < NODES; u++)
	{
		int pred = graph_nodes[u].p; // predecessor node
		int dist = graph_nodes[u].d; // distance to source node
 
		if (pred == -1 && dist > 0) // If node is not reachable (make sure it is not the source)
		{
			printf("Path from source node to node %d doesn't exist! \n", u);
		}
		else
		{
			int path_len = display_path_bellman(graph_nodes, u);

			if (path_len != 0)
			{
				reachable_nodes++;
				avg_transform_len += path_len;
			}
		}
	}

	avg_transform_len /= reachable_nodes;

	printf("\n\nTotal number of reachable words from source: %d", reachable_nodes);
	printf("\nAverage number of transformations needed to reach reachable words: %f\n\n", avg_transform_len);
}


/*
Function to push an element onto the stack
inputs:
stack - The stack data structure, implemented as an array
size_ptr - int pointer to a int size variable
val - int value to be pushed into the stack

returns:
0 if successful, 1 if error
*/

int Push(int stack[], int * size_ptr, int val)
{
	// int size_val = *size_ptr;

	if(*size_ptr < NODES ) //COMPLETE LOGIC
	{
		stack[*size_ptr] = val;
		*size_ptr = *size_ptr + 1;// COMPLETE LOGIC

		return 0;
	}
	else 
	{
		printf("Insertion error; stack is full\n");
		return 1;
	}
}

/*
Function to delete an element from the stack
inputs:
stack - The stack data structure, implemented as an array
size_ptr - int pointer to a int size variable

returns:
returnValue - value at the top of the stack, -1 if error
*/
int Pop(int stack[], int * size_ptr)
{
	int returnValue;
	
	if(*size_ptr > 0) 
	{	
		*size_ptr = *size_ptr - 1;
		returnValue = stack[*size_ptr];	
		printf("removing %d from stack\n", returnValue);
	}
	else
	{
		printf("Deletion error; stack is empty\n");
		returnValue = -1;
	}	
	return returnValue;
}

/*
Function to print out source->target path 
inputs:
stack - The stack data structure, implemented as an array
size_ptr - int pointer to a int size variable
target - target node

returns:
0 if successful, -1 if error
*/
int PrintPath(int stack[], int * size_ptr, int target)
{
	if(*size_ptr>0)
	{
		for(int j = *size_ptr - 1; j >= 0; j--)	// COMPLETE
		{
			if (stack[j] != target)
			{
				printf("%d -> ",stack[j]);
			}
			else
			{
				printf("%d ", stack[j]);
			}
		}
		printf("\n");
		return 0;
	}
	else
	{
		printf("Printing error; stack is empty\n");
		return -1;
	}
}