/* 	adjacency list representation of a graph
*/
#include <stdio.h>
#include <stdlib.h> // has the malloc prototype
#include <string.h>
#define NODES 500
#define WORDSIZE 4

typedef struct node {
	int outNodeIndex;
	struct node * next;
} Node;

typedef struct graph{
	int numNodes;
// for the lists, use a pointer to a pointer (will be a pointer to an array)
	struct node** alists; 
} Graph;

Graph* InitializeGraph(int myNodes);
Node* InitializeNode(int myoutNodeIndex);
int addEdge(Graph* mygraph, int node1, int node2);
void printGraph(Graph* mygraph);
int deleteGraph(Graph* mygraph);

int main(int argc, char *argv[])
{
	FILE* fp = fopen("wordlist.txt","r"); //Open the file
	
	// Make sure that the file opens
	if (fp == NULL)
	{
		printf("Error while opening the word file\n");
	}
	
	char wordlist[NODES][WORDSIZE]; // 2d array that contains the words
	char word[WORDSIZE] = "";
	
	for (int i=0;i<NODES;i++)
	{
		fscanf(fp,"%s", word); //scan the word line by line
		strcpy(wordlist[i],word);//store the word into the array
	}
	
	//print the list of words
	/*
	for (int j=0;j<NODES;j++)
	{
		for (int k = 0;k<WORDSIZE;k++)
		{
			printf("%c",wordlist[j][k]);
		}
		printf("\n");
	}
	*/
	
	fclose(fp); //close the file to free memory
	
	Graph* mygraph = InitializeGraph(NODES); //initialize the graph
	
	int source = atoi(argv[1]); // source node/word (0<= source <= 499)
	int destination = atoi(argv[2]); //destination node/word (0<= destination <=499) (destination != source)
	char *option = argv[3]; // swap transformation option
	
	for (int i=0;i<NODES;i++)
	{
		for (int j=0;j<NODES;j++)
		{
			if (j != i)
			{
				int counter = 0;
				int identical_index[WORDSIZE] = {5,5,5,5};
				
				for (int k=0;k<WORDSIZE;k++)
				{
					if (wordlist[i][k] == wordlist[j][k]) // Compare each letter of word i and word j
					{
						counter = counter + 1;
						identical_index[k] = k;
					}
				}
				if (counter == WORDSIZE-1) // if 3 identical letters
				{
					addEdge(mygraph,i,j); // Create edge between word i and word j
					addEdge(mygraph,j,i); // symmetrical graph
				}
				if (argc>=4 && option[0]=='s') // if swap transformation is wanted
				{
					int swap = 0;
					if (counter == WORDSIZE-2) // if 2 identical letters
					{
						for (int k=0;k<WORDSIZE-1;k++)
						{
							if ((identical_index[k]==5) && (identical_index[k+1]==5) && (wordlist[i][k] == wordlist[j][k+1]) && (wordlist[i][k+1] == wordlist[j][k])) //Compare 2 (different) adjacent letters
							{
								swap = swap + 1;
							}
						}
						if (swap > 0) //if 2 identical letters and swap is possible
						{
							addEdge(mygraph,i,j); // Create edge between word i and word j
							addEdge(mygraph,j,i); // symmetrical graph
						}
					}
				}
			}
		}
	}
	
	
	printGraph(mygraph); // print the graph

	deleteGraph(mygraph); // delete the graph to free memory
	
	return 0;
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

Node* InitializeNode(int myoutNodeIndex)
{
	Node* newnode = malloc(sizeof(Node*));			// COMPLETE
	newnode->outNodeIndex = myoutNodeIndex;					// COMPLETE
	newnode->next = NULL;							// COMPLETE
	return newnode;									// COMPLETE
}


int addEdge(Graph* mygraph, int node1, int node2)
{
	Node* newnode = InitializeNode(node2);		// COMPLETE
	newnode->next = mygraph->alists[node1];
	mygraph->alists[node1] =  newnode;			// COMPLETE
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
			printf("%d  ", temp->outNodeIndex);			// COMPLETE
			temp =   temp->next  ;						// COMPLETE
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
			free(  temp   ); 						// COMPLETE
			temp=  tempnext;							// COMPLETE
		}
	}
	// then, free the space for the Graph
	free(  mygraph  );								// COMPLETE
}

