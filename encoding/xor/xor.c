#include <stdio.h>
#include "../../lib/encode.h"
#include "../../lib/decode.h"

/**
 * takes two equal-length buffers(in hex) and produces their XOR combination and 
 * prints its ascii and hex value.
 * 
 * Diego Méndez Medina.
 */

#define MAXBUFF 1000

char* XOR(char* , char*, int);

/* Xor combinator*/
int main()
{
  int i, j;
  char buff[MAXBUFF], hex[MAXBUFF], *decode1, *decode2;
  char *xor, *r;
  
  i = j = 0;
  
  while((buff[i] = getchar()) != '\n' && i++ < MAXBUFF)
    ;
  buff[i] = '\0';
  string_to_hex(buff, hex, i);
  decode1 = decode_hex(hex, i);

  while((buff[j] = getchar()) != '\n' && j++ < MAXBUFF)
    ;
  buff[j] = '\0';
  string_to_hex(buff, hex, j);
  decode2 = decode_hex(hex, j);

  if(i != j){
    printf("error: buffers of different length\n");
    return 0;
  }

  xor = XOR(decode1, decode2, i);
  r = encode_hex(xor, i);

  print_hex(r, i);
  printf("%s\n", xor);
  
  free(decode1);
  free(decode2);
  free(xor);
  free(r);
  return 0;
}

/* takes two string with same length and returns it's xor combination as a string */
char* XOR(char *d1, char *d2, int length)
{
  int i, j, sum;
  char *xor, a, b, mask;
  
  xor = malloc(length);

  sum = 0;
  for(j = 0; j < length; xor[j++] = sum, sum = 0)
    for(i = 6; i>=0; i--){
      mask = 1<<i;
      a = d1[j] & mask;
      b = d2[j] & mask;
      if(a!=b)
	sum += mask;
    }
  
  xor[j] = '\0';
  return xor;
}