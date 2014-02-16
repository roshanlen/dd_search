/* 
   Go through a given file and generate an index. 
   A keyword is defined as [A-Za-z_][A-Za-z0-9_-]*

   Each file has to be parsed, a list of keywords collected,
   with the position of the keyword in the file, and generate
   a list of keyword:filepath entries. For a given keyword
   there can be multiple ( 1 or more ) filepaths.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_LINE 256
#define SEPERATOR " ()="

#define iswhite(c)    (c=='\t' || c== ' ')
#define iskeyword(c)  (c=='_' || isalpha(c))
#define eos(c)        (c=='\0')

#define TOK_START  0x7878
#define TOK_KEYWORD 0x8877
#define TOK_IGNORE  0xdead

/*
   get the next keyword, start position, of the
   string pointed to by line. Return the start of 
   they keyword, null if it cannot find one.
*/
char*  get_next_keyword(char* line)
{
        int state = TOK_START;
        char* cp = line;

start:
        switch(state)
        {
                case TOK_START:
                        while(!eos(cp) && iswhite(*cp)) 
                                cp++;
                        if ( eos(cp) )
                                return NULL;
                        else if ( iskeyword(*cp))
                                state = TOK_KEYWORD;
                        else
                                state = TOK_IGNORE;
                        break;
                case TOK_IGNORE:
                        while(!eos(cp) && !iskeyword(*cp))
                                cp++;
                        if ( eos(cp) ) 
                                return NULL;
                        state = TOK_START; 
                        break;
                case TOK_KEYWORD:
                        line=cp;
                        while(iskeyword(*cp))
                        {
                                cp++;
                        }
                        *cp='\0';
                        return line;
      #if 0
                        if (eos(cp) || iswhite(*cp)) 
                        {
                                *cp='\0';
                                return line;
                        }
                        else
                                state=TOK_START;
#endif
        }
        goto start;
}
char*  tokenize_line(char* line)
{
        static char* in_s,*end_s;
        char* cp=NULL;
        int state = TOK_START;

        if ( line )
        {
                in_s = line;
                end_s = in_s+strlen(line);
        } 
        /* eat all the spaces */
        cp=get_next_keyword(in_s); 
        /* advance to the next keyword*/
        if ( cp )
        {
                in_s += strlen(cp) + 1;
                if ( in_s >= end_s )
                        cp = NULL;
        }
        
        return cp;
}

void tokenize_file(FILE* file)
{
        //char* line = NULL;
        char line[MAX_LINE];
        char* token = NULL,*c = NULL;

        while(fgets(line,MAX_LINE,file))
        {
                c=tokenize_line(line);
                do
                {
                        printf(" -- %s --- \n",c);
                }while(c=tokenize_line(NULL));

        }
}

