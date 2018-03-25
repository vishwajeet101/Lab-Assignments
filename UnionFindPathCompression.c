#include<stdio.h>
#include<stdlib.h>
#define size 30						//initializing maximum no of vertices for graph

struct graph {
	int vertex;
	struct graph *next;
};

struct subset{
	int parent;
	int rank;
};

struct graph *s[size];
struct subset subset[size];			
int visited[size];					//array for checking a vertex is visited or not
int parent[size];

int find(int i)
{
	if(subset[i].parent==i)
		return i;
	else
		return find(subset[i].parent);
}

void Union(int x,int y)
{
	int xroot=find(x);
	int yroot=find(y);
	
	if(subset[xroot].rank < subset[yroot].rank)
		subset[xroot].parent=yroot;
	else if(subset[xroot].rank > subset[yroot].rank)
		subset[yroot].parent=xroot;
	else
	{
		subset[yroot].parent=xroot;
		subset[xroot].rank++;
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
		parent[i]=-1;
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
	struct graph *p;
	int TraverseVertex;
	int ParentOfi;
	int ParentOfd;
	int CycleFlag=0;
	for(i=0;i<vertices;i++)
	{
		p=s[i];
		while(p!=NULL)
		{
			TraverseVertex=p->vertex;
			if(visited[p->vertex]==0)
			{
				visited[i]=1;
					ParentOfi=find(i);
					ParentOfd=find(p->vertex);
					if(ParentOfi==ParentOfd)
					{
						printf("Cycle Detected in the Graph\n");
						return 0;
					}
					else
						Union(i,p->vertex);
				
			}
			p=p->next;
			
		}
	}
	
	 printf("No cycle in the graph\n");
	
	return 0;
}

