#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#ifndef MAXLINE
#define MAXLINE 10000
#endif

#ifndef MAXBUFF
#define MAXBUFF 10000
#endif

/**
 * Cryptographic encoding functions.
 *
 * @author Diego Méndez Medina.
 */

/********************** b2 **********************/

/********************** HEX **********************/

/**
 * encode_hex: encodes string and returns it 
 *            as an array of bytes.
 * 
 * @param p, string: string to encode.
 * @param length, int: length of the string;
 * 
 */
char* encode_hex(char *p, int length);


/**
 * print_hex: prints the representation of an 
 *            array of bytes encodes in hex.
 *
 * @param hex, array of bytes: bytes to print.
 * @param size, int. size of the array.
 */
void print_hex(char *hex, int size);


/********************** b64 **********************/
/**
 * get64mask: returns the int value that will mask the bit to obtain the sextet 
 *
 * @param cont, int. current iteration.
 */
unsigned get_64mask(int cont);

/**
 * encode_b64: encodes text, an string, to base 64 and returns it
 * 
 * @param text, string: string to encode.
 * @param length: length of the string.
 * 
 * @return char*, array of bytes: B64 encode.
 */
char* encode_b64(char* text, int length);

/**
 * print_b63: prints the b64 representation of the bytes 
 *
 * @param b63, char*: array of bytes.
 * @param size, int. size of the array.
 */
void print_b64(char* b64, int size);

/********************** XOR **********************/

/**
 * xor: takes two string with same length and returns it's xor combination as 
 *      an array of bytes.
 * @param d1, string:  string to xor #1.
 * @param d2, string:  string to xor #2.
 * @param length, int: length of both d1 and d2.
*/
char* xor(char* d1, char* d2, int length);
