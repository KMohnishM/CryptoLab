#include<stdio.h>

// Recursive Extended Euclidean Algorithm
int extendedEuclid(int a, int b, int t1, int t2){

    // Base case
    if(b == 0)
        return t1;

    return extendedEuclid(
        b,
        a % b,
        t2,
        t1 - (a / b) * t2
    );
}

// Modular inverse
int modularinv(int a, int m){

    // Inverse exists only if gcd(a,m)=1
    int x = a;
    int y = m;

    while(y != 0){
        int t = y;
        y = x % y;
        x = t;
    }

    if(x != 1)
        return -1;

    int ans = extendedEuclid(m, a, 0, 1);

    return (ans % m + m) % m;
}

int main(){

    int p = 23, g = 5, x = 6, k = 7, m = 7;

    // Public key
    int y = 1;

    for(int i = 0; i < x; i++)
        y = (y * g) % p;

    // Encryption
    int c1 = 1, c2 = 1;

    for(int i = 0; i < k; i++){

        c1 = (c1 * g) % p;
        c2 = (c2 * y) % p;
    }

    c2 = (c2 * m) % p;

    // Decryption
    int s = 1;

    for(int i = 0; i < x; i++)
        s = (s * c1) % p;

    int s_inv = modularinv(s, p);

    if(s_inv == -1){

        printf("Modular inverse does not exist\n");
        return 0;
    }

    int dec = (c2 * s_inv) % p;

    printf("c1 = %d\n", c1);
    printf("c2 = %d\n", c2);
    printf("decrypted = %d\n", dec);

    return 0;
}