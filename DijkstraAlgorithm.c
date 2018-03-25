#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define size 50

struct graph{
	int vertex;
	int weight;
	struct graph *next;
};
struct graph *list[size];						//to create adjacency list
int vertex[size];							//to keep track at which index which vertex exist
int visited[size];							//to check if vertex is visited or not
int distance[size];
int pred[size];								//to keep track of predicessor vertex							
int indices[size];							//to keep track of position of vertex

void swap(int *x,int *y)
{
	int t = *y;
	*y = *x;
	*x = t;
}

void addedge(int u, int v, int weight)					//function to add an edge
{
	struct graph *temp;
	temp=(struct graph*)malloc(sizeof(struct graph));
	if(temp==NULL)
	{
		printf("memory is not allocated properly\n");
		return;
	}
	temp->vertex=v;
	temp->weight=weight;
	temp->next=NULL;
	if(list[u]==NULL)
	{
		list[u]=temp;
	}
	else
	{
		struct graph *traversal;
		traversal=list[u];
		while(traversal->next!=NULL)
			traversal=traversal->next;
		traversal->next=temp;
	}
}




void printGraph(int vertices)							// Function to print Graph 
{
	int i;
	struct graph *temp = (struct graph*)malloc(sizeof(struct graph));
	for(i = 0;i < vertices;i++)
	{
		temp = list[i];
		printf("%d -> ",i);
		while(temp != NULL)
		{
			printf(" %d ->",temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}	
}

void MinHeapify(int a[],int index,int n)
{
	int lindex,rindex,s;
	lindex=2*index+1;				//initializing left child of index
	rindex=2*index+2;				//initializing right child of index
	if(index >= (n / 2))
	{
		return;
	}
	
	if( rindex<n && a[rindex]<a[lindex])		//checking which index is less in lindex and rindex
	{
		s=rindex;
	}
	else
	{
		s=lindex;
	}
	if(a[index]>a[s])				//swapping the parent with smaller child and calling minheapify to maintain heap property
	{
		swap(&a[index],&a[s]);
		swap(&vertex[index],&vertex[s]);
		swap(&indices[vertex[index]],&indices[vertex[s]]);
		MinHeapify(a,s,n);
	}
}



void BuildHeap(int a[],int n)				//function to change array in heap
{
	int i;
	for(i= (n/2) -1 ; i>=0 ; i--)
	{
		MinHeapify(a,i,n);
	}
}


void DeleteHeap(int a[],int index,int n)			
{
	swap(&a[index],&a[n-1]);			//swaping value at index position with last one
	swap(&vertex[index],&vertex[n-1]);
	swap(&indices[vertex[index]],&indices[vertex[n-1]]);
	//a[n-1]=-1;
	//vertex[n-1]=-1;
	//indices[vertex[n-1]]=-1;
	MinHeapify(a,index,n-1);			//calling function to maintain heap property
}



int ExtractMin(int a[],int n)				//function delete minimum value in heap and returns it and creates new heap with remaining elements
{
	int SmallDistanceVertex=vertex[0];
	DeleteHeap(a,0,n);
	return SmallDistanceVertex;
}


void DecreaseKey(int a[],int index,int newkey,int n)
{
	int parent;
	if(a[index]<newkey)
	{
			printf("you are not decreasing key rather you are increasing it");
	}
	else
	{
		parent=(index-1)/2;
		a[index]=newkey;
		while(a[index]<a[parent])			//running loop till heap property is restored
		{
			swap(&a[index],&a[parent]);
			swap(&vertex[index],&vertex[parent]);
			swap(&indices[vertex[index]],&indices[vertex[parent]]);	
			index=parent;
			parent=(index-1)/2;	
		}
	}
}


void dijkstra(int distance[],int vertices)
{
	struct graph *temp;
	int j = vertices,u;
	while(j>0)
	{
		u = ExtractMin(distance,j--);
		visited[u]=1;
		temp=list[u];
		while(temp!=NULL)							// For all edge starting from u
		{
			if(visited[temp->vertex]!=1)					// If vertex Is not Visited then continue else not
			{
				if(distance[indices[temp->vertex]] > distance[indices[u]] + temp->weight)
				{
					distance[indices[temp->vertex]]=distance[indices[u]] + temp->weight;
					pred[temp->vertex]=u;										// setting pred of current visiting vertex
					DecreaseKey(distance,indices[temp->vertex],distance[indices[temp->vertex]],j);			// decreasing key to new smaller distance
				}
			}
		temp=temp->next;
		}
	}
}


int main()
{
	int vertices,v1,v2,i,j,weight;
	int noOfadjvertices;
	int sourcevertex;
	v1=0;
	//printf("Enter no of vertices : ");
	scanf("%d",&vertices);
	for(i=0;i<vertices;i++)
	{
		//printf("Enter no of vertices adjacent to vertex %d and greater than vertex %d : ",v1,v1);
		scanf("%d",&noOfadjvertices);
		for(j=0;j<noOfadjvertices;j++)
		{
			//printf("Enter adjacent vertex with its edge weight: ");
			scanf("%d %d",&v2,&weight);
			addedge(v1,v2,weight);
			addedge(v2,v1,weight);								//in an undirected graph if u-->v is an edge then v-->u is also an edge
		}
		v1++;
	}
	printGraph(vertices);
	
	printf("Entern SourceVertex: ");
	scanf("%d",&sourcevertex);

	for(i=0;i<vertices;i++)
	{
		vertex[i]=i;
		distance[i]=100;									//initially setting the distance of all vertex to a max value
		pred[i]=-1;
		visited[i]=-1;
		indices[i]=i;
	}
	distance[sourcevertex]=0;									//distance of source vertex is set to zero
	BuildHeap(distance,vertices);									//building heap with key values as distance
	dijkstra(distance,vertices);


	printf("Vertices            Distance from Source\n");
	for(i = 0;i < vertices;i++)
	{
		printf("\n%d\t\t\t%d\n",i,distance[indices[i]]);
	}


	printf("Vertices            Predcessor\n");
	for(i = 0;i < vertices;i++)
	{
		printf("\n%d\t\t\t%d\n",i,pred[i]);
	}

}
