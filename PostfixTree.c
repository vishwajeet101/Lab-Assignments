#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define size 100

struct tree{
	int data;
	struct tree *left;
	struct tree *right;
};

struct tree *stack[size];				//initializing array of structures
int top=-1;								//innitializing variables globally
struct tree *node;

struct tree * pop()						//to pop node out of stack
{
	struct tree *temp;
	temp=stack[top];
	top--;
	return(temp);
}

void push(struct tree *node)			//to push node into stack
{
	top++;
	stack[top]=node;
}

void operand(int b)						//to push operand in stack
{
	node=(struct tree *)malloc(sizeof(struct tree));
	node->data=b;
	node->left=NULL;
	node->right=NULL;
	push(node);
}

void operators(int a)					//to create node by poping out last 2 nodes of stack and push that new node in stack 
{
	node=(struct tree *)malloc(sizeof(struct tree));
	node->data=a;
	node->right=pop();
	node->left=pop();
	push(node);
}

int check(char ch)						//to check operators,operands or any errors in input string
{
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
	return 2;
	else if(ch >= '0' && ch<= '9')
	return 1;
	else if(ch == ' ')
	return 4;
	else {
			printf("Error in input");
			exit(0);
		 }
	
}

int convert(char c[])					//to convert character number into integer data type
{
	int sum=0,value,b[30],i=0,j=0;
	while(c[i]!='\0')
	{
		b[i]=c[i]-'0';
		j=i;
		while(j!=-1)
		{
			b[j]=b[j]*10;
			j--;
			
		}
		i++;
	}
	j=0;
	for(j=0;j<i;j++)
	{
		sum =sum + b[j];
	}
	value = sum / 10;
	return value;
	
}

/*displaying the tree*/
void display(struct tree *ptr,int space)	
{
 int i;
 if ( ptr!=NULL )
 {
  	display(ptr->right, space+1);		//Recursive Call
  	printf("\n");
    for (i = 0; i < space; i++)
    printf("    "); 
    if((ptr->left != NULL && ptr->right !=NULL) && (ptr->data == '+' || ptr->data == '-'|| ptr->data == '*'|| ptr->data == '/'||ptr->data == '^'))
    {
    	printf("%c", ptr->data);
    }
    else
    printf("%d", ptr->data);
    display(ptr->left, space+1);		//Recursive Call
 }
}

int main()								//calling main function
{
	int i=0,j=0,var,p;
	char s[100],c[10];
	printf("PLEASE Enter a Valid Postfix Expression : ");
	scanf("%[^\n]99s",s);
	while(s[i]!='\0')
	{
		p=check(s[i]);
		if(p == 1)
		{
			j=0;
			while(s[i]!= ' ')
			{
				c[j]=s[i];
				i++;
				j++;
			}
			c[j]='\0';
			var=convert(c);				//calling function to convert character number into integer data type
			operand(var);
			i++;
		}
		else if(p == 2)
		{
			operators(s[i]);
			i++;
		}
		else if(p== 4)
		{
			i++;
		}
		else if(p == 5)
		{
			printf("error in input");
			return 8;
		}
	}
	display(node,1);
	free(node);
	
	return 0;
}

