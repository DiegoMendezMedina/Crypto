#include "encode.h"

/**
 * For documentation see encode.h
 */

/***** HEX *****/

char* encode_hex(char *p, int length)
{
  char aux; 
  int i, j;
  char *hex = malloc(2*length);
  unsigned int mask = 15;

  for(i = 0, j = 0; i < length; i++){
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

void print_hex(char *hex, int size)
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

/***** B64 ****/
unsigned get_64mask(int cont)
{
  if(cont==2)
    return 3;
  else if(cont==4)
    return 15;
  return 63;
}


char* encode_b64(char* text, int length)
{
  int i, j, bl;
  char *b64;
  unsigned aux, mask, cont, prev, val;
  
  bl = ceil(length*4/3);     // base64 length = ceil(n*4/6)
  b64 = calloc(bl, 1);
  mask = 3;                // mask to get the bits that are not used in a sextet
  cont = 2;                // first n bits to form the next sexteto
  prev = 0;                // next value of the n=cont bits that were not used in the last sextet
  i = j = 0;

  while(j<=bl){
  
    if(i<length){
      aux = text[i] & mask;
      val = text[i] >> cont;
      
      if(cont != 2)
	val += prev;
      else if(prev != 0) // for every cont = 2 except the first
	  b64[j++] = prev;
      
      b64[j++] = val;
      prev = aux<<(6-cont);
    }
    else{
      aux = (cont==2)? 0 : cont;
      b64[j++] = (text[length-1]<<aux)&63;
    }
    
    cont = (cont==6)? 2:((cont+2)%8);  
    mask = get_64mask(cont);
    i++;
  }
  return b64;
}

void print_b64(char* b64, int size)
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


/*****  XOR *****/

char* xor(char* d1, char* d2, int length)
{
  int i, j, sum;
  char *xor, a, b, mask;

  xor = malloc(length);

  sum = 0;
  for(j = 0; j < length; xor[j++] = sum, sum = 0)
    for(i = 7; i>=0; i--){
      mask = 1<<i;
      a = d1[j] & mask;
      b = d2[j] & mask;
      if(a!=b)
	sum += mask;
    }
  
  xor[j] = '\0';
  return xor;
}
