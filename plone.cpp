/************************* plone.c ************************/
/*
** Include file
*/
#include "includeFile/scanner.h"
#include "includeFile/resword.h"
#include "includeFile/err.h"
#include "includeFile/followsym.h"
#include "includeFile/idobj.h"
#include "includeFile/procobj.h"
/********For C File********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
/*
** Constant
*/
#define IDLEN      36
#define BUFSIZE   512
#define PROCDEPTH  36
/*
** Function
*/
// C++
void translation_unit();            //Language #1
void external_declaration();        //Language #2
void function_definition();         //Language #3
void declaration_specifier();       //Language #4
void storage_class_specifier();     //Language #5
void type_specifier();              //Language #6
void struct_or_union_specifier();   //Language #7
void struct_or_union();             //Language #8
void struct_declaration();          //Language #9
void specifier_qualifier();         //Language #10
void struct_declarator_list();      //Language #11
void struct_declarator();           //Language #12
void declarator();                  //Language #13
void pointer();                     //Language #14
void type_qualifier();              //Language #15
void direct_declarator();           //Language #16
void constant_expression();         //Language #17
void conditional_expression();      //Language #18
void logical_or_expression();       //Language #19
void logical_and_expression();      //Language #20
void inclusive_or_expression();     //Language #21
void exclusive_or_expression();     //Language #22
void and_expression();              //Language #23
void equality_expression();         //Language #24
void relational_expression();       //Language #25
void shift_expression();            //Language #26
void additive_expression();         //Language #27
void multiplicative_expression();   //Language #28
void cast_expression();             //Language #29
void unary_expression();            //Language #30
void postfix_expression();          //Language #31
void primary_expression();          //Language #32
void constant();                    //Language #33
// void expression();                  //Language #34
void assignment_expression();       //Language #35
void assignment_operator();         //Language #36
void unary_operator();              //Language #37
void type_name();                   //Language #38
void parameter_type_list();         //Language #39
void parameter_list();              //Language #40
void parameter_declaration();       //Language #41
void abstract_declarator();         //Language #42
void direct_abstract_declarator();  //Language #43
void enum_specifier();              //Language #44
void enumerator_list();             //Language #45
void enumerator();                  //Language #46
void typedef_name();                //Language #47
void declaration();                 //Language #48
void init_declarator();             //Language #49
void initializer();                 //Language #50
void initializer_list();            //Language #51
void compound_statement();          //Language #52
void Statement();                   //Language #53
void labeled_statement();           //Language #54
void expression_statement();        //Language #55
void selection_statement();         //Language #56
void iteration_statement();         //Language #57
void jump_statement();              //Language #58
void DEBUG_PRINT(char []);
// Plone Orignial
void Identifier();
void Number();
void IdentifierList();
void Factor();
void Term();
void Expression();
void Condition();
void WriteStatement();
void ReadStatement();
void WhileStatement();
void IfStatement();
void CompoundStatement();
void CallStatement();
void AssignmentStatement();
// void Statement();
void ProcDeclaration();
void VarDeclaration();
void ConstDeclaration();
void Block();
void ProgramHead();
void Program();
/*
** Global Constant
*/
struct symbolTag *token;
int errorCount = 0;
struct idobjTag *idobj;
char outname[IDLEN];
FILE *outfile;
int labelCount = 0;
int level = -1;
char progname[IDLEN];
char procname[IDLEN];
char funcName[IDLEN];
struct procobjTag *procStack[BUFSIZE];
int procTop = 0;
struct procobjTag *procobj = NULL;
char id[IDLEN];
char buf[BUFSIZE];
// Self Define
bool FirstFunction = true;
/*
** Error()
*/
void Error(int n)
{
  int j;
  printf("****");
  for (j=0; j<token->right; j++) printf(" ");
  printf("^Error %d  %s\n",n, errmsgs[n]);
  errorCount++;
}
/*
** checkexist()
*/
  int checkexist()
  {
    idobj=getIdobj(procStack[procTop-1], token->value);
    if (idobj==NULL)
      return 0;
    else
      return 1;
  }
/*
** skip()
*/
  void skip(char follows[], int n)
  {
    if (follows[token->sym]==0)
    {
      Error(n);
      while (follows[token->sym]==0)
        token = nextToken();
    }
  }
