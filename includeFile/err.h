/************************ err.h **********************/
#define ERRMAX 500
char errmsgs[ERRMAX][54]=
{
  "Must follow with a period.",                /*errmsgs[0] */
  "Missing PROGRAM",                           /*errmsgs[1] */
  "PROGRAM Must follow with identifier",       /*errmsgs[2] */
  "PROGRAM must have identifier following",    /*errmsgs[3] */
  "Missing CONST",                             /*errmsgs[4] */
  "Missing =",                                 /*errmsgs[5] */
  "Missing , or ;",                            /*errmsgs[6] */
  "Missing VAR",                               /*errmsgs[7] */
  "Missing :=",                                /*errmsgs[8] */
  "Missing CALL",                              /*errmsgs[9] */
  "Missing BEGIN",                             /*errmsgs[10]*/
  "Missing END",                               /*errmsgs[11]*/
  "Missing IF",                                /*errmsgs[12]*/
  "Missing THEN",                              /*errmsgs[13]*/
  "Missing WHILE",                             /*errmsgs[14]*/
  "WHILE statement is wrong ,Missing DO",      /*errmsgs[15]*/
  "Missing READ",                              /*errmsgs[16]*/
  "Missing (",                                 /*errmsgs[17]*/
  "Missing )",                                 /*errmsgs[18]*/
  "Missing WRITE",                             /*errmsgs[19]*/
  "Relation Operation Error",                  /*errmsgs[20]*/
  "Missing Identifier",                        /*errmsgs[21]*/
  "Missing Numer",                             /*errmsgs[22]*/
  "Over to the next statement",                /*errmsgs[23]*/
  "CONST Declaration repeat",                  /*errmsgs[24]*/
  "VAR Declaration repeat",                    /*errmsgs[25]*/
  "Identifier does not declare",               /*errmsgs[26]*/
  "Not a Reserve Word",                        /*errmsgs[27]*/
  "Non Storage Class Specifier",               /*errmsgs[28]*/
  "Non Declaration Specifier token",           /*errmsgs[29]*/
  "Missing {",                                 /*errmsgs[30]*/
  "Missing }",                                 /*errmsgs[31]*/
  "The File has ended"                         /*errmsgs[32]*/
};
