#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/encode.h"
#include "../../lib/decode.h"

/**
 * This programs encrypts the file received using 
 * repeating-key XOR with the key received on the standard 
 * input.
 */

#define MAXLENGTH 1000

char* rep_xor(char*, char *);

int main(int argc, char* argv[])
{
  char in[MAXLENGTH];
  char key[] = "ICE", *xor, *r;

  int j = 0;
  while((in[j] = getchar()) != EOF)
    j++;
  in[j-1] = '\0';
  j--;
  
  xor = rep_xor(in, key);
  r = encode_hex(xor, 2*j);
  print_hex(r, 2*j);

  free(xor);
  free(r);
  return 0;
}

char* rep_xor(char* src, char* key)
{
  int i, j, length, sum, ik, l_key;
  char mask, a, b, *xor;

  l_key = strlen(key);
  length = strlen(src);
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