/*
** Language Rule#1 <translation_unit>
*/
  void translation_unit()
  {
    // while()
    cout << "\nDebug translation_unit" << endl;
    external_declaration();
    // ProgramHead();
    // Block();
    // Do c++ need a period;
    // if (token->sym != symPERIOD) Error(0);
  }
/*
** Language Rule#2 <external-declaration>
*/
  void external_declaration(){
    function_definition();
    // while (1){
    //   token = nextToken();
    //   cout << "Debug " <<token-> value << endl;
    //   function_definition();
    //   break;
    // }
  }
  // void ProgramHead()
  // {
  //   struct procobjTag *p;
  //   if (strcmp(token->value,"PROGRAM")==0)
  //   {
  //     token = nextToken();
  //     if (token->sym == symIDENTIFIER)
  //     {
  //       strcpy(procname, token->value);
  //       p = newProcobj(procname);
  //       p->next = NULL;
  //       p->head = NULL;
  //       p->tail = NULL;
  //       procpush(p);
  //       procStack[procTop++] = p;
  //       strcpy(progname, token->value);
  //       strcat(outname, token->value);
  //       strcat(outname, ".asm");
  //       outfile = fopen(outname, "w");
  //       ++labelCount;
  //       sprintf(buf,
  //         ";************** %s ****************\n"
  //         ";\n"
  //         "\tORG\t100H\n"
  //         "\tJMP\t_start%d\n"
  //         "_intstr\tDB\t'     ','$'\n"
  //         "_buf\tTIMES 256 DB ' '\n"
  //         "\tDB 13,10,'$'\n",
  //         outname, labelCount);
  //       fprintf(outfile,"%s", buf);
  //       strcpy(buf, "%include\t\"dispstr.mac\"\n");
  //       strcat(buf, "%include\t\"itostr.mac\"\n");
  //       strcat(buf, "%include\t\"readstr.mac\"\n");
  //       strcat(buf, "%include\t\"strtoi.mac\"\n");
  //       strcat(buf, "%include\t\"newline.mac\"\n");
  //       fputs(buf, outfile);
  //       token = nextToken();
  //       if (token->sym == symSEMI)
  //         token = nextToken();
  //       else
  //         Error(3);
  //     }
  //     else
  //       Error(2);
  //   }
  //   else
  //     Error(1);
  // }main
/*
** Language Rule#3 <function-definition>
*/
  void function_definition(){
    while((token->sym > symSCSBEGIN )and(token->sym < symTSEND)){
      cout << "Debug function_definition"  << endl;
      declaration_specifier();
    }
    declarator();
    // Need more modify {<declaration>}* ?? only symSCSBEGIN ~ symTSEND ??
    while(((token->sym > symSCSBEGIN )and(token->sym < symTSEND)) or(token->sym == symLPAREN)){
      cout << "Debug function_definition "  << endl;
      declaration();
    }
    compound_statement();
  }
  void Block()
  {
    ++level;
    if (strcmp(token->value, "CONST")==0)
      ConstDeclaration();
    if (strcmp(token->value, "VAR")==0)
      VarDeclaration();
    sprintf(buf, "_start%d:\n", labelCount);
    fprintf(outfile,"%s", buf);
    if (strcmp(token->value, "PROCEDURE")==0)
      ProcDeclaration();
    strcpy(procname, procStack[procTop-1]->name);
    CompoundStatement();
    --level;
  }
