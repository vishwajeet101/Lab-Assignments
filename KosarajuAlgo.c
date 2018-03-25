#include<stdio.h>
#include<stdlib.h>
# define size 50

int stack[size];
int top=-1;									//to keep track of top vertex in stack
void push(int vertex)						//to push vertex in stack
{
	top++;
	stack[top]=vertex;
}

int pop()									//to pop vertex out of stack
{
	int vertex=stack[top];
	top--;
	return vertex;
}

struct graph{
	int vertex;
	struct graph *next;
};

struct graph *list[size];					//array to represent adjacency list of original graph
struct graph *REVERSElist[size];			//array to represent adjacency list of REVERSED graph
int visited[size];							//array for checking a vertex is visited or not in original graph
int REVERSEvisited[size];					//array for checking a vertex is visited or not in REVERSED graph
int Count=0;								
int Component[size];


void addedge(int u,int v)					//to add edge between 2 vertices in original graph
{
	struct graph *temp;
	temp=(struct graph *)malloc(sizeof(struct graph));
	temp->vertex=v;
	temp->next=NULL;
	if(list[u]==NULL)
	{
		list[u]=temp;
	}
	else
	{
		struct graph *traversal=list[u];
		while(traversal->next!=NULL)
		{
			traversal=traversal->next;
		}
		traversal->next=temp;
		
	}
}

void REVERSEaddedge(int u,int v)			//to add edge between 2 vertices in REVERSED graph
{
	struct graph *temp;
	temp=(struct graph *)malloc(sizeof(struct graph));
	temp->vertex=v;
	temp->next=NULL;
	if(REVERSElist[u]==NULL)
	{
		REVERSElist[u]=temp;
	}
	else
	{
		struct graph *traversal=REVERSElist[u];
		while(traversal->next!=NULL)
		{
			traversal=traversal->next;
		}
		traversal->next=temp;
		
	}
}


void DFS(int i)								//DFS function for original graph
{
	struct graph *temp=list[i];
	visited[i]=1;
	while(temp!=NULL)
	{
		if(visited[temp->vertex]==0)
		{
			DFS(temp->vertex);
		}
		temp=temp->next;
	}
	push(i);								//pushing vertex into stack by its finish time
}

void REVERSEDFS(int i)						//DFS function for REVERSED graph
{
	Component[i]=Count;
	struct graph *temp=REVERSElist[i];
	REVERSEvisited[i]=1;
	while(temp!=NULL)
	{
		if(REVERSEvisited[temp->vertex]==0)
		{
			REVERSEDFS(temp->vertex);
		}
		temp=temp->next;
	}
	
}




int main()
{
	int i,j,k,vertices,AdjacentVertex,u,v,TopOfStack;
	printf("Enter no of Vertices in the graph: \n");
	scanf("%d",&vertices);
	for(i=0;i<vertices;i++)
	{
		visited[i]=0;
		REVERSEvisited[i]=0;
		list[i]=NULL;
		REVERSElist[i]=NULL;
	}
	
	for(i=0;i<vertices;i++)
	{
		while(1)
		{
			scanf("%d",&AdjacentVertex);
			if(AdjacentVertex == -1)
				break;
			addedge(i,AdjacentVertex-1);								//for original graph
			REVERSEaddedge(AdjacentVertex-1,i);							//for REVERSED graph
		}
	}
	
	for(i=0;i<vertices;i++)												//calling DFS function on original graph
	{
		if(visited[i] == 0)
			DFS(i);
	}
	
	
	while(top!=-1)														//calling DFS function on REVERSED graph with topmost vertex on stack
	{
		TopOfStack=pop();
		if(REVERSEvisited[TopOfStack] == 0)
		{
			Count++;
			REVERSEDFS(TopOfStack);
		}
	}
	
	printf("\n Total Component : %d\n",Count);
	printf("\n\nVertex    |     Component No");
	for(i = 0;i < vertices;i++)
	{
		printf("\n%d     -------     %d",i + 1,Component[i]);
	}
	
}
