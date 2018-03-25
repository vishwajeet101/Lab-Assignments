#include<stdio.h>
#include<stdlib.h>
#define size 30						//initializing maximum no of vertices for graph

struct graph {
	int vertex;
	struct graph *next;
};

struct graph *s[size];			
int visited[size];					//array for checking a vertex is visited or not


void DFS(int i)						//to traverse adjacency list
{
	struct graph *p;
	printf(" %d",i);
	p=s[i];
	visited[i]=1;
	while(p!=NULL)
	{
		i=p->vertex;
		if(visited[i]==0)
			DFS(i);
		p=p->next;
	}
}

void addedge(int v1,int v2)				//to add edge between 2 vertices				
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
		s[i]=NULL;							//initializing s[] to NULL
		visited[i]=0;						//initializing every vertices as not visited
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
		addedge(v1,v2);
		addedge(v2,v1);
	}
	
	printf("\n\n");
	printf("DFS for this Graph is :");
	
	for(i=0;i<vertices;i++)
	{
		if(visited[i] == 0)
		{
			DFS(i);
		}
	}
	
	for(i=0;i<vertices;i++)
	{
		visited[i]=0;
	}
	
	printf("\n\n");
	
	for(i=0;i<vertices;i++)
	{
		if(visited[i] == 0)
		{
			c++;
			printf("component %d : ",c);
			DFS(i);
			printf("\n");
		}
	}
	printf("There are total %d components\n",c);
	return 0;
}