/*
** Language Rule#4 <declaration-specifier>
*/
  void declaration_specifier()
  {
    cout << "Debug declaration_specifier" << endl;
    // cout << symTSBEGIN << endl;
    // cout << symTSEND << endl;
    // cout << token->sym << endl;
    // cout << token->value << endl;
    if ((token->sym > symSCSBEGIN) && (token->sym < symSCSEND))
    {
      storage_class_specifier();
    }
    else if ((token->sym > symTQBEGIN) && (token->sym < symTQEND)){
      type_qualifier();
    }
    else if ((token->sym > symTSBEGIN) && (token->sym < symTSEND)){
      type_specifier();
    }
  }
  void ConstDeclaration()
  {
    if (strcmp(token->value, "CONST")==0)
    {
      token = nextToken();
      if (token->sym == symIDENTIFIER)
      {
        varlistadd(procStack[procTop-1], 
          newIdobj(token->value, token->sym, symCONST, 
          level, procStack[procTop-1]->name));
        strcpy(id, procStack[procTop-1]->name);
        strcat(id, "_");
        strcat(id, token->value);
        sprintf(buf, "%s\tDB\t", id);
        fprintf(outfile,"%s", buf);
        token = nextToken();
      }
      if (token->sym == symEQ)
      {
        token = nextToken();
        sprintf(buf, "'%s','$'\n", token->value);
        fprintf(outfile,"%s", buf);
        token = nextToken();
        while (token->sym == symCOMMA)
        {
          token = nextToken();
          if (token->sym == symIDENTIFIER)
          {
            varlistadd(procStack[procTop-1], 
              newIdobj(token->value, token->sym, symCONST, 
              level, procStack[procTop-1]->name));
            sprintf(buf, "%s_%s\tDB\t",
              procStack[procTop-1]->name, token->value);
            fprintf(outfile,"%s", buf);
            token = nextToken();
          }
          if (token->sym == symEQ)
          {
            token = nextToken();
            sprintf(buf, "'%s','$'\n", token->value);
            fprintf(outfile,"%s", buf);
            token = nextToken();
          }
          else
            Error(5);
        }
        if (token->sym == symSEMI)
          token = nextToken();
        else
        {
          Error(6);
          skip(statement, 23);
          if (token->sym == symSEMI)
            token = nextToken();
        }
      }
      else
      {
        Error(5);
        skip(statement, 23);
        if (token->sym == symSEMI)
          token = nextToken();
      }
    }
    else
    {
      Error(4);
    }
  }
/*
** Language Rule#5 <storage-class-specifier>
*/
 void storage_class_specifier()
 {
    cout << "Debug Into Storage Class Specifier" << endl;
    if (isResword(token->value) != -1){
        if ((token->sym == symAUTO )||(token->sym == symREGISTER)||
        (token->sym == symSTATIC)|| (token->sym == symEXTERN)||
        (token->sym == symTYPEDEF)){
          token = nextToken();
        }
        else
        {
          Error(27);
        }
    }
    else
      skip(statement, 22);

 }
  void VarDeclaration()
  {
    if (strcmp(token->value, "VAR")==0)
    {
      token = nextToken();
      if (token->sym == symIDENTIFIER)
      {
        idobj=newIdobj(token->value,token->sym,
          symVAR, level, procStack[procTop-1]->name);
        varlistadd(procobjTop, idobj);
        sprintf(buf, "%s_%s\tDW\t0\n",
          procStack[procTop-1]->name, token->value);
        fprintf(outfile,"%s", buf);
        token = nextToken();
      }
      while (token->sym == symCOMMA)
      {
        token = nextToken();
        if (token->sym == symIDENTIFIER)
        {
          idobj=newIdobj(token->value,token->sym,symVAR,
                         level, procStack[procTop-1]->name);
          varlistadd(procobjTop, idobj);
          sprintf(buf, "%s_%s\tDW\t0\n",
            procStack[procTop-1]->name, token->value);
          fprintf(outfile,"%s", buf);
          token = nextToken();
        }
      }
      if (token->sym == symSEMI)
      {
        token = nextToken();
      }
      else
      {
        Error(6);
        skip(statement, 23);
        if (token->sym == symSEMI)
          token = nextToken();
      }
    }
    else
    {
      Error(7);
    }
  }
