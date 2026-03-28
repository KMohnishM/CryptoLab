#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// GCD
long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Extended Euclidean Algorithm (mod inverse)
long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m; a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Prime check
int isPrime(long long n) {
    if (n < 2) return 0;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

// Get next prime
long long nextPrime(long long n) {
    while (!isPrime(n)) n++;
    return n;
}

// Get prime factors of n
void getPrimeFactors(long long n, long long factors[], int *size) {
    *size = 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors[(*size)++] = i;
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        factors[(*size)++] = n;
}

// Find primitive root
long long primitiveRoot(long long p) {
    long long phi = p - 1;
    long long factors[20];
    int size;

    getPrimeFactors(phi, factors, &size);

    for (long long g = 2; g < p; g++) {
        int flag = 1;
        for (int i = 0; i < size; i++) {
            if (power(g, phi / factors[i], p) == 1) {
                flag = 0;
                break;
            }
        }
        if (flag)
            return g;
    }
    return -1;
}

// Simple hash (sum of ASCII)
long long hashMessage(char *msg) {
    long long h = 0;
    for (int i = 0; i < strlen(msg); i++)
        h += msg[i];
    return h;
}

int main() {
    long long start, p, g, x, y, k, r, s;
    char name[100];

    printf("Enter starting number (reg no): ");
    scanf("%lld", &start);
    getchar();

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    // Generate prime and primitive root
    p = nextPrime(start);
    g = primitiveRoot(p);

    // Private key (random)
    srand(time(0));
    x = rand() % (p - 2) + 1;

    // Public key
    y = power(g, x, p);

    // Hash message
    long long m = hashMessage(name) % (p - 1);

    // Choose random k
    do {
        k = rand() % (p - 2) + 1;
    } while (gcd(k, p - 1) != 1);

    // Signature
    r = power(g, k, p);
    long long k_inv = modInverse(k, p - 1);

    s = (k_inv * (m - x * r)) % (p - 1);
    if (s < 0) s += (p - 1);

    printf("\n--- Generated Values ---\n");
    printf("Prime (p): %lld\n", p);
    printf("Primitive Root (g): %lld\n", g);

    printf("\n--- Keys ---\n");
    printf("Private Key (x): %lld\n", x);
    printf("Public Key (p, g, y): (%lld, %lld, %lld)\n", p, g, y);

    printf("\n--- Message ---\n");
    printf("Name: %s\n", name);
    printf("Hash (m): %lld\n", m);

    printf("\n--- Signature ---\n");
    printf("(r, s): (%lld, %lld)\n", r, s);

    // Verification
    long long v1 = (power(y, r, p) * power(r, s, p)) % p;
    long long v2 = power(g, m, p);

    printf("\n--- Verification ---\n");
    printf("v1 = %lld\nv2 = %lld\n", v1, v2);

    if (v1 == v2)
        printf("Verification Status: SUCCESS \n");
    else
        printf("Verification Status: FAILED \n");

    return 0;
}
