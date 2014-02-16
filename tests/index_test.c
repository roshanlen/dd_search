#include<stdio.h>
extern void tokenize_file(FILE* line);


int main(int argc,char* argv[])
{
        FILE* file;
        if ( argc < 2 )
                return 1;
        file=fopen(argv[1],"r"); 
        if ( file == NULL )
                return 1;
        tokenize_file(file);
}
