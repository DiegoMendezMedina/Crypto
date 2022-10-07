#include <ctype.h>
#include "encode.h"

/**
 * character frecuency functions
 * 
 * Diego Méndez Medina
 */

/* structure that helps us get the correct plain text*/
struct Analyzer{
  char alphabet[27];
  int  frecuency[27];
  int numlet;
};

/* clear_frecuency: sets every analyer.frecuency item to zero */
void clear_frecuency(struct Analyzer* an)
{
  int aux;

  aux = 97;
  for(int i = 0; i < 26; i++){
    an->frecuency[i] = 0;
    an->alphabet[i] = aux+i;
  }
  an->frecuency[26] = 0;
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
  for(i = 0; i < 26; i++)
    if(an->frecuency[i] == 0)
      an->alphabet[i] = ' ';
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
	cont -= 2;
    if(i>=22)
      if(aux == 'z' || aux == 'x' || aux == 'q' || aux == 'j')
	cont ++;
      else if (aux == 'e' || aux == 't' || aux == 'a' || aux == 'o')
	cont -= 2;

    // most common silabes:
    if(i>=1){
      if(aux == 'h' && prev == 't')
	cont+=2;
      if(aux == 'r' && prev == 'e')
	cont += 2;
      if(aux == 'n' && (prev == 'o' || prev == 'a'))
	cont += 2;
      
      // least common silabes:
      if(aux == prev && aux == 's')
	cont --;
      if(aux == prev && aux == 'e')
	cont --;
      if(aux == prev && aux == 't')
	cont --;
      if(aux == prev && aux == 'f')
	cont --;
    }

    if(isdigit(aux))
      cont--;
    if(!isalpha(aux))
      cont--;
  }

  // percent of characters in terms of string length
  if(3*strlen(s)/4 <= an->numlet+an->alphabet[26])
    cont += 5;
  return cont;
}

/* best_key: returns the best key */
char best_key(char* decode, struct Analyzer* analyzer)
{
  int cont, aux, key;
  char *xor;
  
  cont = 0;
  for(int j = 0; j < 256; j++){
    xor = xor_byte(decode, (char) j);
    get_frecuency(analyzer, xor);
    qsort_analyzer(analyzer,0, 25);
    aux = get_analyzer_value(analyzer, xor);
    
    if(aux > cont){
      cont = aux;
      key = j;
    }
    clear_frecuency(analyzer);
  }
  free(xor);
  return key;
}
