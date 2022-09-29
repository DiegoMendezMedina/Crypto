#include "decode.h"

/**
 * See decode.h for documentation
 */


char* decode_hex(char* hex, int size)
{
  int i, j;
  unsigned mask = 15;
  char * text = calloc((size/2)+1, 1);
  
  j = 0;
  for(i = 0; j < size; i++){
    int aux = hex[j++]<<4;        
    int aux2 = hex[j++] &mask;
    text[i] = aux+aux2;
  }

  text[i] = '\0';
  return text;
}

