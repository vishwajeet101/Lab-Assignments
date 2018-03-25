#define size 30
#include<stdio.h>
char stack[size];
int top = -1;
void push(char data)
{
	top++;
	stack[top]=data;
}

int pop()
{
	int temp=stack[top];
	top--;
	return temp;
}

int priority(char op)
{
	if (op == '+' || op == '-')
	return 1;
	else if (op == '*' || op == '/')
	return 2;
	if(op == '(')
	return 0;
}


int main()
{
	int i=0,j=0,a,b,c,d,count;
	char s[50],temp;
	printf("enter a valid infix expression: ");
	scanf("%[^\n]49s",&s);
	printf("printing input : %s\n",s);
	while(s[i]!='\0')
	{
		if(s[i] >= '0' && s[i] <= '9')
		{
			while(s[i] >= '0' && s[i] <= '9')
			{
				printf("%c",s[i]);
				i++;	
			}
			i--;
		}
		else if(s[i]==')')
		{
			while(temp=pop()!= '(')
			{
				printf(" %c",temp);
			}
		}
		else if(s[i]=='(')
		{
			push(s[i]);
		}
		else if (s[i]== '+' || s[i]== '-' || s[i]== '*' || s[i]== '/')
		{
			while(priority(stack[top]) >= priority(s[i]))
			{
				printf(" %c",pop());
			}
			push(s[i]);
		}
		i++;
		printf(" ");
	}
	
	while(top!= -1)
	{
		printf(" %c",pop());
	}
	
	

}

