#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for ceil

/**
 * this program encodes the string received of the standard input to
 * base 64
 *
 * @author Diego Méndez Medina 
 * contact: diegomm@ciencias.unam.mx
 *          @DiegoMendezMedina on github          
 */

#define MAXLINE 1000

char* encode_b64(char*, int);
unsigned getmask(int);
void pretty_printing(char*, int);

/* b64 encoder */
int main()
{
  char text[MAXLINE], *b64;
  int i;
  
  i= 0;
  
  while((text[i]=getchar()) != EOF && i++<MAXLINE)
    ;
  if(text[i-1]=='\n') //Erasing last new line taken from the standard input
    i--;
  if(i==MAXLINE)
    printf("error: MAXLINE exceeded.\n\t Try with a smaller input");
  
  b64 = encode_b64(text, i);
  pretty_printing(b64, i);
  free(b64);
  return 0;
}

/* encode_b64: encodes text to base 64 and returns it*/
char* encode_b64(char* text, int size)
{
  int i, j, bl;
  char *b64;
  unsigned aux, mask, cont, prev, val;
  
  bl = ceil(size*4/3.0);     // base64 length = ceil(n*8/6)
  b64 = calloc(bl, 1);
  mask = 3;                // mask to get the bits that are not used in a sextet
  cont = 2;                // first n bits to form the next sexteto
  prev = 0;                // next value of the n=cont bits that were not used in the last sextet
  i = j = 0;

  while(j<bl){
  
    if(i<=size){
      aux = text[i] & mask;
      val = text[i] >> cont;
      
      if(cont != 2){
	val += prev;

      }
      else if(prev != 0) // for every cont = 2 except the first
	  b64[j++] = prev;

      if(j<bl)
	b64[j++] = val;
      prev = aux<<(6-cont);
    }
    else{
      aux = (cont==2)? 0 : cont;
      b64[j++] = (text[size-1]<<aux)&63;
    }
    
    cont = (cont==6)? 2:((cont+2)%8);  
    mask = getmask(cont);
    i++;
  }
  return b64;
}

/* getmask: returns the int value that will mask the bit to obtain the sextet */
unsigned getmask(int cont)
{
  if(cont==2)
    return 3;
  else if(cont==4)
    return 15;
  return 63;
}

/* Printing the bytes */
void pretty_printing(char* b64, int size)
{
  int i = ceil(size*4/3.0);

  for(int j = 0; j < i; j++){
    if(b64[j] <= 25)
      printf("%c", b64[j]+65);
    else if(b64[j] <= 51)
      printf("%c", b64[j]+71);
    else if(b64[j] <= 61)
      printf("%c", b64[j]-4);
    else if(b64[j] == 62)
      printf("%c", 42);
    else
      printf("%c", 47);
  }
  printf("\n");
}

