#include <math.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
  
int main() 
{    
    uint32_t N, count = 0, i, bit;
    
    scanf("%" SCNu32, &N);
                	
    for (i = 0; i < 32; i++)
    {    
		bit = N & 1;
		
		if ( bit == 1 ) count = count + 1; 
    
		N = N >> 1;
	}
    
    printf("%" SCNu32, count);
      
    return 0;  
}
