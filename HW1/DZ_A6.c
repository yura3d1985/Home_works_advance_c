#include <math.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
  
int main() 
{    
    uint32_t N, N_high, N_low;
    
    uint32_t mask_high = 0b11111111000000000000000000000000;
    uint32_t mask_low  = 0b00000000111111111111111111111111;
    
    scanf("%" SCNu32, &N);
    
    N_high = N & mask_high;
    N_high = ~ N_high;
    N_high = N_high & mask_high;
    
    N_low  = N & mask_low;
    
    N = N_high + N_low;
    
    printf("%" SCNu32, N);
      
    return 0;  
}
