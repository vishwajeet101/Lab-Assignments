#define SIZE 50
#include<stdio.h>
int stack [SIZE];
int top = -1;
void push(int data)
{
	top++;
	stack[top]=data;
}

int pop()
{
	int data=stack[top];
	top--;
	return data;
}

int convert(char c[])
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

int main ()
{
	int i=0,j=0,k=0,evl,a,b,d,result;
	char s[30];
	char sub[30];
	scanf("%[^\n]29s",&s);
	printf("%s\n",s);
	while(s[i]!='\0')
	{
		if(s[i]>='0' && s[i]<='9')
		{
			k=0;
			while(s[i]>='0' && s[i]<='9')
			{
			sub[k]=s[i];
			i++;
			k++;
			}
			sub[k]='\0';
			d=convert(sub);
			push(d);
		}

		else if (s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
		{
			b=pop();
			a=pop();
			
			switch(s[i])
			{
				case '+' :
					evl = a+b;
					push(evl);
					break;
				case '-' :
					evl = a-b;
					push(evl);
					break;
				case '*' :
					evl = a*b;
					push(evl);
					break;
				case '/' :
					evl = a/b;
					push(evl);
					break;
			}
			
		}
		else
		{
			printf("\n");
		}
		i++;
		
	}
	result=pop();
	printf("RESULT=%d",result);
	return 0;
}

