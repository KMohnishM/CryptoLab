#include<iostream>
using namespace std;
typedef long long ll;
// ll mod_inv(ll a , ll b , ll t1 , ll t2){
//     if(b==0)return t1;
//     return mod_inv(b,a%b,t2,t1-(a/b)*t2);
// }
// int main(){
//     // cout<<mod_inv(1093,42,0,1);
//     char a[]={'C'};
//     cout<<a[0]-'A';
// }

ll normalisze(ll a , ll p){
    a=a%p;
    if(a<0){
        return a+p;
    }
    return a;
}

int main(){
    cout<<normalisze(378,26);
}