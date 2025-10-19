#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 255

typedef int datatype;
 
int pst=0;
datatype st[MAX_STACK_SIZE];

void push(datatype v)
{     
	if(pst>MAX_STACK_SIZE) 
	{        
		fprintf(stderr,"Error. Stack overflow");          
	}    
	 else st[pst++]=v; 
}

datatype pop()
{    
	if(pst<=0) 
	{        
		fprintf(stderr, "Error. Stack underflow");
		return 0;    
	}      
	else
	return st[--pst];
}

void operate(char c)
{
	datatype arg1=pop();
	datatype arg2=pop();

	if (c=='+') push(arg1+arg2);    
	else 
	if (c=='-') push(arg2-arg1);
	else 
	if (c=='*') push(arg1*arg2);
	else 
	if (c=='/') push(arg2/arg1); 
}

int isDigit(char c)
{ 
	return ((c>='0')&&(c<='9')); 
}

int main(void)
{ 	   
	datatype number;      
	char c, string_tmp[MAX_STACK_SIZE];
	int i = 0, string_tmp_len = 0;
	
	while((c = getchar()) != '\n') 
	{
		string_tmp[i] = c;
		i++;
	} 
	
	string_tmp_len = strlen(string_tmp);
		
	for (i = 0; i < string_tmp_len; i++)
	{
		if (string_tmp[i] == ' ') continue;
		if (string_tmp[i] == '.') break;
		
		if (isDigit(string_tmp[i]) == 1)
		{
			number = 0;
			while (isDigit(string_tmp[i]) != 0)
			{
				number = number * 10 + string_tmp[i] - '0';
				i++;
			}
			push(number);
		}
		else		
		{
		operate(string_tmp[i]);
		}		
	}
	  
	printf("%d",pop());    
	return 0; 
}

