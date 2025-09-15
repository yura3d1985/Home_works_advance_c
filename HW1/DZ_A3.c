#include <math.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
  
int main() 
{    
    uint32_t N, K, i, mask = 1;
    
    scanf("%" SCNu32, &N);
    scanf("%" SCNu32, &K);
    
    for (i = 1; i < K; i++)
    {
		mask = ((mask << 1) | mask);
	}
            	
    N = N & mask;
    
    printf("%" SCNu32, N);
      
    return 0;  
}
