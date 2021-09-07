#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * this program receives the hex code from the standard input as string
 * and decodes it.
 *
 * @author Diego Méndez Medina 
 * contact: diegomm@ciencias.unam.mx
 *          @DiegoMendezMedina on github          
 */

#define MAXLINE 1000 // max length of the input

char* decode_hex(char*, int);

/* hex decoder*/
int main()
{
  int t, i;
  char hex[MAXLINE], *text;

  i = 0;
  while((t = getchar()) != EOF && i<MAXLINE){
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
  
  if(i==MAXLINE){
    printf("error: input exceeded MAXLINE\n");
    return 0;
  } 
  if(hex[i-1] == '\n') // Deleting the new line from the standard input
    i--;
  
  text = decode_hex(hex, i);
  printf("%s\n", text);
  free(text);
  return 0;
}

/* decodes the hex code and returns it as a string*/
char* decode_hex(char* hex, int size)
{
  int i, j;
  unsigned mask = 15;
  char * text = malloc((size)/2);
  
  j = 0;
  for(i = 0; i <(size-1)/2; i++){
    int aux = hex[j++]<<4;        
    int aux2 = hex[j++] &mask;
    text[i] = aux+aux2;
  }
  text[i] = '\0';
  return text;
}
