#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define size 50

struct graph{
	int u;
	int v;
	int weight;
	int flag;
}list[size];


void swap(int *x,int *y)
{
	int t = *y;
	*y = *x;
	*x = t;
}

struct subset{
	int parent;
	int rank;
}subset[size];

int find(int u)
{
	if(subset[u].parent==u)
		return u;
		
	return find(subset[u].parent);
}

void Union(int x,int y)
{
	int xroot=find(x);
	int yroot=find(y);
	if(subset[xroot].rank > subset[yroot].rank)
	{
		subset[yroot].parent=xroot;
	}
	else if(subset[xroot].rank < subset[yroot].rank)
	{
		subset[xroot].parent=yroot;
	}
	else
	{
		subset[xroot].parent=yroot;
		subset[yroot].rank++;
	}
}

void MakeSet(int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		subset[i].parent=i;
		subset[i].rank=0;
	}
}


void MinHeapify(struct graph a[],int index,int n)
{
	int lindex,rindex,s;
	lindex=2*index+1;				//initializing left child of index
	rindex=2*index+2;				//initializing right child of index
	if(index >= (n / 2))
	{
		return;
	}
	
	if( rindex<n && a[rindex].weight < a[lindex].weight)		//checking which index is less in lindex and rindex
	{
		s=rindex;
	}
	else
	{
		s=lindex;
	}
	if(a[index].weight>a[s].weight)				//swapping the parent with smaller child and calling minheapify to maintain heap property
	{
		swap(&a[index].weight,&a[s].weight);
		MinHeapify(a,s,n);
	}
}



void BuildHeap(struct graph a[],int n)				//function to change array in heap
{
	int i;
	for(i= (n/2) -1 ; i>=0 ; i--)
	{
		MinHeapify(a,i,n);
	}
}


struct graph  ExtractMin(struct graph a[],int n)				//function delete minimum value in heap and returns it and creates new heap with remaining elements
{
	struct graph min=a[0];
	
	swap(&a[0].weight,&a[n-1].weight);							//swaping value at index position with last one
	MinHeapify(a,0,n-1);										//calling function to maintain heap property
	return min;
}


int main()
{
	int vertices,v1,v2,i,j,weight;
	int k=0;
	int noOfEdges=0;
	int noOfadjvertices;
	struct graph temp;
	
	v1=0;
	printf("Enter no of vertices : ");
	scanf("%d",&vertices);
	for(i=0;i<vertices;i++)
	{
		scanf("%d",&noOfadjvertices);
		for(j=0;j<noOfadjvertices;j++)
		{
			scanf("%d %d",&v2,&weight);
			list[k].u=v1;
			list[k].v=v2;
			list[k].weight=weight;
			list[k].flag=0;
			noOfEdges++;
			k++;
		}
		v1++;
	}
	BuildHeap(list,noOfEdges);									//building heap with key values as edge weights
	int count=0;
	for(i=0;i<noOfEdges;i++)
	{
		temp=ExtractMin(list,noOfEdges-i);
		printf("%d\t",temp.u);
		printf("%d\n",temp.v);
		if(find(temp.u)!=find(temp.v))
		{
			printf("\nbye\n");
			Union(list[i].u,list[i].v);
			list[noOfEdges-i-1].flag=1;
			count++;
		}
	}

	if(1/*count==vertices-1*/)
	{
		printf("\nu\t\tv\t\tweight\n");
		for(i = 0;i < noOfEdges;i++)
		{
			//printf("\nhi\n");
			//printf("list[%d].flag=%d\n",i,list[i].flag);
			//if(list[i].flag == 0)
			//{
			//	printf("%d\t\t%d\t\t   %d\n",list[i].u,list[i].v,list[i].weight);
			//	printf("\nbye\n");
			//}
		}
	}
	else
	{
		printf("\nGraph is not Connected\n");
	}



}
