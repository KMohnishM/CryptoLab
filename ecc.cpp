#include <iostream>
using namespace std;

typedef long long ll;

struct ECPoint {
    ll x, y;
    bool inf;
};

ll normalize(ll val, ll modVal) {
    ll r = val % modVal;
    return (r >= 0) ? r : r + modVal;
}

ll inverseMod(ll val, ll modVal) {
    ll t = 0, newt = 1;
    ll r = modVal, newr = val;

    while (newr != 0) {
        ll q = r / newr;
        t = t - q * newt;
        swap(t, newt);
        r = r - q * newr;
        swap(r, newr);
    }

    if (r > 1) return -1;
    if (t < 0) t += modVal;

    return t;
}

bool validPoint(ECPoint pt, ll a, ll b, ll modVal) {
    if (pt.inf) return true;
    return normalize(pt.y * pt.y, modVal) ==
           normalize(pt.x * pt.x * pt.x + a * pt.x + b, modVal);
}

ECPoint addPoints(ECPoint p1, ECPoint p2, ll a, ll modVal) {
    if (p1.inf) return p2;
    if (p2.inf) return p1;

    if (p1.x == p2.x && p1.y != p2.y)
        return {0, 0, true};

    ll slope;

    if (p1.x == p2.x && p1.y == p2.y) {
        ll inv = inverseMod(normalize(2 * p1.y, modVal), modVal);
        if (inv == -1) return {0,0,true};
        ll num = normalize(3 * p1.x * p1.x + a, modVal);
        slope = normalize(num * inv, modVal);
    } else {
        ll inv = inverseMod(normalize(p2.x - p1.x, modVal), modVal);
        if (inv == -1) return {0,0,true};
        ll num = normalize(p2.y - p1.y, modVal);
        slope = normalize(num * inv, modVal);
    }

    ll xr = normalize(slope * slope - p1.x - p2.x, modVal);
    ll yr = normalize(slope * (p1.x - xr) - p1.y, modVal);

    return {xr, yr, false};
}

ECPoint multiplyPoint(ECPoint base, ll k, ll a, ll modVal) {
    ECPoint res = {0, 0, true};

    while (k > 0) {
        if (k & 1)
            res = addPoints(res, base, a, modVal);

        base = addPoints(base, base, a, modVal);
        k >>= 1;
    }

    return res;
}

ECPoint negatePoint(ECPoint pt, ll modVal) {
    return {pt.x, normalize(-pt.y, modVal), pt.inf};
}

int main() {
    ll a, b, modVal;
    cout << "Enter a b p: ";
    cin >> a >> b >> modVal;

    ll gx, gy;
    cout << "Enter base point G (x y): ";
    cin >> gx >> gy;

    ECPoint base = {gx, gy, false};

    ll privKey;
    cout << "Enter private key: ";
    cin >> privKey;

    ll mx, my;
    cout << "Enter message point (x y): ";
    cin >> mx >> my;

    ECPoint msg = {mx, my, false};

    ll k;
    cout << "Enter random k: ";
    cin >> k;

    if (!validPoint(base, a, b, modVal) || !validPoint(msg, a, b, modVal)) {
        cout << "Invalid point\n";
        return 0;
    }

    ECPoint pubKey = multiplyPoint(base, privKey, a, modVal);
    cout << "\nPublic Key: (" << pubKey.x << ", " << pubKey.y << ")\n";

    ECPoint c1 = multiplyPoint(base, k, a, modVal);
    ECPoint c2 = addPoints(msg, multiplyPoint(pubKey, k, a, modVal), a, modVal);

    cout << "\nCipher:\n";
    cout << "C1: (" << c1.x << ", " << c1.y << ")\n";
    cout << "C2: (" << c2.x << ", " << c2.y << ")\n";

    ECPoint temp = multiplyPoint(c1, privKey, a, modVal);
    ECPoint dec = addPoints(c2, negatePoint(temp, modVal), a, modVal);

    cout << "\nDecrypted Message:\n";
    cout << "(" << dec.x << ", " << dec.y << ")\n";

    if (dec.x == msg.x && dec.y == msg.y)
        cout << "Decryption Verified\n";
    else
        cout << "Decryption Failed\n";

    return 0;
}

