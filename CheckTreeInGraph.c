#include<stdio.h>
#include<stdlib.h>
# define size 50					//initializing maximum no of vertex

struct graph {
	int vertex;
	struct graph *next;
};

struct graph *s[size];					
int visited[size];					//to check if vertex is visited or not
int predecessor[size];					//to keep track of predecessor for finding cycle
int edgesnumber=0;					//to count no of edges in the graph


void Detectcycle(int i)				
{
	struct graph *p;
	p=s[i];
	visited[i]=1;
	int c=i;									
	int k=i;						
	while(p!=NULL)
	{
		i=p->vertex;
		if(visited[i]==0)
		{
			predecessor[i]=k;
			edgesnumber++;
			Detectcycle(i);
			
		}
		else if(visited[i]==1 && predecessor[c]!=i)			
		{
			printf("given graph is not a tree beacause\n");
			printf("there is a cycle in the graph\n");
			exit(0);
		}
		p=p->next;
	}
}


void addedge(int v1,int v2)						//to addedge between vertex u to v				
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
	int i,j,k,l,vertices,adjvertex,flag=1,component=0;
	printf("enter no of vertices");
	scanf("%d",&vertices);
	for(i=1;i<=vertices;i++)
	{
		s[i]=NULL;
		visited[i]=0;
		predecessor[i]=-1;	
	}
	for(i=1;i<=vertices;i++)
	{
		printf("enter adjacent vertex of vertex %d: ",i);
		flag=1;
		while(flag==1)
		{
			scanf("%d",&adjvertex);
			if(adjvertex==-1)
			{
				flag=-1;
			}
			else if(adjvertex<i || adjvertex>vertices)
			{
				printf("invalid input");
				exit(0);
			}
			else
			{
				addedge(i,adjvertex);
				addedge(adjvertex,i);				//in an undirected graph if (u,v) is an edge then (v,u) is also an edge
			}
		}

	}
			
	for(i=1;i<=vertices;i++)
	{
		
		if(visited[i]==0)
		{
			Detectcycle(i);
			component++;						//to count no of components in the graph
		}
	}

	if(component==1 && edgesnumber==vertices-1)
	{
		printf("given graph is a tree\n");
	}
	else
	{
		printf("given graph is not a tree beacause\n");
		if(component!=1)
		printf("there are more than one component to the graph\n");
		if(edgesnumber != vertices-1)
		printf("number of edges is not equal to (total vertices-1)");
	}	

}



