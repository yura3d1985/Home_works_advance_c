#include <math.h>
#include <string.h>
#include <stdio.h> 
  
#define SIZE 1000

void zFunction2 (char *s, int z[]) 
{    
	int n = strlen(s);    
	for (int i=1, l=0, r=0; i<n; ++i) 
	{        
		if (i <= r)            
		z[i] = fmin(r-i+1, z[i-l]);        
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];        
		if (i+z[i]-1 > r)            
		l = i,  r = i+z[i]-1;    
	} 
}

int main() 
{    
    char word_1[SIZE] = {0}; 
    char word_2[SIZE] = {0};
    char S[SIZE+SIZE+1] = {0};
    
    char word_tmp[SIZE] = {0}; 
    
    int z[SIZE+SIZE+1] = {0};
    
    int max_len_1 = 0;
    int max_len_2 = 0;
    int i, j, k;
    
    scanf("%s", word_1); 
    scanf("%s", word_2);
    
    size_t w1_len = strlen(word_1);
     
    size_t w2_len = strlen(word_2); 
    
    for (i = 0; i < w1_len; i++)
    {
		for(j = 0; j <= i; j++) word_tmp[j] = word_1[j];
		
		size_t plen = strlen(word_tmp); 
		
		sprintf(S,"%s#%s",word_tmp,word_2);
		
		zFunction2(S,z);
		
		for(k = (w2_len-plen); k < w2_len; k++)    
		if(z[k+plen+1] == plen) max_len_1 = z[k+plen+1];
	}
		 
	memset(S, 0, sizeof S);
	memset(word_tmp, 0, sizeof word_tmp);
	memset(z, 0, sizeof z);
	
	for (i = 0; i < w2_len; i++)
    {
		for(j = 0; j <= i; j++) word_tmp[j] = word_2[j];
		
		size_t plen = strlen(word_tmp); 
		
		sprintf(S,"%s#%s",word_tmp,word_1);
		 
		zFunction2(S,z); 
		
		for(k = (w1_len-plen); k < w1_len; k++)    
		if(z[k+plen+1] == plen) max_len_2 = z[k+plen+1];
	}
		
	printf("%d %d", max_len_1, max_len_2); 
}
