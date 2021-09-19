#include <stdio.h>
#include <stdlib.h>
#include "../../lib/encode.h"
#include "../../lib/decode.h"
#include <string.h>

/**
 * this progams reads an hex encodes string from the standard input
 * that has been xor'd against a single character
 *
 * Diego Méndez Medina
 */

#define MAXLINE 1000

/* structure that helps us get the correct plain text*/
struct Analyzer{
  char alphabet[27];
  int  frecuency[27];
  int numlet;
};
  
char* xor_byte(char* , char);
void print_analyzer(struct Analyzer* );
void clear_frecuency(struct Analyzer* );
void get_frecuency(struct Analyzer*, char*);
void qsort_analyzer(struct Analyzer* , int, int);
void swap(struct Analyzer* , int , int );
int get_analyzer_value(struct Analyzer*, char*);

/* single-byte XOR cipher*/
int main()
{
  int i, cont, aux, key;
  char s[MAXLINE], *xor, hex[MAXLINE], *decode, higher[256][MAXLINE], r;
  
  struct Analyzer analyzer = {{'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '}, {0}, 0};
  
  i = 0;
  while((s[i] = getchar()) != EOF && i++ < MAXLINE)
    ;
  if(s[i-1] == '\n')
    i--;
  s[i] = '\0';

  string_to_hex(s, hex, i);
  decode = decode_hex(hex, i);
  for(int j = 0; j < 256; j++)
    higher[j][0] = '\0';
  
  cont = 0;
  for(int j = 0; j < 256; j++){
    xor = xor_byte(decode, (char) j);
    get_frecuency(&analyzer, xor);
    qsort_analyzer(&analyzer,0, 25);
    aux = get_analyzer_value(&analyzer, xor);
    
    if(aux > cont){
      cont = aux;
      key = j;
    }
    clear_frecuency(&analyzer);
  }

  xor = xor_byte(decode, key);
  printf("%s\n", xor);
  
  free(decode);
  free(xor);
}

/* xor_single_byte: encrypts or decrypts the string received with the byte key 
                    and returns it. s has to be a proper(decoded) string.*/
char* xor_byte(char* s, char key)
{
  int i, j, length;
  unsigned int sum;
  char *xored, mask, a, b;

  length = strlen(s);
  xored = malloc(length);
  
  sum = 0;
  for(i = 0; i < length; xored[i++] = sum, sum = 0)
    for(j = 7; j>=0; j--){
      mask = 1<<j;
      a = s[i] & mask;
      b = key & mask;
      if(a!=b)
	sum += mask;
    }
  xored[i] = '\0';
  
  return xored;
}

/* clear_frecuency: sets every analyer.frecuency item to zero */
void clear_frecuency(struct Analyzer* an)
{
  for(int i = 0; i < 27; i++)
    an->frecuency[i] = 0;
  an->numlet = 0;
}

/* printing the analyzer */
void print_analyzer(struct Analyzer* an)
{
  for(int i = 0; i < 27; i++)
    printf("%c: %d\n", an->alphabet[i], an->frecuency[i]);
  printf("Number of letter: %d\n", an->numlet);
}

/* get_frecuency: gets the english alphabet character frecuency appeared on s*/
void get_frecuency(struct Analyzer* an, char *s)
{
  int i, j;

  for(i = 0; i < strlen(s); i++)
    if(s[i] == ' ')
      an->frecuency[26]++;
    else if(isalpha(s[i]))
      for(j = 0; j < 26; j++)
	if(tolower(s[i]) == an->alphabet[j]){
	  an->frecuency[j]++;
	  an->numlet++;
	  break;
	}
}

/* qsort_analyzer: sorts the analyzer decreasingly */ 
void qsort_analyzer(struct Analyzer* an, int left, int right)
{
  int i, last;

  if(left >= right)
    return;

  swap(an, left, (left+right)/2);
  
  last = left;
  for(i = left+1; i <= right; i++)
    if(an->frecuency[i] > an->frecuency[left])
      swap(an, ++last, i);
  
  swap(an, left, last);
  qsort_analyzer(an, left, last-1);
  qsort_analyzer(an, last+1, right);
}

/* swap: swaping elements in the analyzer */
void swap(struct Analyzer* an, int i, int j)
{
  int itemp;
  char ctemp;

  ctemp = an->alphabet[i];
  itemp = an->frecuency[i];
  
  an->alphabet[i] = an->alphabet[j];
  an->frecuency[i] = an->frecuency[j];
  an->alphabet[j] = ctemp;
  an->frecuency[j] = itemp;
}

/* get_analyzer_value : sets a value to the character frecuency */
int get_analyzer_value(struct Analyzer* an, char*s)
{
  int cont, i;
  char aux, prev;
  
  cont = 0;
  if(isupper(s[0]))
    cont += 2;
  
  for(i = 0; i < 26; i++){
    aux = an->alphabet[i];
    if(i>=1)
      prev = an->alphabet[i-1];
    // ETAOIN SHRDLU
    if(i<= 11)
      if(aux == 'e' || aux == 't' || aux == 'a' || aux == 'o' || aux == 'i'
	 || aux == 'n' || aux == 's' || aux == 'h' || aux == 'r' || aux == 'd'
	 || aux == 'l' || aux == 'u')
	cont ++;
      else if (aux == 'z' || aux == 'x' || aux == 'q' || aux == 'j')
	cont -= 3;
    if(i>=22)
      if(aux == 'z' || aux == 'x' || aux == 'q' || aux == 'j')
	cont ++;
      else if (aux == 'e' || aux == 't' || aux == 'a' || aux == 'o')
	cont -= 3;

    // most common silabes:
    if(i>=1){
      if(aux == 'h' && prev == 't')
	cont+=2;
      if(aux == 'r' && prev == 'e')
	cont += 2;
      if(aux == 'n' && (prev == 'o' || prev == 'a'))
	cont += 2;
      
      // least common silabes:
      if(aux == prev == 's')
	cont --;
      if(aux == prev == 'e')
	cont --;
      if(aux == prev == 't')
	cont --;
      if(aux == prev == 'f')
	cont --;
    }
  }

  // percent of characters in terms of string length
  if(3*strlen(s)/4 <= an->numlet+an->alphabet[26])
    cont += 5;
  return cont;
}

