#include<stdio.h>

int modularinv(int a,int m){
    for(int i=0;i<m;i++)
        if((a*i)%m==1) return i;
    return -1;
}

int crt(int *m,int *a){
    int M=1,ans=0;
    for(int i=0;i<3;i++) M*=m[i];
    for(int i=0;i<3;i++){
        int temp=M/m[i];
        ans+=a[i]*temp*modularinv(temp,m[i]);
    }
    return ans%M;
}

int main(){
    int m[3]={3,5,7};
    int a[3]={2,4,6};
    printf("%d\n",crt(m,a));
    return 0;
}