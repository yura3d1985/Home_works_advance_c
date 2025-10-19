#include <math.h>
#include <string.h>
#include <stdio.h> 
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
  
int cnk2(int n, int k) 
{    
	double res = 1;    
	for (int i=1; i<=k; ++i)        
	res = res * (n-k+i) / i;    
	return (int) (res + 0.01); 
}

int cnk3(int n, int k) 
{    
	const int maxn = n;
	int C[maxn+1][maxn+1];    
	for (int i=0; i<=maxn; ++i) 
	{        
		C[i][0] = C[i][i] = 1;        
		for (int j=1; j<i; ++j)            
		C[i][j] = C[i-1][j-1] + C[i-1][j];    
	}    
	return C[n][k]; 
}

int main() 
{    
    int i, j, N_len, digits_count = 0;
    int digit_zero = 0;
    int result;
    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char N[100];
    scanf("%s", N);
    N_len = strlen(N);
    printf("%d\n", N_len);
    if (N_len < 3)
    { 
		printf("%d", 0);
		return 0;
	}
    
    for (j = 0; j<10; j++)
    {
		for (i = 0; i<N_len; i++)
		{
			if (N[i] == digits[j])
			{
				if (N[i] == '0') digit_zero = 1;
				digits_count = digits_count + 1;
				break;
			} 
		}
	}
	printf("%d\n", digits_count);
	
    if (digits_count == 1)
    { 
		printf("%d", 1);
		return 0;
	}	
    if ((digits_count == 2)&&(digit_zero == 1))
    { 
		printf("%d", 1);
		return 0;
	}
    //if (digits_count == 2)
    //{ 
		result = cnk2(digits_count, 3);
		printf("%d", result);
		return 0;
	//}
}
