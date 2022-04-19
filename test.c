#include <stdio.h>
#include"textcmp.h"
void main() {
    //FILE *f=fopen("hakabaka.txt","w");
    // char t[21]="This is a large file";
    // printf("%d",EOF);
    // for(int i=0;t[i]!=0;i++)
    //     putc(t[i],f);
    //putc(255,f);
    // for(int i=0;i<1024*1024;i++)
    //     putc('B',f);
    // char *t="10110011";
    // char b=0;
    // for(int i=0;t[i]!=0;i++)
    //     b=(b<<1)+(t[i]-'0');
    //printf("%s",streamOfBitsToString("010000010100001",15));
    //fclose(f);
    char* str="01000010";
    char ch=0;
    int i;
    for(i=0;i<8;i++) {
        ch=(ch<<1)+(str[i]-'0');
    }
    printf("%c",ch);
}