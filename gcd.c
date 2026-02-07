#include<stdio.h>

int gcd(int a,int b){
    if(b==0){
        return a;
    }
    return gcd(b,a%b);
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    if(n<m){
    int temp=m;
    m=n;
    n=temp;
    }
    printf("%d\n",gcd(n,m));

    return 0;
}