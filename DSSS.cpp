#include <iostream>
#include <algorithm> // for __gcd
using namespace std;

// Fast modular exponentiation
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Extended Euclidean Algorithm
long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = gcdExtended(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// Modular inverse
long long modInverse(long long a, long long mod) {
    long long x, y;
    long long g = gcdExtended(a, mod, x, y);

    if (g != 1) return -1; // inverse doesn't exist
    return (x % mod + mod) % mod;
}

int main() {
    long long p, q, g;
    long long d;     // private key
    long long hM;    // message hash
    long long k;     // random value

    cout << "Enter prime p: ";
    cin >> p;

    cout << "Enter prime q (q divides p-1): ";
    cin >> q;

    // Check q divides p-1
    if ((p - 1) % q != 0) {
        cout << "Error: q must divide (p-1)\n";
        return 0;
    }

    cout << "Enter generator g: ";
    cin >> g;

    // Check generator condition
    if (powerMod(g, q, p) != 1) {
        cout << "Error: g^q mod p must be 1\n";
        return 0;
    }

    cout << "Enter private key d (1 < d < q): ";
    cin >> d;

    if (d <= 1 || d >= q) {
        cout << "Error: Invalid private key\n";
        return 0;
    }

    // Public key
    long long e2 = powerMod(g, d, p);
    cout << "\nPublic Key (p, q, g, y): (" << p << ", " << q << ", " << g << ", " << e2 << ")\n";

    cout << "\nEnter message hash h(M): ";
    cin >> hM;

    cout << "Enter random k (1 < k < q and gcd(k,q)=1): ";
    cin >> k;

    if (k <= 1 || k >= q || __gcd(k, q) != 1) {
        cout << "Error: Invalid k\n";
        return 0;
    }

    // --- Signature ---
    long long S1 = powerMod(g, k, p) % q;
    long long k_inv = modInverse(k, q);

    if (k_inv == -1) {
        cout << "Error: k inverse doesn't exist\n";
        return 0;
    }

    long long S2 = (k_inv * (hM + d * S1)) % q;

    if (S1 == 0 || S2 == 0) {
        cout << "Error: Invalid signature values (S1 or S2 = 0)\n";
        return 0;
    }

    cout << "\n--- Signature ---\n";
    cout << "S1 = " << S1 << "\n";
    cout << "S2 = " << S2 << "\n";

    // --- Verification ---
    long long w = modInverse(S2, q);
    if (w == -1) {
        cout << "Error: S2 inverse doesn't exist\n";
        return 0;
    }

    long long u1 = (hM * w) % q;
    long long u2 = (S1 * w) % q;

    long long v1 = powerMod(g, u1, p);
    long long v2 = powerMod(e2, u2, p);

    long long V = ((v1 * v2) % p) % q;

    cout << "\n--- Verification ---\n";
    cout << "V = " << V << "\n";

    if (V == S1)
        cout << "Signature Verified (Valid) \n";
    else
        cout << "Signature Invalid \n";

    return 0;
}
