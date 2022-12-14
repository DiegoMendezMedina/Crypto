#include "../../lib/encode.h"
#include "../../lib/decode.h"

/**
 * takes two equal-length buffers(in hex) and produces their XOR combination and 
 * prints its ascii and hex value.
 * 
 * Diego Méndez Medina.
 */

/* Xor combinator*/
int main()
{
  int i, j;
  char buff[MAXBUFF], hex[MAXBUFF], *decode1, *decode2;
  char *xor_encode, *r;
  
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
    return 1;
  }

  xor_encode = xor(decode1, decode2, ceil(i/2.0));
  r = encode_hex(xor_encode, i);

  printf("xor:");
  print_hex(r, i);
  printf("hex to string:%s\n", xor_encode);
  
  free(decode1);
  free(decode2);
  free(xor_encode);
  free(r);
  return 0;
}
