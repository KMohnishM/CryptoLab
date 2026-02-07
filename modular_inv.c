#include<stdio.h>

int modularinv(int a,int m){
    a=(a%m+m)%m;
    for(int i=0;i<m;i++){
        if((a*i)%m==1)
            return i;
    }
    return -1;
}

int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d\n",modularinv(a,b));
    return 0;
}