#include<stdio.h>
#include<stdlib.h>
#define size 30						//initializing maximum no of vertices for graph

struct graph {
	int vertex;
	struct graph *next;
};

struct graph *s[size];			
int visited[size];					//array for checking a vertex is visited or not
int parent[size];

int find(int parent[],int i)
{
	if(parent[i]==-1)
		return i;
	else
		return find(parent,parent[i]);
}

void Union(int parent[],int x,int y)
{
	int xset=find(parent,x);
	int yset=find(parent,y);
	parent[xset]=yset;
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
				if(parent[p->vertex]==-1 &&parent[i]==-1)
				{
					Union(parent,p->vertex,i);
				}
				else
				{
					ParentOfi=find(parent,i);
					ParentOfd=find(parent,p->vertex);
					if(ParentOfi==ParentOfd)
					{
						printf("Cycle Detected in the Graph\n");
						return 0;
					}
					else
						Union(parent,i,p->vertex);
				}
			}
			p=p->next;
			
		}
	}
	
	 printf("No cycle in the graph\n");
	
	return 0;
}

