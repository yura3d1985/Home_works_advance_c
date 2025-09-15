#include <stdio.h>  
  
int main() 
{    
    int N, tmp, tmp_next, count;

    scanf("%d", &N);  
            
    scanf("%d", &tmp);
      
    count = 1;
       
    for (int i = 1; i < N; i++) 
    {  
        scanf("%d", &tmp_next);  
          
        if (tmp_next > tmp)
        {  
            tmp = tmp_next;  
            count = 1; 
        } 
        else if (tmp_next == tmp) 
        {  
            count++;
        }  
    }  
      
    printf("%d\n", count);  
      
    return 0;  
}  
