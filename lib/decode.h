#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Cryptographic decoding functions.
 *
 * @author Diego Méndez Medina.
 */

#ifndef MAXLINE
#define MAXLINE 10000
#endif

#ifndef MAXBUFF
#define MAXBUFF 10000
#endif

/***** HEX *****/

/* decodes the hex code and returns it as a string*/
char* decode_hex(char* hex, int size);


/** 
 * string_to_hex: gets the proper value of the string and stores it in hex.
 * @param s, string: string hex representation.
 * @param hex, array of bytes: array where the proper hex value will be stored.
 * @param length, 
*/
void string_to_hex(char *s, char *hex, int length);

/**
 * hamming_distance: 
 * 
 * @params s1, s2: strings.
 * @return -1 if the lengths of the strings
 *         are different, otherwise the hamming
 *         distance, >= 0.
 **/
/*
int hamming_distance(char *s1, char *s2)
{
  int dis, i, l1, l2, j;
  unsigned char mask, c1, c2;
  
  l1 = strlen(s1);
  l2= strlen(s2);

  if(l1 != l2){
    printf("Strings with different length\n");
    return -1;
  }

  dis = 0;
  for(i = 0; i < l1; i++)
    for(j = 0; j < 8; j++){
      mask = 1 << j;
      c1 = s1[i] & mask;
      c2 = s2[i] & mask;
      if(c1 != c2)
	dis++;
    }
  
  return dis;
}
*/
