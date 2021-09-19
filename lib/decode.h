#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Cryptographic decoding functions.
 *
 * Diego Méndez Medina.
 */

/* decodes the hex code and returns it as a string*/
char* decode_hex(char* hex, int size)
{
  int i, j;
  unsigned mask = 15;
  char * text = malloc(size/2);
  
  j = 0;
  for(i = 0; j < size; i++){
    int aux = hex[j++]<<4;        
    int aux2 = hex[j++] &mask;
    text[i] = aux+aux2;
  }
  text[i] = '\0';
  return text;
}

/* gets the proper value of the string and stores it in hex*/
void string_to_hex(char *s, char *hex, int length)
{
  int t, i;

  i = 0;
  while((t = s[i]) != '\0'){
    if(isdigit(t))
      hex[i] = t-'\0'-48;
    else
      switch(toupper(t)){
      case 'A':
	hex[i] = 10;
	break;
      case 'B':
	hex[i] = 11;
	break;
      case 'C':
	hex[i] = 12;
	break;
      case 'D':
	hex[i] = 13;
	break;
      case 'E':
	hex[i] = 14;
	break;
      case 'F':
	hex[i] = 15;
	break;
      case 0:
	hex[i] = 0;
	break;
      }
    i++;
  }
}
