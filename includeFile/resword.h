/********************** resword.h ******************/
#include <stdlib.h>
#define RESWORDMAX 100
char reswords[RESWORDMAX][20] =
  {
    // storage-class-specifier
    "auto", "register", "static", "extern", "typedef",
    // type-specifier
    "void", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
    // struct-or-union
    "struct", "union", 
    // statement
    "switch", "for", "goto", "continue", "return",
    // Plone Reserve Word
  "BEGIN","CALL","CONST","DO","END","IF","PROCEDURE",
  "PROGRAM","READ","THEN","VAR","WHILE","WRITE",""
  };
int isResword(char *s)
{
  int i;
  for (i=0; i<RESWORDMAX; i++)
  {
    if (strcmp(s, reswords[i])==0) return i;
  }
  return -1;
}
