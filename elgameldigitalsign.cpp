#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}


int findPrime4m1(int start) {
    int p = start;
    while (true) {
        if (p % 4 == 1 && isPrime(p))
            return p;
        p++;
    }
}


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


vector<int> primeFactors(int n) {
    vector<int> f;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            f.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}


vector<int> primitiveRoots(int p) {
    vector<int> roots;
    int phi = p - 1;
    vector<int> factors = primeFactors(phi);

    for (int g = 2; g < p; g++) {
        bool ok = true;
        for (int f : factors) {
            if (power(g, phi / f, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) roots.push_back(g);
    }
    return roots;
}

int main() {
    long long roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    int last4 = roll % 10000;
    int p = findPrime4m1(last4);

    cout << "\nLast 4 digits: " << last4;
    cout << "\nPrime (4m + 1) chosen: p = " << p << endl;

    vector<int> roots = primitiveRoots(p);

    cout << "\nPrimitive Roots of " << p << ":\n";
    for (int g : roots) cout << g << " ";
    cout << endl;

    srand(time(0));
    int g = roots[0];
    cout << "\nRandomly selected primitive root g = " << g << endl;

    int a, b;
    cout << "\nEnter Alice private key a: ";
    cin >> a;
    cout << "Enter Bob private key b: ";
    cin >> b;

    long long A = power(g, a, p);
    long long B = power(g, b, p);

    cout << "\nAlice sends A = " << A;
    cout << "\nBob sends B = " << B << endl;

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
