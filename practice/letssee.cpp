#include<iostream>
#include<vector>
using namespace std;


// 27 5 2 0 1 -4
// 5 2  1 1 -4  9
// 2 1  0 -4 9 -22
// 1 0    9 -22 
int pow_mod(int base , int power , int p){
base=base%p;
int res=1;
while(power){
    if(power&1){
        res=res*base%p;
    }
    base=base*base%p;
    power>>=1;
}
return res;
}
int mod_inv(int a, int b , int t1 , int t2){
    if(b==0){
        return t1;
    }
    return mod_inv(b,a%b,t2,t1-(a/b)*t2);
}

int gcd(int a,int b){
    if(b==0){
        return a;
    }
    return gcd(b,a%b);
}

// RSA - p q n=p*q  ,phi = p-1*q-1 , gcd(e,phi)=1 , d=mod_inv(e,phi), S=M^dmod p , m1=S^emodp  , S==m1
// int main(){
//     int p,q,n,phi;
//     cin>>p>>q;
//     n=p*q;
//     phi=(p-1)*(q-1);
//     int e=3;
//     while(gcd(e,phi)!=1)e++;
//     int d=mod_inv(e,phi,0,1);
//     int M;
//     cin>>M;
//     int S=(M,d,n);
//     int m1=(S,e,n);
//     printf("%d\n",S);
//     printf("%d",m1);
//     if(S==m1){
//         printf("Verified");
//     }
// }



 
// Elgamel 
// vector<int>factor(int p){
//     vector<int>ans;
//     for(int i=2;i*i<=p;i++){
//         if(p%i==0){
//             ans.push_back(i);
//             while(p%i==0)p=p/i;
//         }
//     }
//     if(p>1)ans.push_back(p);
//     return ans;
// }

// vector<int>primitive(int p){
//     vector<int>factors=factor(p-1);
//     vector<int>ans;
//     int phi=p-1;
//     for(int g=2;g<phi;g++){
//         bool ok=true;
//         for(int f: factors){
//             if(pow_mod(g,phi/f,p)==1){
//                 ok=false;
//                 break;
//             }
//         }
//         if(ok){
//             ans.push_back(g);
//         }
//     }
//     return ans;
// }


// //Elgamel p , g->primitive root of p, x , k , y=g^x mod p , S1= g^k mod p , S2=(M-xS1)k^-1 mod p , V1=S1^yS2^S1modp , V2=g^M mod p , V1==V@
// int main(){
//     int p , g , x;
//     cin>>p;
//     vector<int>roots=primitive(p);
//     if(roots.empty()){
//         cout << "No primitive root found for p=" << p << endl;
//         return 1;
//     }
//     g=roots[0];
//     cin>>x;
//     int k;
//     cin>>k;
//     int y=pow_mod(g,x,p)%p;
//     int s1=pow_mod(g,k,p)%p;
//     int k_inv=mod_inv(k,p-1,0,1);
//     // Ensure k_inv is positive modulo (p-1)
//     k_inv = (k_inv % (p-1) + (p-1)) % (p-1);
//     int M;
//     cin>>M;
//     int s2 = ( ( (M - x*s1) % (p-1) + (p-1) ) % (p-1) ) * k_inv % (p-1);
//     // Ensure s2 is positive
//     s2 = (s2 + (p-1)) % (p-1);
//     int v1=pow_mod(s1,y,p)*pow_mod(s2,s1,p)%p;
//     int v2=pow_mod(g,M,p);

//     cout<<v1<<" "<<v2;
//     if(v1==v2){
//         cout<<"Verified";
//     }
// }

// DSSS p , q -> divisble by p-1 , g => g^q mod p =1 , x=>1<x<q , k => gcd(k,q)=1  , y=g^x mod p , s1=g^kmodq , s2=(h(m)+xS1)k^-1 mod q mod p , v=s1^y*(s2^-1modq) modp * s2^s1*(s2^-1modq) mod p  ,v==s1

int main(){
    int p, q, g, x, y;
    cin >> p >> q;
    if ((p - 1) % q != 0) {
        cout << "q does not divide p-1" << endl;
        return 0;
    }
    // Find a generator g such that g^q mod p == 1
    g = 2;
    while (pow_mod(g, q, p) != 1) g++;
    cout << "Generator g: " << g << endl;
    cout << "Enter private key x (1 < x < q): ";
    cin >> x;
    if (x <= 1 || x >= q) {
        cout << "x must be in (1, q)" << endl;
        return 0;
    }
    cout << "Enter random k (1 < k < q, gcd(k,q)=1): ";
    int k;
    cin >> k;
    if (k <= 1 || k >= q || gcd(k, q) != 1) {
        cout << "k must be in (1, q) and gcd(k, q) = 1" << endl;
        return 0;
    }
    y = pow_mod(g, x, p); // public key
    cout << "Enter message hash m (as integer): ";
    int m;
    cin >> m;
    // Signature generation
    int s1 = pow_mod(g, k, p) % q;
    int k_inv = mod_inv(q, k, 0, 1);
    k_inv = (k_inv % q + q) % q;
    int s2 = (k_inv * (m + x * s1)) % q;
    cout << "Signature: (" << s1 << ", " << s2 << ")" << endl;
    // Signature verification
    if (s1 <= 0 || s1 >= q || s2 <= 0 || s2 >= q) {
        cout << "Invalid signature values." << endl;
        return 0;
    }
    int w = mod_inv(q, s2%q, 0, 1);
    w = (w % q + q) % q;
    int u1 = (m * w) % q;
    int u2 = (s1 * w) % q;
    int v = ((pow_mod(g, u1, p) * pow_mod(y, u2, p)) % p) % q;
    cout << "Verification v: " << v << endl;
    if (v == s1) {
        cout << "\nSignature Verified" << endl;
    } else {
        cout << "\nSignature NOT Verified" << endl;
    }
}