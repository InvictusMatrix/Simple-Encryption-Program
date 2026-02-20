#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Kelvin Bhual
| Language: c, c++, Java, go, python, rust
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| rustc pa01.rs
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or rust -> ./pa01 kX.txt pX.txt
| or python -> python3 pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 2/23/2025 at 11:59pm
+===========================================================================*/



int main(int argc, char **argv)
{
  int i, j, k;
  int ciphsize;
  FILE *keyfile;
  FILE *plaintext;
  char matrix[3];
  char ptxtChar;
  char ptxtStr[10000];
  char ctxtStr[10000];
  int key;
  int ptxtIndex = 0;
  int padLen = 0;
  
  // Open key and plaintext files
  keyfile = fopen(argv[1], "r");
  if(keyfile == NULL)
  {
    printf("Could not open key file\n");
    fclose(keyfile);
    return 1;
  }
  
  plaintext = fopen(argv[2], "r");
  if(plaintext == NULL)
  {
    printf("Could not open plaintext file\n");
    fclose(plaintext);
    return 1;
  }
  
  // Store the first line of key file as an integer
  fgets(matrix, sizeof(matrix), keyfile);
  if(matrix == NULL)
  {
    printf("Key matrix size value could not be converted to integer\n");
    return 1;
  }
  else
  {
    ciphsize = atoi(matrix);
    if(ciphsize < 1 || ciphsize > 10)
    {
      printf("Key matrix size value outside of limits\n");
      return 1;
    }
  }
  
  // Key matrix variable initalized after key file is opened and size is stored in ciphsize   
  int keymtx[ciphsize][ciphsize];
     
  // Moves key file content into key matrix and prints key matrix
  for(i = 0; i < ciphsize; i++)
  {
    for(j = 0; j < ciphsize; j++)
    {
      fscanf(keyfile, "%d", &keymtx[i][j]);
    }
  }
  
  printf("\nKey matrix:\n");
  
  for(i = 0; i < ciphsize; i++)
  {
    for(j = 0; j < ciphsize; j++)
    {
      printf("%4d", keymtx[i][j]);
    }
    printf("\n");
  }
  
  // Checks plaintext file for alphabetic letters and stores them in string variable in lower case while counting the length of the string
  printf("\nPlaintext:\n");
  while((ptxtChar = fgetc(plaintext)) != EOF)
  {
    if(isalpha(ptxtChar))
    {
      ptxtStr[ptxtIndex] = tolower(ptxtChar);
      ptxtIndex++;
    }
  }
  
  ptxtStr[ptxtIndex] = '\0';
  
  // Checks if plaintext needs padding and pads the end before printing the plaintext
  padLen = ciphsize - (ptxtIndex % ciphsize);
  if(padLen != ciphsize)
  {
    for(i = 0; i < padLen; i++)
    {
      ptxtStr[ptxtIndex] = 'x';
      ptxtIndex++;
    }
    ptxtStr[ptxtIndex] = '\0';
  }
  
  for(i = 0; i < ptxtIndex; i++)
  {
    printf("%c", ptxtStr[i]);
    if((i + 1) % 80 == 0)
    {
      printf("\n");
    }
  }
  
  printf("\n\n");
  
  // Encrypts the plaintext and prints the ciphertext
  printf("Ciphertext:\n");
  
  for(i = 0; i < ptxtIndex; i += ciphsize)
  {
    for (j = 0; j < ciphsize; j++)
    {
      key = 0;
      for(k = 0; k < ciphsize; k++)
      {
        key += keymtx[j][k] * (ptxtStr[i + k] - 'a');
      }
      ctxtStr[i + j] = (key % 26) + 'a';
    }
  }
  
  ctxtStr[ptxtIndex] = '\0';
  
  for(i = 0; i < ptxtIndex; i++)
  {
    printf("%c", ctxtStr[i]);
    if((i + 1) % 80 == 0)
    {
      printf("\n");
    }
  }
  
  printf("\n\n");
  
  fclose(keyfile);
  fclose(plaintext);
  
  return 0;
}



/*=============================================================================
| I Kelvin Bhual (ke203968) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/