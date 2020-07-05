/********************** scanner.h ********************/
#include <stdio.h>
#include <stdlib.h>
#include "sym.h"
#include "symbol.h"
#include <string>
#include "symname.h"
#include "iostream"
using namespace std;
int nextChar;
int cp = 0;
int linelen = 0;
int linenum = 0;
char line[512];
FILE *sourcefile;
void advance()
{
  cp++;
  if (cp < linelen)
    nextChar = line[cp];
  else
  {
    if (feof(sourcefile))
    {
      linelen = 0;
      nextChar = -1;
    }
    else
    {
      if (fgets(line, 512, sourcefile) != NULL)
      {
        linelen = strlen(line);
        linenum++;
        cp = 0;
        nextChar = line[cp];
        printf("%4d %s", linenum, line);
      }
    }
  }
}
struct symbolTag *nextToken()
{
  static char s[128] = "";
  int n=0;
  symnameinit();
  while (1)
  {
    if ((nextChar>='a' && nextChar<='z') ||
        (nextChar>='A' && nextChar<='Z'))
    {
      do
      {
        s[n++]=nextChar;
        advance();
      } while ((nextChar >= 'a' &&  nextChar <= 'z') ||
               (nextChar >= 'A' && nextChar <= 'Z') ||
               (nextChar>='0' && nextChar<='9'));
      s[n]='\0';
      bool findResFlag = false;
      int findResValue = 2;
      for (int i = 0; i < symSYMMAX; i++){
        // For Debug Reserve Word
        // cout << s << " " << names[i] << endl;
        if (strcmp(s,names[i]) == 0){
          findResValue = i;
          findResFlag = true;
        }
      }
      // Debug Reserve Flag and the value
      // cout << findResFlag << " " << s << " " << findResValue << endl;
      if (findResFlag == false)
        return newSymbol(symIDENTIFIER,linenum,cp,s);
      else
        return newSymbol(findResValue,linenum,cp,s);

    }
    else if (nextChar>='0' && nextChar<='9')
    {
      do
      {
        s[n++]=nextChar;
        advance();
      } while (nextChar >= '0' && nextChar <= '9');
      s[n] = '\0';
      return newSymbol(symNUMBER,linenum,cp,s);
    }
    else
    {
      switch (nextChar)
      {
      case ';':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symSEMI,linenum,cp,s);
      case '.':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symPERIOD,linenum,cp,s);
      case ',':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symCOMMA,linenum,cp,s);
      case '{':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symLCURLY,linenum,cp,s);
      case '}':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symRCURLY,linenum,cp,s);
      case '(':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symLPAREN,linenum,cp, s);
      case ')':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symRPAREN,linenum,cp, s);
      case '+':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symPLUS,linenum,cp,s);
      case '-':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symMINUS,linenum,cp, s);
      case '*':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symMUL,linenum,cp, s);
      case '/':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symDIV,linenum,cp, s);
      case '=':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symEQ,linenum,cp, s);
      case '<':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        if (nextChar=='=')
        {
          s[n++]=nextChar;
          advance();
          s[n]='\0';
          return newSymbol(symLEQ,linenum,cp,s);
        }
        else if (nextChar=='>')
        {
          s[n++]=nextChar;
          advance();
          s[n]='\0';
          return newSymbol(symNEQ,linenum,cp,s);
        }
        else
        {
          return newSymbol(symLESS,linenum,cp,s);
        }
      case '>':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        if (nextChar=='=')
        {
          s[n++]=nextChar;
          advance();
          s[n]='\0';
          return newSymbol(symGEQ,linenum,cp,s);
        }
        else
        {
          return newSymbol(symGREATER,linenum,cp,s);
        }
      case ':':
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        if (nextChar=='=')
        {
          s[n++]=nextChar;
          advance();
          s[n]='\0';
          return newSymbol(symBECOMES,linenum,cp, s);
        }
        else
        {
          return newSymbol(symCOLON,linenum,cp, s);
        }
      case '"':
        advance();
        while (nextChar!='"')
        {
          s[n++]=nextChar;
          advance();
        }
        advance();
        s[n]='\0';
        return newSymbol(symSTRING,linenum,cp,s);
      case '\0':
        advance();          
        break;
      case ' ':
        // cout << "Debug Space Char" << endl;
        advance();          
        break;
      case '\t':
      case '\r':
      case '\n':
        // cout << "Debug Next Char" << endl;
        advance();          
        break;
      case -1:
        return newSymbol(symEOF, linenum,cp,s);
        // return NULL;
      default:
        cout << "Debug Into Default" << endl;
        s[n++]=nextChar;
        s[n]='\0';
        advance();
        return newSymbol(symerror, linenum,cp,s);
      }
    }
  }
}
void scanner(FILE *f)
{
  sourcefile = f;
}
