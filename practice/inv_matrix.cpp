#include<iostream>
#include<vector>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

int modInverse(int a, int m = 26) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

// Determinant of 3x3
int determinant3x3(vector<vector<int>> &mat) {
    int det =
        mat[0][0] * (mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1]) -
        mat[0][1] * (mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0]) +
        mat[0][2] * (mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);

    return (det % 26 + 26) % 26;
}


vector<vector<int>> inverse3x3(vector<vector<int>> &mat) {
    vector<vector<int>> inv(3, vector<int>(3));

    int det = determinant3x3(mat);
    int invDet = modInverse(det);

    if (invDet == -1) return inv;

    // Adjoint (transpose of cofactor matrix)
    inv[0][0] =  (mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1]);
    inv[0][1] = -(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0]);
    inv[0][2] =  (mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);

    inv[1][0] = -(mat[0][1]*mat[2][2] - mat[0][2]*mat[2][1]);
    inv[1][1] =  (mat[0][0]*mat[2][2] - mat[0][2]*mat[2][0]);
    inv[1][2] = -(mat[0][0]*mat[2][1] - mat[0][1]*mat[2][0]);

    inv[2][0] =  (mat[0][1]*mat[1][2] - mat[0][2]*mat[1][1]);
    inv[2][1] = -(mat[0][0]*mat[1][2] - mat[0][2]*mat[1][0]);
    inv[2][2] =  (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);

    // Transpose + multiply with inverse determinant
    vector<vector<int>> res(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i][j] = (inv[j][i] * invDet) % 26;
            res[i][j] = (res[i][j] + 26) % 26;
        }
    }

    return res;
}



int main() {
    // Hardcoded 3x3 matrix (valid Hill cipher key)
    vector<vector<int>> mat = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    cout << "Original Matrix:\n";
    for (auto &row : mat) {
        for (auto &val : row) cout << val << " ";
        cout << endl;
    }

    int det = determinant3x3(mat);
    if (modInverse(det) == -1) {
        cout << "\nMatrix is NOT invertible mod 26\n";
        return 0;
    }

    vector<vector<int>> inv = inverse3x3(mat);

    cout << "\nInverse Matrix (mod 26):\n";
    for (auto &row : inv) {
        for (auto &val : row) cout << val << " ";
        cout << endl;
    }

    return 0;
}