#include<stdio.h>
#include<string.h>

int main(){
    char text[50];
    int key[3]={2,0,1};
    int k=3;

    scanf("%s",text);
    int len=strlen(text);
    int r=(len+k-1)/k;

    char mat[10][10];
    int idx=0;

    for(int i=0;i<r;i++)
        for(int j=0;j<k;j++)
            mat[i][j]=(idx<len)?text[idx++]:'X';

    idx=0;
    for(int i=0;i<k;i++)
        for(int j=0;j<r;j++)
            text[idx++]=mat[j][key[i]];

    text[idx]='\0';
    printf("%s\n",text);
    return 0;
}