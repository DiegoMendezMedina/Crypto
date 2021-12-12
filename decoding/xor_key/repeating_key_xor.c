#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/encode.h"
#include "../../lib/decode.h"

/**
 * This programs decodes the hex string received on the terminal
 * by repeating-key XOR with the key, received on the standard 
 * input.
 * Proper execution: ./exe -p password 
 */

#define MAXLENGTH 10000
#define MAXPSWD 100

char* rep_xor(char*, char *, int);

/* Decoding Reapeating key xor */
int main(int argc, char* argv[])
{
  int i, j;
  char in[MAXLENGTH], hex[MAXLINE], *xor, *r;
  
  if(argc < 3){
    printf("error: the password may be entered with the -p flag.");
    printf("\n \t Ej: ./exe -p password\n");
    return 0;
  }

  i = 0;
  while(argv[i][0] != '-')
    i++;
  
  if(argv[i][1] != 'p'){
    printf("error: flag not recognized\n");
    return 0;
  }
  if(i == argc-1){
    printf("error: the password may be entered after the -p flag\n");
    printf("\n \t Ej: ./exe -p password\n");    
    return 0;
  }

  
  j = 0;
  while((in[j] = getchar()) != EOF)
    j++;
  in[j-1] = '\0';
  j--;
  
  string_to_hex(in, hex, j);
  r = decode_hex(hex, j);
  xor = rep_xor(r, argv[i+1], (j/2));
  printf("%s\n", xor);
  
  free(xor);
  free(r);
  return 0;
}

/**
 * rep_xor: Decodes src with xor repeating the key.
 *           
 * Note: length is necesary since src may have
 *        0's values. (strlen won't work)
 */
char* rep_xor(char* src, char* key, int length)
{
  int i, j, sum, ik, l_key;
  char mask, a, b, *xor;

  l_key = strlen(key);
  xor = calloc(2*length, 1);
  
  sum = 0;
  for(i = 0 ; i < length; xor[i++] = sum,sum = 0){
    ik = i%l_key;
    for(j = 7; j>=0; j--){
      mask = 1<<j;
      a = src[i] & mask;
      b = key[ik] & mask;
      if(a!=b)
	sum += mask;
    }
  }
  
  if(i<length+1)
    xor[i] = '\0';
  return xor;
}
