#include<stdio.h>
# define size 100

void swap(int *a,int *b)
{
	int s;
	s = *a;
	*a = *b;
	*b = s;
}

void MinHeapify(int a[],int index,int n)
{
	int lindex,rindex,s;
	lindex=2*index+1;
	rindex=2*index+2;
	if(index >= (n / 2))
	{
		return;
	}
	
	if( rindex<n && a[rindex]<a[lindex])
	{
		s=rindex;
	}
	else
	{
		s=lindex;
	}
	if(a[index]>a[s])
	{
		swap(&a[index],&a[s]);
		MinHeapify(a,s,n);
	}
}

void BuildHeap(int a[],int n)
{
	int i;
	for(i= (n/2) -1 ; i>=0 ; i--)
	{
		MinHeapify(a,i,n);
	}
}

int FindMin(int a[])
{
	return a[0];
}

void DeleteHeap(int a[],int index,int n)
{
	swap(&a[index],&a[n-1]);
	a[n-1]=-1;
	MinHeapify(a,index,n-1);
}

int ExtractMin(int a[],int n)
{
	int min=a[0];
	DeleteHeap(a,0,n);
	return min;
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
		while(a[index]<a[parent])
		{
			swap(&a[index],&a[parent]);
			index=parent;
			parent=(index-1)/2;	
		}
	}
}

void insert(int a[],int value,int n)
{
	
	int parent,index=n-1;
	a[index]=value;
	while(index>0)
	{
		parent=(index-1)/2;
		if(a[parent]<a[index])
		{
			return;
		}
		swap(&a[parent],&a[index]);
		index=parent;
		DisplayElements(a,n);
	}
	a[0]=value;
}

void HeapSort(int a[],int n)
{
	int i;
	printf("sorted list is : ");
	for(i=0;i<n;i++)
	printf(" %d",ExtractMin(a,n-i));
}

DisplayElements(int a[],int n)
{
	int i;
	printf("\nthe heap: \n");
	for(i=0;i<n;i++)
	{
		printf(" %d",a[i]);
	}	
}

int main()
{
	int i,j,n,index,newKey;
	int a[size],extractedmin,min,choice,value;
	do{
		printf("\nEnter Your Choice \n");
		printf("Press 1) for BuildHeap\n");
		printf("Press 2) for Find Min\n");
		printf("Press 3) for Extract Minimum\n");
		printf("Press 4) for Decrease Key\n");
		printf("Press 5) for Insert\n");
		printf("Press 6) for Display Elements\n");
		printf("Press 7) for HeapSort\n");
		printf("Press 8) for Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:				
				printf("enter no of elements you want in heap: ");
				scanf("%d",&n);
				printf("enter the elements : ");
				for(i=0;i<n;i++)
				{
					scanf("%d",&a[i]);
				}
				BuildHeap(a,n);
				break;
			case 2:
				min = FindMin(a);
				printf("Min is %d ",min);
				break;
			case 3:
				extractedmin=ExtractMin(a,n);
				printf("Min is Extraxted from heap & min is %d\n\n",extractedmin);
				n=n-1;
				break;
			case 4:
				
				printf("Enter index whose key is to be decreased : ");
				scanf("%d",&index);
				printf("Enter new Key Value : ");
				scanf("%d",&newKey);
				DecreaseKey(a,index - 1,newKey,n);
				break;
			case 5:
				printf("Enter a value to insert in heap: ");
				scanf(" %d", &value);
				insert(a,value,++n);
				break;
			case 6:
				DisplayElements(a,n);
				break;
			case 7:
				HeapSort(a,n);
				break;
			case 8:
				return(0);
			default:
				printf("Please Enter valid Choice\n");
		}
	}while(1);
	
}