/*
** Language Rule#6 <type-specifier>
*/
  void type_specifier()
  {
    if (isResword(token->value) != -1){
        if ((token->sym > symTSBEGIN) && (token->sym < symTSEND)){
          token = nextToken();
        }
        // if else(){} For struct-or-union-specifier
        // if else(){} For enum-specifier
        // if else(){} For typedef-name
        else
        {
          Error(27);
        }
    }
    else
      skip(statement, 26);
  }
  void ProcDeclaration()
  {
    int tail;
    char *procid;
    struct procobjTag *p;
    while (strcmp(token->value, "PROCEDURE")==0)
    {
      token = nextToken();
      tail = 0;
      if (token->sym == symIDENTIFIER)
      {
        strcpy(procname, token->value);
        p = newProcobj(procname);
        p->head = NULL; 
        p->tail = NULL;
        varlistadd(
          procStack[procTop-1],
          newIdobj(procname, token->sym, symPROCEDURE,
          level, procStack[procTop-1]->name));
        procpush(p);
        procStack[procTop++] = p;
        tail = ++labelCount;
        sprintf(buf,"\tJMP\t_go%d\n%s:\n"
                    "\tJMP\t_start%d\n",
                    tail, token->value, labelCount);
        fprintf(outfile,"%s", buf);
        token = nextToken();
      }
      if (token->sym == symSEMI)
      {
        token = nextToken();
        Block();
        if (token->sym == symSEMI)
        {
          sprintf(buf, "\tRET\n_go%d:\n",tail);
          fprintf(outfile,"%s", buf);
          token = nextToken();
        }
        else
        {
          Error(6);
          skip(statement, 23);
          if (token->sym == symSEMI)
            token = nextToken();
        }
      }
      else
      {
        Error(6);
      }
      --procTop;
    }
  }
/*
** Language Rule#7 <Statement>
*/

/*
** Language Rule#8 <AssignmentStatement>
*/
  void AssignmentStatement()
  {
    char result[BUFSIZE];
    idobj=getIdobj(procStack[procTop-1], token->value);
    if (idobj != NULL)
    {
      sprintf(result, "%s_%s",
        idobj->procname, token->value);    
    }    
    Identifier();
    if (token->sym == symBECOMES)
    {
      token = nextToken();
      Expression();
      sprintf(buf, "\tPOP\tAX\n"
                   "\tMOV\t[%s], AX\n", result);
      fprintf(outfile,"%s", buf);
    }
    else
    {
      Error(8);
      skip(statement, 23);
    }
  }
/*
** Language Rule#9 <CallStatement>
*/
  void CallStatement()
  {
    if (strcmp(token->value, "CALL")==0)
    {
      token = nextToken();
      idobj=getIdobj(procStack[procTop-1], token->value);
      if (idobj != NULL)
      {
        sprintf(buf, "\tCALL\t%s\n", token->value);
        fprintf(outfile,"%s", buf);
      }
      Identifier();
    }
    else
    {
      Error(9);
      skip(statement, 23);
    }
  }
/*
** Language Rule#10 <CompoundStatement>
*/
  void CompoundStatement()
  {
    if (strcmp(token->value,"BEGIN")==0)
    {
      token = nextToken();
      Statement();
      while (token->sym == symSEMI)
      {
        token = nextToken();
        Statement();
      }
      if (strcmp(token->value,"END")==0)
        token = nextToken();
      else
      {
        Error(11);
        skip(statement, 23);
      }
    }
    else
    {
      Error(10);
      skip(statement, 23);
    }
  }
/*
** Language Rule#11 <IfStatement>
*/
  void IfStatement()
  {
    int head, tail;
    if (strcmp(token->value,"IF")==0)
    {
      token = nextToken();
      Condition();
      head = labelCount;
      tail = ++labelCount;
      sprintf(buf, "\tJMP\t_go%d\n"
                   "_go%d:\n", tail,head);
      fprintf(outfile,"%s", buf);
      if (strcmp(token->value, "THEN")==0)
      {
        token = nextToken();
        Statement();
        sprintf(buf, "_go%d:\n", tail);
        fprintf(outfile,"%s", buf);
      }
      else
      {
        Error(13);
        skip(statement, 23);
      }
    }
    else
    {
      Error(12);
      skip(statement, 23);
    }
  }
/*
** Language Rule#12 <WhileStatement>
*/
  void WhileStatement()
  {
    int home, head, tail;
    if (strcmp(token->value,"WHILE")==0)
    {
      token = nextToken();
      home = ++labelCount;
      sprintf(buf, "_go%d:\n", home);
      fprintf(outfile,"%s", buf);
      Condition();
      head = labelCount;
      tail = ++labelCount;
      sprintf(buf, "\tJMP\t_go%d\n"
                   "_go%d:\n", tail, head);
      fprintf(outfile,"%s", buf);
      if (strcmp(token->value,"DO")==0)
      {
        token = nextToken();
        Statement();
        sprintf(buf, "\tJMP\t_go%d\n", home);
        fprintf(outfile,"%s", buf);
      }
      else
      {
        Error(15);
        skip(statement, 23);
      }
      sprintf(buf, "_go%d:\n", tail);
      fprintf(outfile,"%s", buf);
    }
    else
    {
      Error(14);
      skip(statement, 23);
    }
  }
