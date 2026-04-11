#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
typedef long long ll;
ll power_mod(ll base,ll power,ll mod){
base=base%mod;
ll res=1;
while(power){
    if(power&1)res=res*base%mod;
    base=base*base%mod;
    power>>=1;
}
return res;
}
ll mod_inv(ll a , ll b , ll t1 , ll t2){
    if(b==0){
        return t1;
    }
    return mod_inv(b,a%b,t2,t1-(a/b)*t2);
}
ll normalisze(ll a , ll p){
    a=a%p;
    if(a<0){
        return a+p;
    }
    return a;
}
vector<int> factor(int p){
    vector<int>res;
    for(int i=2;i*i<=p;i++){
        if(p%i==0){
            res.push_back(i);
            while(p%i==0)p=p/i;
        }
    }
    if(p>1){res.push_back(p);}
    return res;
}
vector<int>primitve(int p){
    vector<int> res;
    vector<int>factors=factor(p-1);
    int phi=p-1;
    for(int g=2;g<=phi;g++){
        bool ok=true;
        for(int f:factors){
            if(power_mod(g,phi/f,p)==1){
                ok=false;
            }
        }
        if(ok){
             res.push_back(g);
        }
    }
    return res;
}
int main(){ 
    // cout<<power_mod(12345,12345,1607);
    //    cout<<normalisze(mod_inv(1607,77,0,1),1607);

    //caesar
    // string pt;
    // cin>>pt;
    // int key;
    // cin>>key;

    // string ct;
    // for(int i=0;i<pt.length();i++){
    //     ct+=(((pt[i]-'A')+key)%26+'A');
    // }
    // cout<<ct;


    //vigenere
    // string pt;
    // string key;
    // cin>>pt;
    // cin>>key;
    // int k=0;
    // string ct;
    // for(int i=0;i<pt.length();i++){
    //     if(!isupper(pt[i])){
    //         pt[i]=toupper(pt[i]);
    //     }
    //     int l=key[k%key.length()]-'A';
    //     ct+=((pt[i]-'A')+l)%26+'A';
    //     k++;
    // }
    // cout<<ct;

    // vector<int>roots=primitve(1061);
    // for(int i=0;i<roots.size();i++){
    //     cout<<roots[i]<<" ";
    // }
    
    
}