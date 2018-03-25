#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define size 30								//initializing maximum no of vertex for graph

struct graph{
	int vertex;
	struct graph *next;
};

struct graph *s[size];
int visited[size];								//array for checking a vertex is visited or not
int distance[size];								//array to find distance of each vertex from startvertex

struct queue{
	int data;
	struct queue *qnext;
};
struct queue *front=NULL;							//to keep track of front vertex of queue
struct queue *rear=NULL;							//to keep track of last vertex of queue

void Enqueue(int x)								//to Enqueue a node in queue
{
	struct queue *temp;
	temp=(struct queue*)malloc(sizeof(struct queue));
	temp->data=x;
	temp->qnext=NULL;
	if(front==NULL)
	{
		front=rear=temp;
	}
	else
	{
		rear->qnext=temp;
		rear=temp;
	}
}

int Dequeue()									//to Dequeue a node from queue
{
	struct queue *temp=front;
	int a=front->data;
	if(front==rear)
	{
		front=rear=NULL;
		free(temp);
		return(a);
	}
	else
	{
		front=front->qnext;
		free(temp);
		return(a);	
	}
}

void BFS(int i)									//BFS function to traverse adjacency list breadth wise
{
	struct graph *p;
	int d=i;									//a integer to keep track of predecessor vertex
	visited[i]=1;
	distance[i]=0;
	printf(" %d",i);
	Enqueue(i);
	while(1)
	{
		d=i;
		p=s[i];
		while(p!=NULL)
		{
			i=p->vertex;
			if(visited[i]!=1)
			{
				visited[i]=1;
				distance[i]=distance[d]+1;				//distance of each vertex from its source vertex will be equal to distance of its predecessor vertex + 1
				Enqueue(i);
				//printf(" %d",i);
			}
			p=p->next;
		}
		if(front==NULL)
			return;
		i=Dequeue();
	}
}

void addedge(int u, int v)							//to add edge between 2 vertices
{
	struct graph *temp;
	temp=(struct graph*)malloc(sizeof(struct graph));
	temp->vertex=v;
	temp->next=NULL;
	if(s[u]==NULL)
	{
		s[u]=temp;
	}
	else
	{
		struct graph *traversal = s[u];
		while(traversal->next != NULL)
			traversal = traversal->next;
		traversal->next = temp;
	}
}

int main()
{
	int vertices,i,edges,v1,v2,StartVertex;
	printf("Enter no of Vertices: ");
	scanf("%d",&vertices);
	printf("Enter no Edges: ");
	scanf("%d",&edges);
	for(i=0;i<vertices;i++)
	{
		s[i]=NULL;							//initializing s[] to NULL
		visited[i]=0;							//initializing every vertices as not visited
		distance[i]=-1;
	}
	for(i=0;i<edges;i++)
	{
		printf("Enter an Edge (u,v):");
		scanf("%d %d",&v1,&v2);

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
	printf("enter the start vertex for BFS: ");
	scanf("%d",&StartVertex);
	printf("BFS for this graph is: ");
	BFS(StartVertex);							//calliing BFS function
	printf("\n\n");
	for(i=0;i<vertices;i++)
	{
		printf("distance of vertex %d from sourse vertex is %d\n",i,distance[i]);
	}
	return 0;
}
