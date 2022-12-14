#include <stdio.h>
#include <stdlib.h>
#include "../../lib/decode.h"

/**
 * this program encodes the string received on the standard input
 *
 * @author Diego Méndez Medina 
 * contact: diegomm@ciencias.unam.mx
 *          @DiegoMendezMedina on github          
 */

#define MAXLINE 1001                //max length of the input

int main()
{
  char text[MAXLINE], *hex;
  int i;
  
  i = 0;
  while((text[i]=getchar()) != EOF && i++<MAXLINE-1)
    ;  
  /* text[i] = '\0';  if text would be printed*/
  if(i == MAXLINE-1){
    printf("error: input exceeded MAXLINE\n");
    return 0;
  }
  if(text[i-1] == '\n') /* Deleting the last new line taken 
			   from the standard input */
    i--;
  
  hex = encode_hex(text, i);
  print_hex(hex, 2*i);
  free(hex);
  return 0;
}
