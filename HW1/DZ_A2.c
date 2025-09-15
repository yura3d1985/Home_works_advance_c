#include <math.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
  
int main() 
{    
    uint32_t K;
    
    uint32_t N;
        
    scanf("%" SCNu32, &N);
    scanf("%" SCNu32, &K);
     	
    N = ((N >> K) | (N << (32 - K)));
    
    printf("%" SCNu32, N);
      
    return 0;  
}
