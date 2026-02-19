#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

long long power(long long base, long long exp, long long mod) {
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

vector<int> primeFactors(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        factors.push_back(n);
    return factors;
}

vector<int> primitiveRoots(int p) {
    vector<int> roots;
    int phi = p - 1;
    vector<int> factors = primeFactors(phi);

    for (int g = 2; g < p; g++) {
        bool isPrimitive = true;
        for (int f : factors) {
            if (power(g, phi / f, p) == 1) {
                isPrimitive = false;
                break;
            }
        }
        if (isPrimitive)
            roots.push_back(g);
    }
    return roots;
}

int main() {
    int p;
    cout << "Enter a prime number p: ";
    cin >> p;

    vector<int> roots = primitiveRoots(p);

    cout << "\nPrimitive Roots of " << p << ":\n";
    for (int g : roots)
        cout << g << " ";
    cout << endl;

    
    srand(time(0));
    int g = roots[0];

    cout << "\nRandomly selected primitive root g = " << g << endl;

    int a, b;
    cout << "Enter Alice's private key (a): ";
    cin >> a;
    cout << "Enter Bob's private key (b): ";
    cin >> b;

    long long A = power(g, a, p);
    long long B = power(g, b, p);

    cout << "\nAlice sends A = g^a mod p = " << A;
    cout << "\nBob sends B = g^b mod p = " << B << endl;

    long long s1 = power(B, a, p);
    long long s2 = power(A, b, p);

    cout << "\nShared Secret (Alice): " << s1;
    cout << "\nShared Secret (Bob): " << s2 << endl;

    if (s1 == s2)
        cout << "\nKey Exchange Successful ";
    else
        cout << "\nKey Exchange Failed ";

    return 0;
}
