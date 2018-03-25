#include<stdio.h>
#include<stdlib.h>
# define INF 99999

int main()
{
	int i,j,k,noOfAdjacentVertices,v1=0,v2,weight;
	int vertices;
	printf("Enter no of vertices:\n");
	scanf("%d",&vertices);
	int graph[vertices][vertices];							//array for storing graph in adjacency matrix
	int pred[vertices][vertices];							//array for storing predicessors
	
	for(i=0;i<vertices;i++)
	{
		for(j=0;j<vertices;j++)
		{
			if(i==j)
				graph[i][j]=0;								//for diagonal Element of matrix
			else
				graph[i][j]=INF;
		}
	}
	
	
	for(i=0;i<vertices;i++)
	{
		scanf("%d",&noOfAdjacentVertices);
		for(j=0;j<noOfAdjacentVertices;j++)
		{
			scanf("%d %d",&v2,&weight);
			graph[v1][v2-1]=weight;
			graph[v2-1][v1]=weight;
		}
		v1++;
	}
	
	
	printf("\n\nThe Graph in Adjacency matrix representation is :\n\n");	
	for(i=0;i<vertices;i++)
	{
		for( j=0;j<vertices;j++)
		{
			if(graph[i][j] == INF)
				printf("%7s","INF"); 
			else
				printf("%7d",graph[i][j]);
		}
		printf("\n");
	}
	
	//iniitializing predicessor matrix for graph
	for(i=0;i<vertices;i++)
	{
		for( j=0;j<vertices;j++)
		{
			if(i==j)
				pred[i][j]=INF;
			
			if(graph[i][j]!=INF)
				pred[i][j]=i;
			else
				pred[i][j]=INF;
				
		}
	}
	
	//Floyd-Warshall Algorithm
	for(k=0;k<vertices;k++)
	{
		for(i=0;i<vertices;i++)
		{
			for(j=0;j<vertices;j++)
			{
				if (graph[i][k]!=INF && graph[k][j]!=INF && graph[i][j] > graph[i][k]+graph[k][j])
					{
						graph[i][j] = graph[i][k]+graph[k][j];
						pred[i][j]=pred[k][j];
					}
						
			}
		}
	}
	
	
	printf("The Solution Graph:\n\n\n");
	for(i=0;i<vertices;i++)
	{
		for( j=0;j<vertices;j++)
		{
			if(graph[i][j] == INF)
				printf("%7s","INF"); 
			else
				printf("%7d",graph[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	//for displaying distance between 2 vertices and predicessor of end vertex in that path
	for(i = 0;i< vertices;i++)
		for(j = 0;j< vertices;j++)
		{
			printf("(%d,%d) -:  dist : ",i+1,j+1);
			if (graph[i][j] == INF)
                printf("%s ", "INF");
            else
                printf ("%d ", (graph[i][j]));
			if(pred[i][j]!=INF)
			{
				printf("pred : %d ",pred[i][j]+1);
			}
			else
				printf("pred : No path");
			printf("\n");
		}
}

