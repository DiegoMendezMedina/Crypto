#include "../../lib/decode.h"

/**
 * this program receives the hex code from the standard input
 * and decodes it.
 *
 * @author Diego Méndez Medina 
 * contact: diegomm@ciencias.unam.mx
 *          @DiegoMendezMedina on github          
 */

int read_hex(char*);

/* hex decoder*/
int main()
{
  int i;
  char hex[MAXLINE], *text;

  i = read_hex(hex);
  
  if(i<0)
    return -1;
  
  text = decode_hex(hex, i);
  printf("%s\n", text);
  free(text);
  return 0;
}

/**
 * read_hex: reads from the standard input and 
 *           saves its hexadecimal value into hex.
 *
 * @param hex, char*. Where the proper value will be stored.
 * 
 * @return 0 if the Input is a proper hex string representation.
 * @return -1 if not.
 */
int read_hex(char* hex)
{
  int t, i;
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
      case '\n':
	return i;
      default:
	printf("error: string received is not in hex form\n");
	return -1;
      }
    i++;
  }
  
  if(i==MAXLINE){
    printf("error: input exceeded MAXLINE\n");
    return -1;
  }
  
  return i;
}
