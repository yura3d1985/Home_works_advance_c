#include <stdint.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 

typedef struct list 
{ 
	char word[20];
	struct list *next;
} list;

void add_to_list (list **head, char value[])
{
	list *new = calloc(1, sizeof(list));    
	for (int i = 0; i<strlen(value); i++)
	{
		new->word[i] = value[i];
	}    
	if( *head == NULL ) 
	{ 
		*head = new;    
	} 
	else 
	{        
		list *p = *head;        
		while(p->next != NULL)            
		p = p->next;       
		p->next = new;
	}
}

void print_list (list *head)
{
	list *tmp = head;
	while(tmp)    
	{	
		printf("%s",tmp->word);
		tmp = tmp->next;
				
		if (tmp != NULL) printf(" ");
	}
}

void delete_list (list **head)
{	
	list *tmp = *head;
	list *next;
	
	while(tmp)    
	{        
		 next = tmp->next;
		 free(tmp);
		 tmp = next; 
	}
	*head = NULL;
}

void swap_elements (list **head, int idx_1, int idx_2)
{
	list *tmp;
	char word_1[20], word_2[20];
	
	tmp = *head;
	
	for (int i = 1; i < idx_1; i++) tmp = tmp->next;
	for (int i = 0; i < (sizeof(tmp->word)/sizeof(tmp->word[0])); i++)
	{
		word_1[i] = tmp->word[i];
	}
	
	tmp = *head;  
	
	for (int i = 1; i < idx_2; i++) tmp = tmp->next;
	for (int i = 0; i < (sizeof(tmp->word)/sizeof(tmp->word[0])); i++)
	{
		word_2[i] = tmp->word[i];
	}
	
	tmp = *head;
	
	for (int i = 1; i < idx_1; i++) tmp = tmp->next;
	for (int i = 0; i < (sizeof(tmp->word)/sizeof(tmp->word[0])); i++)
	{
		tmp->word[i] = word_2[i];
	}
	  
	tmp = *head;
	
	for (int i = 1; i < idx_2; i++) tmp = tmp->next;
	for (int i = 0; i < (sizeof(tmp->word)/sizeof(tmp->word[0])); i++)
	{
		tmp->word[i] = word_1[i];
	}

}

int main(void)
{ 	   
	int i = 0, j = 0, min_idx;
	int k = 0;
	
	list *head  = NULL;
	list *tmp_1 = NULL;
	list *tmp_2 = NULL;
	char c, string_tmp[20] = {0}; 
	
	char current_min[20];   
			
	do
	{
		c = getchar();
		
		if((c != ' ') && (c != '.'))
		{
			string_tmp[i] = c;
			i++;
		}
		else
		{
			add_to_list(&head, string_tmp);
			memset(string_tmp, 0, strlen(string_tmp));
			i = 0;
		}
	} while(c != '.');
	
	tmp_1 = head;
	
	while (tmp_1)
	{
		memset(current_min, 0, strlen(current_min));
		
		for (k = 0; k < strlen(tmp_1->word); k++)
		{
			current_min[k] = tmp_1->word[k];
		}	
			
		min_idx = 1;
		i = i + 1;
		j = i;
		tmp_2 = tmp_1;
		
		while((tmp_2 = tmp_2->next))
		{
			j = j + 1;
										
			if (strcmp(current_min,tmp_2->word) > 0)
			{
				min_idx = j;
				memset(current_min, 0, strlen(current_min));
				for (k = 0; k < strlen(tmp_2->word); k++)
				{
					current_min[k] = tmp_2->word[k];
				}	
			}
		}
		
		if (i == j) break;
		
		if (min_idx > i) swap_elements(&head,i,min_idx);
		
		tmp_1 = tmp_1->next;
	}
		
	print_list (head);
	delete_list (&head);
	
	return 0; 
}

