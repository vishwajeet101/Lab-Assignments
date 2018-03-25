#include<stdio.h>
#include<stdlib.h>
#define size 30						//initializing maximum no of vertices for graph

struct graph {
	int vertex;
	struct graph *next;
};

struct graph *s[size];			
int visited[size];					//array for checking a vertex is visited or not
int predecessor[size];
int cyclestack[size];				//to store vertex which are in cycle
int top=-1;

void push(int data)					//to push vertex into stack
{
	top++;
	cyclestack[top]=data;
}

int pop()							//to pop vertex out of the stack
{
	int data=cyclestack[top];
	top--;
	return data;
}


void Detectcycle(int i)				//to traverse adjacency list
{
	struct graph *p;
	p=s[i];
	visited[i]=1;
	push(i);
	int c=i;									
	int k=i;						//to keep track of predecessor
	while(p!=NULL)
	{
		i=p->vertex;
		if(visited[i]==0)
		{
			predecessor[i]=k;
			Detectcycle(i);
			pop();
		}
		else if(visited[i]==1&&predecessor[c]!=i)			//checking if i is not predecessor of c
		{
			printf("cycle detected:");
			printf(" %d",i);
			while(cyclestack[top]!=i)
			printf(" %d",pop());
			printf(" %d\n",pop());
			exit(0);
		}
		p=p->next;
	}
}


void addedge(int v1,int v2)						//to add edge between two vertices
{
	struct graph *p,*q;
	q=(struct graph*)malloc(sizeof(struct graph));
	q->vertex=v2;
	q->next=NULL;
	
	if (s[v1]==NULL)
	{
		s[v1]=q;
	}
	else
	{
		p=s[v1];
		while(p->next!=NULL)
			p=p->next;
		p->next=q;
	}
	
}



int main()
{
	int i,j,k,n,vertices,edge,v1,v2,c=0;
	printf("enter number of vertices:");
	scanf("%d",&vertices);
	printf("enter number of edges:");
	scanf("%d",&edge);
	for(i=0;i<vertices;i++)
	{
		s[i]=NULL;						//initializing s[] to NULL
		visited[i]=0;					//initializing every vertices as not visited
		predecessor[i]=-1;				//intializing precedessor of every vertex to be -1
	}
	for(i=0;i<edge;i++)
	{
		printf("enter an edge (u,v):");
		scanf("%d%d",&v1,&v2);
		if(v1==v2)
		{
			printf("%d---%d cant be an edge\n",v1,v2);
			exit(0);
		}
		else if(v1>=vertices || v2>=vertices)
		{
			printf("vertex can not be greater than %d\n",vertices-1);
			exit(0);
		}
		addedge(v1,v2);					//calling addedge function
		addedge(v2,v1);					//in undirected graph if (u,v) is an then (v,u) is also an edge
	}
	
	for(i=0;i<vertices;i++);
	
	printf("\n\n");
	for(i=0;i<vertices;i++)
	{
		if(visited[i] == 0)
		{
			while(top!=-1)
			pop();								//emptying cyclestack before starting dfs traversal
			Detectcycle(i);
		}
	}
	

	printf("Their is no cycle in the graph");
	return 0;
}

