#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h>
#include <inttypes.h>
  
typedef struct list {
	uint64_t address;
	size_t size;
	char comment[64];
	struct list *next;
} list;

list* push(list *p, uint64_t addr, size_t size)
{
	list *p_tmp;
	p_tmp=malloc(sizeof(list));
	p_tmp->address = addr;
	p_tmp->size = size;
	p_tmp->next = p;
	return p_tmp;
}

void print_list(const list *p)
{
	const list* p_tmp = p;
	
	while (p_tmp != NULL)
	{
		printf("%" SCNu64, p_tmp->address);
		printf("\n");
		printf("%lld", p_tmp->size);
		printf("\n");
			
		p_tmp = p_tmp->next;
	}
}

uint64_t findMaxBlock(list *head)
{
	const list* p_tmp = head;
	uint64_t addr_tmp = p_tmp->address;
	size_t max_size = p_tmp->size;
		
	if (p_tmp == NULL) return 0;
	
	while (p_tmp != NULL)
	{
		if (max_size < p_tmp->size)
		{
				max_size = p_tmp->size;
				addr_tmp = p_tmp->address;
		}	
	p_tmp = p_tmp->next;
	}
	
	return addr_tmp;
}

size_t totalMemoryUsage(list *head)
{
	const list* p_tmp = head;
	size_t total_size = 0;
	
	if (p_tmp == NULL) return 0;
	
	while (p_tmp != NULL)
	{
		total_size = total_size + p_tmp->size;	
		p_tmp = p_tmp->next;
	}
	
	return total_size;
}

int main() 
{    
    list *data = NULL;
    
    uint64_t i, data_number, addr, addr_tmp;
    size_t size, total_size;
       
    scanf("%" SCNu64, &data_number);
    
    for (i=0; i<data_number; i++)
    {
		scanf("%" SCNu64, &addr);
		scanf("%lld", &size);
		
		data = push(data, addr, size);	
	}
		
	addr_tmp = findMaxBlock(data);
	
	printf("%" SCNu64, addr_tmp);
	printf("\n");
	
	total_size = totalMemoryUsage(data);
	
	printf("%lld", total_size);
	printf("\n");
		
    return 0;  
}
