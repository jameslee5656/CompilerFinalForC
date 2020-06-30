/************************* plone.c ************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
/*
** Include file
*/
  #include "includeFile/scanner.h"
  #include "includeFile/resword.h"
  #include "includeFile/err.h"
  #include "includeFile/followsym.h"
  #include "includeFile/idobj.h"
  #include "includeFile/procobj.h"
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
  // void statement();                   //Language #53
  void labeled_statement();           //Language #54
  void expression_statement();        //Language #55
  void selection_statement();         //Language #56
  void iteration_statement();         //Language #57
  void jump_statement();              //Language #58
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
  void Statement();
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
  struct procobjTag *procStack[BUFSIZE];
  int procTop = 0;
  struct procobjTag *procobj = NULL;
  char id[IDLEN];
  char buf[BUFSIZE];
/*
** Error()
*/
  void Error(int n)
  {
    int j;
    printf("****");
    for (j=0; j<=token->right; j++) printf(" ");
    printf("^%d  %s\n",n, errmsgs[n]);
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
    cout << "Debug " <<token-> value << endl;
    external_declaration();
    // ProgramHead();
    // Block();
    if (token->sym != symPERIOD) Error(0);
  }
/*
** Language Rule#2 <ProgramHead>
*/
  void external_declaration(){
    while (1){
      token = nextToken();
      cout << "Debug " <<token-> value << endl;
      function_definition();
      break;
    }
  }
  void ProgramHead()
  {
    struct procobjTag *p;
    if (strcmp(token->value,"PROGRAM")==0)
    {
      token = nextToken();
      if (token->sym == symIDENTIFIER)
      {
        strcpy(procname, token->value);
        p = newProcobj(procname);
        p->next = NULL;
        p->head = NULL;
        p->tail = NULL;
        procpush(p);
        procStack[procTop++] = p;
        strcpy(progname, token->value);
        strcpy(outname, token->value);
        strcat(outname, ".asm");
        outfile = fopen(outname, "w");
        ++labelCount;
        sprintf(buf,
          ";************** %s ****************\n"
          ";\n"
          "\tORG\t100H\n"
          "\tJMP\t_start%d\n"
          "_intstr\tDB\t'     ','$'\n"
          "_buf\tTIMES 256 DB ' '\n"
          "\tDB 13,10,'$'\n",
          outname, labelCount);
        fprintf(outfile, buf);
        strcpy(buf, "%include\t\"dispstr.mac\"\n");
        strcat(buf, "%include\t\"itostr.mac\"\n");
        strcat(buf, "%include\t\"readstr.mac\"\n");
        strcat(buf, "%include\t\"strtoi.mac\"\n");
        strcat(buf, "%include\t\"newline.mac\"\n");
        fputs(buf, outfile);
        token = nextToken();
        if (token->sym == symSEMI)
          token = nextToken();
        else
          Error(3);
      }
      else
        Error(2);
    }
    else
      Error(1);
  }
/*
** Language Rule#3 <Block>
*/
  void function_definition(){
    cout << "Debug function_definition" <<token-> value << endl;
    declaration_specifier();
    // declarator();
    // declaration();
    // compound_statement();
  }
  void Block()
  {
    ++level;
    if (strcmp(token->value, "CONST")==0)
      ConstDeclaration();
    if (strcmp(token->value, "VAR")==0)
      VarDeclaration();
    sprintf(buf, "_start%d:\n", labelCount);
    fprintf(outfile, buf);
    if (strcmp(token->value, "PROCEDURE")==0)
      ProcDeclaration();
    strcpy(procname, procStack[procTop-1]->name);
    CompoundStatement();
    --level;
  }