/*
** Language Rule#13 <declarator>
*/
  void declarator(){
    cout << "Debug Into Declarator" << endl;
    if (token->sym == symMUL){
      pointer();
    }
    direct_declarator();
  }
  void ReadStatement()
  {
    if (strcmp(token->value,"READ")==0)
    {
      token = nextToken();
      if (token->sym == symLPAREN)
      {
        token = nextToken();
        if (token->sym == symIDENTIFIER)
        {
          idobj=getIdobj(procStack[procTop-1],token->value);
          if (idobj != NULL)
          {
            sprintf(id,"%s_%s",idobj->procname,token->value);
            sprintf(buf, "\treadstr\t_buf\n"
                         "\tstrtoi\t_buf, '$', %s\n"
                         "\tnewline\n", id);
            fprintf(outfile,"%s", buf);
          }
          Identifier();
        }
        while (token->sym == symCOMMA)
        {
          token = nextToken();
          if (token->sym == symIDENTIFIER)
          {
            idobj = getIdobj(procStack[procTop-1],
                             token->value);
            if (idobj != NULL)
            {
              sprintf(id, "%s_%s",
                      idobj->procname, token->value);
              sprintf(buf, "\treadstr\t_buf\n"
                           "\tstrtoi\t_buf, '$', %s\n"
                           "\tnewline\n", id);
              fprintf(outfile,"%s", buf);
            }
            Identifier();
          }
        }
        if (token->sym == symRPAREN)
          token = nextToken();
        else
        {
          Error(18);
          skip(statement, 23);
        }
      }
      else
      {
        Error(17);
        skip(statement, 23);
      }
    }
    else
    {
      Error(16);
      skip(statement, 23);
    }
  }
/*
** Language Rule#14 <WriteStatement>
*/
  void pointer()
  {
    cout << "Debug pointer" << endl;
    if (token->sym == symMUL)
    {
      type_qualifier(); 
    }
  }
  void WriteStatement()
  {
    if (strcmp(token->value, "WRITE")==0)
    {
      token = nextToken();
      if (token->sym == symLPAREN)
      {
        token = nextToken();
        if (token->sym == symIDENTIFIER)
        {
          idobj=getIdobj(procStack[procTop-1],token->value);
          if (idobj != NULL)
          {
            sprintf(id, "%s_%s",
                        idobj->procname, token->value);
            if (idobj->attr == symCONST)
            {
              sprintf(buf,"\tdispstr\t%s\n", id);
              fprintf(outfile,"%s", buf);
            }
            else
            {
              sprintf(buf, "\titostr\t%s, _intstr, '$'\n"
                "\tMOV\tDX, _intstr\n"
                "\tMOV\tAH, 09H\n"
                "\tINT\t21H\n"
                "\tnewline\n", id);
              fprintf(outfile,"%s", buf);
            }
          }
          Identifier();
        }
        while (token->sym == symCOMMA)
        {
          token = nextToken();
          if (token->sym == symIDENTIFIER)
          {
            idobj = getIdobj(procStack[procTop-1],
                             token->value);
            if (idobj != NULL)
            {
              sprintf(id, "%s_%s",
                          idobj->procname, token->value);
              if (idobj->attr == symCONST)
              {
                sprintf(buf,"\tdispstr\t%s\n", id);
                fprintf(outfile,"%s", buf);
              }
              else
              {
                sprintf(buf, "\titostr\t%s, _intstr, '$'\n"
                  "\tMOV\tDX, _intstr\n"
                  "\tMOV\tAH, 09H\n"
                  "\tINT\t21H\n"
                  "\tnewline\n", id);
                fprintf(outfile,"%s", buf);
              }
            }
            Identifier();
          }
        }
        if (token->sym == symRPAREN)
          token = nextToken();
        else
        {
          Error(18);
          skip(statement, 23);
        }
      }
      else
      {
        Error(17);
        skip(statement, 23);
      }
    }
    else
    {
      Error(19);
      skip(statement, 23);
    }
  }
