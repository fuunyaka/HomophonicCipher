#ifndef HOMOPHONIC_H
#define HOMOPHONIC_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAXIMUM_NUMLEN 20
typedef char num[MAXIMUM_NUMLEN];

typedef struct{
    int n; // number of numbers on the given line used for substitution for the homophonic cipher.
    num *numbers; // actual array of numbers used for subsitution of each letter.
}KType;

typedef KType key[26];

void readKey(FILE *FileWithKey, key KeyArray);

//returns the pointer to a string of nums used to replace a particular character. picked randomly.
char *get_Number(char letter, key KeyArray);

//performs linear search to return correspondng character, else returns 0.
char getLetter(char *number, key KeyArray);

void generateKey(FILE *FileWithKey ,key KeyArray);

//This does a homophonic encryption, one letter is substituted with any of the numbers or combination of numbers at random
void encryptFile(FILE *PlainTextFile, FILE *En_Dec_Text_File, key KeyArray);


// decryptFile decrypts PlainTextFile and writes back to En_Dec_Text_File


void decryptFile(FILE *PlainTextFile, FILE *En_Dec_Text_File, key KeyArray);


#endif // HOMOPHONIC_H
