#include<iostream>
using namespace std;
typedef long long ll; 
long long power_mod(ll base,ll power,ll mod){
base=base%mod;
ll res=1;
while(power){
    if(power&1){
        res=res*base%mod;
    }
    base=base*base%mod;
    power>>=1;
}
return res;
}
int gcd(ll a , ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}
ll mod_inv(ll a , ll b , ll t1 , ll t2){
    if(b==0)return t1;
    return mod_inv(b,a%b,t2,t1-(a/b)*t2);
}
int main(){
    long long p , q, x, k , m;
    cin>>p;
    cin>>q;
    if((p-1)%q!=0){
        cout<<"p-1 is not divisble by q";
        return 0;
    }
    cin>>x;
    if(x>=q||x<=1){
        cout<<"x is not in the range";
        return 0;
    }

    int g=3;
    while(power_mod(g,q,p)!=1)g++;
    ll y=power_mod(g,x,p);
    cin>>k;
    if(gcd(k,q)!=1){
        cout<<"Gcd of k and q is not 1";
        return 0;
    }
    cin>>m;
    ll k_inv=(mod_inv(q,k%q,0,1)%q+q)%q;
    ll s1=power_mod(g,k,p)%q;
    ll s2=(m+x*s1)*k_inv%q;
    ll s2_inv=(mod_inv(q,s2%q,0,1)%q+q)%q;
    ll exp1=m*s2_inv;
    ll exp2=s1*s2_inv;
    
    ll left=power_mod(g,exp1,p);
    ll right=power_mod(y,exp2,p);
    ll v=(left*right%p)%q;
    cout<<v<<" "<<s1;
    if(v==s1){
        cout<<"verified";
    }
}