#include <stdio.h>
#include <string.h>
#include <math.h>

// Fast modular exponentiation
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Check prime
int isPrime(int n) {
    if (n <= 1) return 0;
    int limit = sqrt(n);
    for (int i = 2; i <= limit; i++)
        if (n % i == 0) return 0;
    return 1;
}

// Find next prime >= n
long long nextPrime(long long n) {
    while (!isPrime(n)) n++;
    return n;
}

// GCD
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Extended Euclidean Algorithm
long long modInverse(long long e, long long phi) {
    long long t = 0, newt = 1;
    long long r = phi, newr = e;

    while (newr != 0) {
        long long q = r / newr;

        long long temp = newt;
        newt = t - q * newt;
        t = temp;

        temp = newr;
        newr = r - q * newr;
        r = temp;
    }

    if (r > 1) return -1; // no inverse
    if (t < 0) t += phi;

    return t;
}

// Simple hash (sum of ASCII values)
long long hashMessage(char *msg) {
    long long hash = 0;
    for (int i = 0; i < strlen(msg); i++)
        hash += msg[i];
    return hash;
}

int main() {
    long long start;

    printf("Enter starting number (from reg no): ");
    scanf("%lld", &start);

    // Generate primes
    long long p = nextPrime(start + 1);
    long long q = nextPrime(p + 1);

    printf("\nGenerated primes:\n");
    printf("p = %lld, q = %lld\n", p, q);

    // RSA calculations
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 3;
    while (gcd(e, phi) != 1) e++;

    long long d = modInverse(e, phi);

    printf("\nRSA Keys:\n");
    printf("Public Key (e, n): (%lld, %lld)\n", e, n);
    printf("Private Key (d, n): (%lld, %lld)\n", d, n);

    // Input name
    char name[100];
    printf("\nEnter your name: ");
    scanf(" %[^\n]", name);

    // Hashing
    long long hash = hashMessage(name);
    printf("\nMessage: %s\n", name);
    printf("Hash value: %lld\n", hash);

    // Signing
    long long signature = power(hash, d, n);
    printf("\nDigital Signature: %lld\n", signature);

    // Verification
    long long recovered = power(signature, e, n);
    printf("\nRecovered Hash: %lld\n", recovered);

    if (recovered == hash)
        printf("Verification Status: Signature Verified Successfully \n");
    else
        printf("Verification Status: Failed \n");

    return 0;
}
