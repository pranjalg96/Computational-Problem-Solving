/* 	adjacency list representation of a graph
*/
#include <stdio.h>
#include <stdlib.h> // has the malloc prototype
#define NODES 5

typedef struct node {
	int outNodeIndex;
	int edgeWeight;
	struct node * next;
} Node;

typedef struct graph{
	int numNodes;
// for the lists, use a pointer to a pointer (will be a pointer to an array)
	struct node** alists; 
} Graph;

Graph* InitializeGraph(int myNodes);
Node* InitializeNode(int myoutNodeIndex, int myedgeWeight);
int addEdge(Graph* mygraph, int node1, int node2, int myedgeweight);
void printGraph(Graph* mygraph);
int deleteGraph(Graph* mygraph);

int main()
{
	Graph* mygraph = InitializeGraph(NODES);
	addEdge(mygraph,0, 3, 9);
	addEdge(mygraph,2, 0, 5);
	addEdge(mygraph,4, 3, 12);
	addEdge(mygraph,3, 2, 3);
	addEdge(mygraph,2, 4, 7);
	printGraph(mygraph);

	deleteGraph(mygraph);	
}

Graph* InitializeGraph(int myNodes)
{
	Graph* mygraph = malloc(sizeof(Graph));		// COMPLETE
	mygraph->numNodes = myNodes;						// COMPLETE
	// sets up the space for the array of nodes
	mygraph->alists = malloc(myNodes * sizeof(Node*));
	for (int i=0; i<myNodes; i++)
	{
		mygraph->alists[i] = NULL;				// COMPLETE
	}
	return mygraph ;									// COMPLETE
}

Node* InitializeNode(int myoutNodeIndex, int myedgeWeight)
{
	Node* newnode = malloc(sizeof(Node));			// COMPLETE
	newnode->outNodeIndex = myoutNodeIndex;					// COMPLETE
	newnode->edgeWeight = myedgeWeight;					// COMPLETE
	newnode->next = NULL;							// COMPLETE
	return newnode;									// COMPLETE
}


int addEdge(Graph* mygraph, int node1, int node2, int myedgeweight)
{
	Node* newnode = InitializeNode(node2, myedgeweight);		// COMPLETE
	newnode->next = mygraph->alists[node1];
	mygraph->alists[node1] = newnode;			// COMPLETE
	return 0;
}

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
			printf("%d (%d)  ", temp->outNodeIndex, temp->edgeWeight);			// COMPLETE
			temp = temp->next;						// COMPLETE
		}
		printf("\n");
	}
}

int deleteGraph(Graph* mygraph)
{
	// first, loop over all entries and free the space for each linked list
	for (int i=0; i<mygraph->numNodes; i++)
	{
		Node* temp = mygraph->alists[i];
		Node * tempnext; 
		while (temp != NULL)
		{
			tempnext = temp->next;						// COMPLETE
			free(temp); 						// COMPLETE
			temp = tempnext;							// COMPLETE
		}
	}
	// then, free the space for the Graph
	free(mygraph);								// COMPLETE
}
		