/*
** Language Rule#4 <ConstDeclaration>
*/
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
        fprintf(outfile, buf);
        token = nextToken();
      }
      if (token->sym == symEQ)
      {
        token = nextToken();
        sprintf(buf, "'%s','$'\n", token->value);
        fprintf(outfile, buf);
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
            fprintf(outfile, buf);
            token = nextToken();
          }
          if (token->sym == symEQ)
          {
            token = nextToken();
            sprintf(buf, "'%s','$'\n", token->value);
            fprintf(outfile, buf);
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
** Language Rule#5 <VarDeclaration>
*/
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
        fprintf(outfile, buf);
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
          fprintf(outfile, buf);
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
** Language Rule#6 <ProcDeclaration>
*/
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
        fprintf(outfile,buf);
        token = nextToken();
      }
      if (token->sym == symSEMI)
      {
        token = nextToken();
        Block();
        if (token->sym == symSEMI)
        {
          sprintf(buf, "\tRET\n_go%d:\n",tail);
          fprintf(outfile, buf);
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
  void Statement()
  {
    if (isResword(token->value) != -1)
    {
      if (strcmp(token->value,"IF")==0)
        IfStatement();
      else if (strcmp(token->value,"BEGIN")==0)
        CompoundStatement();
      else if (strcmp(token->value,"WHILE")==0)
        WhileStatement();
      else if (strcmp(token->value,"READ")==0)
        ReadStatement();
      else if (strcmp(token->value,"WRITE")==0)
        WriteStatement();
      else if (strcmp(token->value,"CALL")==0)
        CallStatement();
    }
    else if (token->sym == symIDENTIFIER)
      AssignmentStatement();
    else
      skip(statement, 23);
  }
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
      fprintf(outfile, buf);
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
        fprintf(outfile, buf);
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
      fprintf(outfile, buf);
      if (strcmp(token->value, "THEN")==0)
      {
        token = nextToken();
        Statement();
        sprintf(buf, "_go%d:\n", tail);
        fprintf(outfile, buf);
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
      fprintf(outfile, buf);
      Condition();
      head = labelCount;
      tail = ++labelCount;
      sprintf(buf, "\tJMP\t_go%d\n"
                   "_go%d:\n", tail, head);
      fprintf(outfile, buf);
      if (strcmp(token->value,"DO")==0)
      {
        token = nextToken();
        Statement();
        sprintf(buf, "\tJMP\t_go%d\n", home);
        fprintf(outfile, buf);
      }
      else
      {
        Error(15);
        skip(statement, 23);
      }
      sprintf(buf, "_go%d:\n", tail);
      fprintf(outfile, buf);
    }
    else
    {
      Error(14);
      skip(statement, 23);
    }
  }
/*
** Language Rule#13 <ReadStatement>
*/
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
            fprintf(outfile, buf);
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
              fprintf(outfile, buf);
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
              fprintf(outfile, buf);
            }
            else
            {
              sprintf(buf, "\titostr\t%s, _intstr, '$'\n"
                "\tMOV\tDX, _intstr\n"
                "\tMOV\tAH, 09H\n"
                "\tINT\t21H\n"
                "\tnewline\n", id);
              fprintf(outfile, buf);
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
                fprintf(outfile, buf);
              }
              else
              {
                sprintf(buf, "\titostr\t%s, _intstr, '$'\n"
                  "\tMOV\tDX, _intstr\n"
                  "\tMOV\tAH, 09H\n"
                  "\tINT\t21H\n"
                  "\tnewline\n", id);
                fprintf(outfile, buf);
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
** Language Rule#15 <IdentifierList>
*/
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
** Language Rule#16 <Condition>
*/
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
      fprintf(outfile, buf);
      switch (operatorDeclare)
      {
        case symEQ:
          sprintf(buf,"\tJE\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
          break;
        case symNEQ:
          sprintf(buf,"\tJNE\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
          break;
        case symLESS:
          sprintf(buf,"\tJL\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
          break;
        case symLEQ:
          sprintf(buf,"\tJLE\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
          break;
        case symGREATER:
          sprintf(buf,"\tJG\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
          break;
        case symGEQ:
          sprintf(buf,"\tJGE\t_go%d\n",(++labelCount));
          fprintf(outfile, buf);
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
        fprintf(outfile, buf);
      }
      Identifier();
    }
    else if (token->sym == symNUMBER)
    {
      sprintf(buf, "\tPUSH\t%s\n", token->value);
      fprintf(outfile, buf);
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
/*
** Identifier Process
*/
  void Identifier()
  {
    if (token->sym == symIDENTIFIER)
    {
      idobj=getIdobj(procStack[procTop-1],token->value);
      if (idobj == NULL)
        Error(26);
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
    return
    fprintf(outfile, "\tMOV\tAX, 4C00H\n"
                 "\tINT\t21H\n");
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
      sprintf(buf, "%s.bat", progname);
      batchfile=fopen(buf,"w");
      fprintf(batchfile, "nasmw %s.asm -o %s.com\n",
              progname, progname);
      fprintf(batchfile, "%s.com\n", progname);
      fclose(batchfile);
     }
    return 0;
  }
