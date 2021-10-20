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

void WordArray(FILE* fp, char wordlist[NODES][WORDSIZE]);
void CreateGraph(Graph* mygraph, char wordlist[NODES][WORDSIZE], char *option,int argc);


int main(int argc, char *argv[])
{
	FILE* fp = fopen("wordlist.txt","r"); //Open the file
	
	// Make sure that the file opens
	if (fp == NULL)
	{
		printf("Error while opening the word file\n");
	}
	
	char wordlist[NODES][WORDSIZE]; // 2d array that contains the words. 1 extra character for '\n'

	// First word is not being read properly ('ble' instead of 'able').
	char word[WORDSIZE+1] = "";
	
	for (int i=0;i<NODES;i++)
	{
		fscanf(fp,"%s", word); //scan the word line by line
		strcpy(wordlist[i],word);//store the word into the array
	}


	// WordArray(fp, wordlist); // This function is only reading the last word 'zone' again and again

	//print the list of words

	for (int j=0;j<NODES;j++)
	{
		for (int k = 0;k<WORDSIZE;k++)
		{
			printf("%c",wordlist[j][k]);
		}
		printf("\n");
	}

	
	fclose(fp); //close the file to free memory

	int source = atoi(argv[1]); // source node/word (0<= source <= 499)
	int destination = atoi(argv[2]); //destination node/word (0<= destination <=499) (destination != source)
	char *option = argv[3]; // swap transformation option
	
	Graph* mygraph = InitializeGraph(NODES); //initialize the graph
	CreateGraph(mygraph,wordlist,option,argc); // Create the graph with all the edges	
	
	printGraph(mygraph); // print the graph
	deleteGraph(mygraph); // delete the graph to free memory
	
	return 0;
}

/*
Function to initialize the graph
input: 
mynodes - number of nodes in the graph

return:
mygraph - initialized graph
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
Function to initialize a node
input: 
myoutNodeIndex - index of the out node

return:
newnode - initialized node
*/
Node* InitializeNode(int myoutNodeIndex)
{
	Node* newnode = malloc(sizeof(Node*));
	newnode->outNodeIndex = myoutNodeIndex;					
	newnode->next = NULL;
	return newnode;
}

/*
Function to create an edge
inputs: 
mygraph - graph in which you are working
node1 - source node
node2 - destination node
*/
int addEdge(Graph* mygraph, int node1, int node2)
{
	Node* newnode = InitializeNode(node2);
	newnode->next = mygraph->alists[node1];
	mygraph->alists[node1] =  newnode;
	return 0;
}

/*
Function to print the graph
input: 
mygraph - graph to be printed
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
			printf("%d  ", temp->outNodeIndex);			// COMPLETE
			temp =   temp->next  ;						// COMPLETE
		}
		printf("\n");
	}
}

/*
Function to delete the graph to free memory
input: 
mygraph - graph to be deleted
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
			tempnext = temp->next;						// COMPLETE
			free(  temp   ); 						// COMPLETE
			temp=  tempnext;							// COMPLETE
		}
	}
	// then, free the space for the Graph
	free(  mygraph  );								// COMPLETE
}

/*
Function to create the word list
input: 
fp - external file that contains the list of all the words
wordlist - 2d array that will store the word
*/
void WordArray(FILE* fp, char wordlist[NODES][WORDSIZE])
{
	char word[WORDSIZE] = "";
	
	for (int i=0;i<NODES;i++)
	{
		fscanf(fp,"%s", word); //scan the word line by line		
		strcpy(wordlist[i],word);//store the word into the array
	}
}

/*
Function to create the graph with all the edges
input: 
mygraph - graph in which you are working
wordlist - 2d array that contains the words
option,argc - contains (or not) the swap transformation option
*/
void CreateGraph(Graph* mygraph, char wordlist[NODES][WORDSIZE], char *option, int argc)
{
	for (int i=0;i<NODES;i++)
	{
		for (int j=i+1;j<NODES;j++)
		{
			int counter = 0;
			int identical_index[WORDSIZE] = {-1,-1,-1,-1};
			
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
						if ((identical_index[k]==-1) && (identical_index[k+1]==-1) && (wordlist[i][k] == wordlist[j][k+1]) && (wordlist[i][k+1] == wordlist[j][k])) //Compare 2 (different) adjacent letters
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