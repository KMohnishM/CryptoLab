#include<stdio.h>
#include<ctype.h>

int main(){
    char text[50];
    int key=3;
    scanf("%s",text);

    for(int i=0;text[i];i++){
        if(isalpha(text[i])){
            text[i]=((text[i]-'A'+key)%26)+'A';
        }
    }
    printf("%s\n",text);
    return 0;
}