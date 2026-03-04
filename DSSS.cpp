#include <iostream>

using namespace std;

// Function for Modular Exponentiation: (base^exp) % mod
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Extended Euclidean Algorithm to find GCD and coefficients x, y
long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = gcdExtended(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return gcd;
}

// Function to find Modular Multiplicative Inverse
long long modInverse(long long a, long long mod) {
    long long x, y;
    gcdExtended(a, mod, x, y);
    return (x % mod + mod) % mod;
}

int main() {
    long long p, q, g; // Domain parameters
    long long d;       // Private key
    long long hM;      // Message hash
    long long k;       // Per-message secret

    // --- Input Parameters ---
    cout << "Enter prime p: ";
    cin >> p;

    cout << "Enter prime q (q divides p-1): ";
    cin >> q;

    cout << "Enter generator g: ";
    cin >> g;

    cout << "Enter private key d (d < q): ";
    cin >> d;

    // --- Key Generation ---
    // Public key e2 = g^d mod p
    long long e2 = powerMod(g, d, p);
    cout << "\nPublic Key (e2) = " << e2 << endl;

    // --- Signing Process ---
    cout << "\nEnter message hash h(M): ";
    cin >> hM;

    cout << "Enter random value k (1 < k < q): ";
    cin >> k;

    // S1 = (g^k mod p) mod q
    long long S1 = powerMod(g, k, p) % q;

    // S2 = [k^-1 * (h(M) + d*S1)] mod q
    long long k_inv = modInverse(k, q);
    long long S2 = ((hM + (d * S1) % q) * k_inv) % q;

    cout << "\n--- Signature ---" << endl;
    cout << "S1 = " << S1 << endl;
    cout << "S2 = " << S2 << endl;

    // --- Verification Process ---
    // w = S2^-1 mod q
    long long w = modInverse(S2, q);

    // u1 = (h(M) * w) mod q
    long long u1 = (hM * w) % q;

    // u2 = (S1 * w) mod q
    long long u2 = (S1 * w) % q;

    // v = [(g^u1 * e2^u2) mod p] mod q
    long long v1 = powerMod(g, u1, p);
    long long v2 = powerMod(e2, u2, p);
    long long V = ((v1 * v2) % p) % q;

    cout << "\n--- Verification ---" << endl;
    cout << "V = " << V << endl;

    if (V == S1)
        cout << "Signature Verified (Valid)" << endl;
    else
        cout << "Signature Invalid" << endl;

    return 0;
}