#include <stdio.h>
#include <stdlib.h>

/**
 * this program encodes the string received on the standard input
 *
 * @author Diego Méndez Medina 
 * contact: diegomm@ciencias.unam.mx
 *          @DiegoMendezMedina on github          
 */

#define MAXLINE 1001                //max length of the input

char* encode_hex(char*, int);     
void pretty_printing(char*, int);

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
  pretty_printing(hex, 2*i);
  free(hex);
  return 0;
}

/* encodes string into hex and returns it*/
char* encode_hex(char *p, int size)
{
  char aux; 
  int i, j;
  char *hex = malloc(2*size);
  unsigned int mask = 15;

  for(i = 0, j = 0; i < size; i++){
    aux = *p;
    /* In case the byte is 0000, '\0' will be stored on hex.
       But hex is not consider a string so that '\0' is not the end of 
       the hex representation, consider this during the printing, take
       in mind the size of the initial string. */
    hex[j++] = aux >> 4;
    hex[j++] = aux & mask;
    p++;
  }

  return hex;
}


/* printing the bytes */
void pretty_printing(char *hex, int size)
{
  int i;

  for(i = 0; i < size; i++)
    if(hex[i]>0 && hex[i] < 10)
      printf("%d", hex[i]);
    else
      switch(hex[i]){
      case'\0':
	printf("0");
	break;
      case 10:
	printf("A");
	break;
      case 11:
	printf("B");
	break;
      case 12:
	printf("C");
	break;
      case 13:
	printf("D");
	break;
      case 14:
	printf("E");
	break;
      case 15:
	printf("F");
	break;
      default:
	printf("?");
	break;
      }
  printf("\n");
}

