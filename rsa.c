#include<stdio.h>

int gcd(int a,int b,int s1,int s2,int t1,int t2){
    if(b==0) return a;
    return gcd(b,a%b,s2,s1-(a/b)*s2,t2,t1-(a/b)*t2);
}

int modularinv(int a,int m){
    for(int i=0;i<m;i++)
        if((a*i)%m==1) return i;
    return -1;
}

int main(){
    int p=17,q=13,m=6;
    int n=p*q,phi=(p-1)*(q-1);

    int e;
    for(e=2;e<phi;e++)
        if(gcd(e,phi,1,0,0,1)==1) break;

    int d=modularinv(e,phi);

    int c=1;
    for(int i=0;i<e;i++) c=(c*m)%n;

    int pt=1;
    for(int i=0;i<d;i++) pt=(pt*c)%n;

    printf("cipher=%d decrypted=%d\n",c,pt);
    return 0;
}