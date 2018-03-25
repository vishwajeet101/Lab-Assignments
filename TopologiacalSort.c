#include<stdio.h>
#include<stdlib.h>
#define size 30						//initializing maximum no of vertices for graph

struct graph {
	int vertex;
	struct graph *next;
};

struct graph *s[size];			
int visited[size];					//array for checking a vertex is visited or not
int cyclestack[size];				//to store vertex which are in cycle
int top=-1;
int startTime[size];				//to check start time of a vertex 
int finishTime[size];				//to check finish time of a vertex
int clock=0;						//a variable to determine start/finish time of a vertex
int topostack[size];				//to store vertex for topological sorting
int top1=-1;


void cyclepush(int data)					//to push vertex into cyclestack
{
	top++;
	cyclestack[top]=data;
}

int cyclepop()							//to pop vertex out of the cyclestack
{
	int data=cyclestack[top];
	top--;
	return data;
}

void topopush(int data)					//to push vertex into topostack
{
	top1++;
	topostack[top1]=data;
}

int topopop()							//to pop vertex out of the topostack
{
	int data=topostack[top1];
	top1--;
	return data;
}

void TopologicalSort(int i)				//to traverse adjacency list
{
	int c=i;						//to store value of i as it changes in while loop
	struct graph *p;
	p=s[c];
	visited[c]=1;
	cyclepush(c);
	startTime[c]=clock;
	clock++;
	while(p!=NULL)
	{
		i=p->vertex;
		if(visited[i]==0)
		{
			TopologicalSort(i);
			cyclepop();
			topopush(i);
		}
		else if(startTime[i]<startTime[c] && finishTime[i]==-1)			
		{
			c=cycleprint(i);
			exit(0);
		}
		p=p->next;
	}
	finishTime[c]=clock;
	clock++;
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

int cycleprint(int s)							//function to print cycle
{
	printf("cycle detected:");
	int a[size],k,i=0;
	while(cyclestack[top]!=s)
	{
		a[i]=cyclepop();
		i++;
	}
	k=i-1;
	printf(" %d",s);
	for(i=k;i>=0;i--)
	printf(" %d",a[i]);
	printf(" %d",s);
	return 0;
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
		startTime[i]=-1;
		finishTime[i]=-1;
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
	}
	
	
	printf("\n\n");
	for(i=0;i<vertices;i++)
	{
		if(visited[i] == 0)
		{
			while(top!=-1)
			cyclepop();								//emptying cyclestack before starting dfs traversal
			TopologicalSort(i);
			topopush(i);
		}
	}

	printf("The Topological sort for this graph is:");
	while(top1!=-1)
	printf(" %d",topopop());	

	return 0;
}