/*
** Language Rule#15 <type-qualifier>
*/
  void type_qualifier()
  {
    if (isResword(token->value) != -1)
    {
      if (token->sym ==  symCONST){}
      else if(token->sym == symVOLATILE){}
    }
    else
    {
      Error(26);
    }
    
  }
  void IdentifierList()
  {
    Identifier();
    while (token->sym == symCOMMA)
    {
      token = nextToken();
      Identifier();
    }
  }
/*
** Language Rule#16 <direct-declarator>
*/
  void direct_declarator(){
    cout << "Debug Into direct-declarator" << endl;
    // struct procobjTag *p;
    cout << "Debug " << token->sym << endl;
    cout << "Debug " << token->value << endl;
    if ((token->sym == symIDENTIFIER) && (FirstFunction == true))
    {
      strcpy(funcName, token->value);
      cout << "Debug funcName " << funcName << endl; 
      struct procobjTag *p;
      p = newProcobj(procname);
      p->next = NULL;
      p->head = NULL;
      p->tail = NULL;
      procpush(p);
      procStack[procTop++] = p;
      strcpy(progname, token->value);
      strcpy(outname, "output/");
      strcat(outname, token->value);
      strcat(outname, ".asm");
      outfile = fopen(outname, "w");
      ++labelCount;
      sprintf(buf,
        ";************** %s ****************\n"
        ";\n"
        "\tglobal _main\n"
        "_intstr\tDB\t'     ','$'\n"
        "_buf\tTIMES 256 DB ' '\n"
        "\tDB 13,10,'$'\n",
         outname);
      fprintf(outfile,"%s", buf);
      strcpy(buf, "%include\t\"dispstr.mac\"\n");
      strcat(buf, "%include\t\"itostr.mac\"\n");
      strcat(buf, "%include\t\"readstr.mac\"\n");
      strcat(buf, "%include\t\"strtoi.mac\"\n");
      strcat(buf, "%include\t\"newline.mac\"\n");
      snprintf(buf, 10, "_main:\n");
      fputs(buf, outfile);
      token = nextToken();
      // The flag that use for Detemine if it is first in function 
      FirstFunction = false;
        // if (token->sym == symSEMI) token = nextToken();
        // else Error(3);
    }
    else if(token->sym == symLPAREN){
      cout << "Debug Into (<declarator>)" << endl;
      token = nextToken();
      cout << "Debug next token: " << token->value << endl;
      // ?? Not sure how to do this part -> need to ignore the null
      // declarator();
    }
    else Error(2);
        // else
    //   Error(1);
    //  Identifier();

  } 
  void Condition()
  {
    Expression();
    if (token->sym == symLESS ||
        token->sym == symLEQ ||
        token->sym == symEQ ||
        token->sym == symNEQ ||
        token->sym == symGREATER ||
        token->sym == symGEQ)
    {
      int operatorDeclare = token->sym;
      token = nextToken();
      Expression();
      sprintf(buf, "\tPOP\tBX\n"
                   "\tPOP\tAX\n"
                   "\tCMP\tAX, BX\n");
      fprintf(outfile,"%s", buf);
      switch (operatorDeclare)
      {
        case symEQ:
          sprintf(buf,"\tJE\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
        case symNEQ:
          sprintf(buf,"\tJNE\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
        case symLESS:
          sprintf(buf,"\tJL\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
        case symLEQ:
          sprintf(buf,"\tJLE\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
        case symGREATER:
          sprintf(buf,"\tJG\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
        case symGEQ:
          sprintf(buf,"\tJGE\t_go%d\n",(++labelCount));
          fprintf(outfile,"%s", buf);
          break;
      }
    }
    else
    {
      Error(20);
      skip(statement, 23);
    }
  }
/*
** Language Rule#17 <Expression>
*/
  void Expression()
  {
    if (token->sym == symPLUS ||
        token->sym == symMINUS)
    {
      token = nextToken();
    }
    Term();
    while (token->sym == symPLUS ||
           token->sym == symMINUS)
    {
      int operatorDeclare = token->sym;
      token = nextToken();
      Term();
      if (operatorDeclare == symPLUS)
      {
        fprintf(outfile,"\tPOP\tBX\n"
                    "\tPOP\tAX\n"
                    "\tADD\tAX, BX\n"
                    "\tPUSH\tAX\n");
      }
      else
      {
        fprintf(outfile, "\tPOP\tBX\n"
                     "\tPOP\tAX\n"
                     "\tSUB\tAX, BX\n"
                     "\tPUSH\tAX\n");
      }
    }
  }
/*
** Language Rule#18 <Term>
*/
  void Term()
  {
    Factor();
    while (token->sym == symMUL ||
           token->sym == symDIV)
    {
      int operatorDeclare = token->sym;
      token = nextToken();
      Factor();
      if (operatorDeclare == symMUL)
      {
        fprintf(outfile, "\tPOP\tBX\n"
                     "\tPOP\tAX\n"
                     "\tMUL\tBX\n"
                     "\tPUSH\tAX\n");
      }
      else
      {
        fprintf(outfile, "\tPOP\tBX\n"
                     "\tMOV\tDX, 0\n"
                     "\tPOP\tAX\n"
                     "\tDIV\tBX\n"
                     "\tPUSH\tAX\n");
      }
    }
  }
/*
** Language Rule#19 <Factor>
*/
  void Factor()
  {
    if (token->sym == symIDENTIFIER)
    {
      idobj=getIdobj(procStack[procTop-1],token->value);
      if (idobj != NULL)
      {
        sprintf(id, "%s_%s",idobj->procname, token->value);
        sprintf(buf, "\tPUSH\tWORD [%s]\n", id);
        fprintf(outfile,"%s", buf);
      }
      Identifier();
    }
    else if (token->sym == symNUMBER)
    {
      sprintf(buf, "\tPUSH\t%s\n", token->value);
      fprintf(outfile,"%s", buf);
      Number();
    }
    else if (token->sym == symLPAREN)
    {
      token = nextToken();
      Expression();
      if (token->sym == symRPAREN)
        token = nextToken();
      else
      {
        Error(18);
        skip(factor, 23);
      }
    }
  }
// Language Rule#48
//<declaration> ::=  {<declaration-specifier>}+ {<init-declarator>}* ;
void declaration(){
  cout << "Debug Into #48 Declaration" << endl;
  cout << token->value << endl;
  if ((token->sym > symSCSBEGIN )and(token->sym < symTSEND)){
    do {
      declaration_specifier();
    }while((token->sym > symSCSBEGIN )and(token->sym < symTSEND));
  }
  else{
    cout << token->value << endl;
    cout << "Debug should be error but not finish yet" << endl;
    // Error(29);
  }
  init_declarator();
}
// Language Rule#49
/*
<init-declarator> ::= <declarator>
                    | <declarator> = <initializer>
*/
void init_declarator(){
  cout << "Debug Into init_declarator" << endl;
  if (nextToken()->sym == symEQ){
    cout << "Debug token "<< token->value << endl;
    declarator();
    cout << "Debug token "<< token->value << endl;
    token = nextToken();
    cout << "Debug token "<< token->value << endl;
    initializer();
  }
  declarator();
}
// Language Rule#50
void initializer(){

}
// Language Rule#52
void compound_statement(){
  cout << "Debug Into #52 Compound Statement" << endl;
  if (token->sym == symLCURLY){
    token = nextToken();
    cout << "Debug After LCURLY " << token->value << endl;
    while((token->sym > symSCSBEGIN )and(token->sym < symTSEND)){
      declaration();
    }
    // Need more Adjust for apply BNF
    Statement();
    cout << "Debug next token "<< token->value << endl;
    if (token->sym != symRCURLY){
      Error(31);
      if(token->sym == symEOF){
        Error(32);
      }
    }
  }
  else Error(30);
}
// Language Rule#53
/*
<statement> ::= <labeled-statement>
              | <expression-statement>
              | <compound-statement>
              | <selection-statement>
              | <iteration-statement>
              | <jump-statement>
*/
void Statement()
{
  // if (isResword(token->value) != -1)
  // {
  //   if (strcmp(token->value,"IF")==0)
  //     IfStatement();
  //   else if (strcmp(token->value,"BEGIN")==0)
  //     CompoundStatement();
  //   else if (strcmp(token->value,"WHILE")==0)
  //     WhileStatement();
  //   else if (strcmp(token->value,"READ")==0)
  //     ReadStatement();
  //   else if (strcmp(token->value,"WRITE")==0)
  //     WriteStatement();
  //   else if (strcmp(token->value,"CALL")==0)
  //     CallStatement();
  // }
  // else if (token->sym == symIDENTIFIER)
  //   AssignmentStatement();
  // else
  //   skip(statement, 23);
}
// Language Rule#54
/*
<labeled-statement> ::= <identifier> : <statement>
                      | case <constant-expression> : <statement>
                      | default : <statement>
*/
void labeled_statement(){
  Identifier();
  token = nextToken();

}
/*
** For DEBUG And Print Purpose
*/
void DEBUG_PRINT(char* DEBUG_STRING){
  sprintf(buf,
    "\tmov       rax, 0x02000004         ; system call for write\n"
    "\tmov       rdi, 1                  ; file handle 1 is stdout\n"
    "\tmov       rsi, message            ; address of string to output\n"
    "\tmov       rdx, 13                 ; number of bytes\n"
    "\tsyscall                           ; invoke operating system to do the write\n"
    "\tmov       rax, 0x02000001         ; system call for exit\n"
    "\txor       rdi, rdi                ; exit code 0\n"
    "\tsyscall                           ; invoke operating system to exit\n"
    "\tsection   .data\n"
    "\tmessage:  db\t\"%s\", 30      ; note the newline at the end\n"
    ,DEBUG_STRING);
    fprintf(outfile,"%s", buf);
}

/*
** Identifier Process
*/
  void Identifier()
  {
    if (token->sym == symIDENTIFIER)
    {
      idobj=getIdobj(procStack[procTop-1],token->value);
      if (idobj == NULL){
        Error(26);
        cout << " This is the place is wrong" << endl;
      }
        
      token = nextToken();
    }
    else
      Error(21);
  }
/*
** Number Process
*/
  void Number()
  {
    if (token->sym == symNUMBER)
      token = nextToken();
    else
      Error(22);
  }
/*
************************** Main Function **********************
*/
  int main(int argc, char *argv[])
  {
    FILE *f=fopen(argv[1], "r");
    scanner(f);
    followsyminit();
    token = nextToken();
    translation_unit();
    // Test the codes
    // return
    char debugString[IDLEN];
    snprintf(debugString, 30, "Hello to NASM World");
    DEBUG_PRINT(debugString);
    // fprintf(outfile, "\tMOV\tAX, 4C00H\n"
    //              "\tINT\t21H\n");
    printf("\n  Plone compile completed. "
      "\n  Error count : %d\n", errorCount);
    if (argc==3)
    {
      printf("\nIdentifier Stacking content is follow:\n%s\n",
        procobjToString());
    }
    fclose(outfile);
    fclose(f);
    if (errorCount==0)
    {
      FILE *batchfile;
      sprintf(buf, "output/%s.bat", progname);
      batchfile=fopen(buf,"w");
      char commandLine[BUFSIZE];
      // sprintf(commandLine, "chmod 766 /Users/jameslee/Desktop/Spring2020/Compiler/Compiler_codes/codingFINAL/output/%s.asm", progname);
      sprintf(commandLine,"nasm -f macho64 /Users/jameslee/Desktop/Spring2020/Compiler/Compiler_codes/codingFINAL/output/%s.asm "
      "-o /Users/jameslee/Desktop/Spring2020/Compiler/Compiler_codes/codingFINAL/output%s.com "
      "&& ld -no_pie -e _main -macosx_version_min 10.13 -arch x86_64 "
      "/Users/jameslee/Desktop/Spring2020/Compiler/Compiler_codes/codingFINAL/output%s.com -lSystem\n",progname,progname,progname);
      cout << commandLine << endl;
      fprintf(batchfile, "%s", commandLine);
      fprintf(batchfile, "/Users/jameslee/Desktop/Spring2020/Compiler/Compiler_codes/codingFINAL/a.out\n");
      fclose(batchfile);
     }
    return 0;
  }
