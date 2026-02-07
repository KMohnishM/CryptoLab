#include<stdio.h>

int gcd(int a,int b,int s1,int s2,int t1,int t2){
    if(b==0){
        printf("s=%d t=%d\n",s1,t1);
        return a;
    }
    return gcd(b,a%b,s2,s1-(a/b)*s2,t2,t1-(a/b)*t2);
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    if(n<m){
    int temp=m;
    m=n;
    n=temp;
    }
    printf("gcd = %d\n",gcd(n,m,1,0,0,1));
    return 0;
}