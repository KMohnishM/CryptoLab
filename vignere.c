#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char text[50],key[20];
    scanf("%s%s",text,key);

    int j=0;
    for(int i=0;text[i];i++){
        if(isalpha(text[i])){
            int k=key[j%strlen(key)]-'A';
            text[i]=((text[i]-'A'+k)%26)+'A';
            j++;
        }
    }
    printf("%s\n",text);
    return 0;
}