#include <stdio.h>
#include "csvutils.h"
#include <string.h>
#include <stdlib.h>

int readupto(FILE *fp, char *s, int linelength, char delimiter) {
   int ch;
   int i = 0;
   s[linelength] = '\0';
    do {
    ch = getc(fp);
    if (ch == EOF)
        break;
    if(ch == delimiter) {
        ch = ' ';
    }
    s[i] = ch;
    i++;
    } while (ch != delimiter);
    return 0;
}

int csvread(const char *filename) {
    FILE * fp = fopen(filename, "r");
    while(fgetc(fp) != EOF) {
        fseek(fp, -1, SEEK_CUR);
        int len = lengthupto(fp, ',');
        char *s = (char *)malloc((len + 1)*sizeof(char));
        readupto(fp, s, len, ',');    
        printf("%s", s);
        free(s);        
    } 
    fclose(fp);
    return 0;
}

int lengthupto(FILE *fp, char delimiter) {
    int linelength = 0;
    int ch = 0;
    do {
    ch = getc(fp);
    if (ch == EOF){
        break;
        linelength--;
    }
    linelength++;
  } while (ch != delimiter);

   fseek(fp, -linelength, SEEK_CUR);
   return linelength;
}