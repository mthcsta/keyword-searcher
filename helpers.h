#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#ifndef HELPERS_H
#define HELPERS_H

void wordtolowercase(char *s);
int tokenizer(char *inputfile_name, char *outputfile_name);
int max(int a, int b);

#endif // HELPERS_H
