#include<stdio.h>

int modularinv(int a,int m){
    for(int i=0;i<m;i++)
        if((a*i)%m==1) return i;
    return -1;
}

int main(){
    int p=23,g=5,x=6,k=7,m=7;

    int y=1;
    for(int i=0;i<x;i++) y=(y*g)%p;

    int c1=1,c2=1;
    for(int i=0;i<k;i++){
        c1=(c1*g)%p;
        c2=(c2*y)%p;
    }
    c2=(c2*m)%p;

    int s=1;
    for(int i=0;i<x;i++) s=(s*c1)%p;

    int dec=(c2*modularinv(s,p))%p;

    printf("c1=%d c2=%d decrypted=%d\n",c1,c2,dec);
    return 0;
}