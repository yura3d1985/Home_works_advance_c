#include <math.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
  
int main() 
{    
    uint32_t N, N_tmp, N_max = 0, K, i, mask = 1;
    
    scanf("%" SCNu32, &N);
    scanf("%" SCNu32, &K);
    
    for (i = 1; i < K; i++)
    {
		mask = ((mask << 1) | mask);
	}
            	
    for (i = 1; i < 32; i++)
    {    
		N_tmp = N & mask;
		
		if ( N_tmp > N_max ) N_max = N_tmp; 
    
		N = N >> 1;
	}
    
    printf("%" SCNu32, N_max);
      
    return 0;  
}
