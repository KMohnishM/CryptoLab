#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> rotateBits(vector<int> block, int step) {
    int sz = block.size();
    vector<int> valSet(sz);
    for (int i = 0; i < sz; i++)
        valSet[i] = block[(i + step) % sz];
    return valSet;
}

vector<int> executeXor(vector<int> alpha, vector<int> beta) {
    vector<int> valSet(alpha.size());
    for (int i = 0; i < alpha.size(); i++)
        valSet[i] = alpha[i] ^ beta[i];
    return valSet;
}

vector<int> switchSides(vector<int> fullBlock) {
    return {fullBlock[4], fullBlock[5], fullBlock[6], fullBlock[7],
            fullBlock[0], fullBlock[1], fullBlock[2], fullBlock[3]};
}

vector<int> fetchSBox(vector<int> nibble, int grid[4][4]) {
    int rIdx = nibble[0] * 2 + nibble[3];
    int cIdx = nibble[1] * 2 + nibble[2];
    int entry = grid[rIdx][cIdx];
    return {entry / 2, entry % 2};
}

vector<int> applyPermutation(vector<int> src, vector<int> map) {
    vector<int> valSet(map.size());
    for (int i = 0; i < map.size(); i++)
        valSet[i] = src[map[i] - 1];
    return valSet;
}

void display(string label, vector<int> vec) {
    cout << label << ": ";
    for (int b : vec) cout << b;
    cout << endl;
}

vector<int> performFk(vector<int> lPart, vector<int> rPart, vector<int> subKey) {
    vector<int> ep_map = {4, 1, 2, 3, 2, 3, 4, 1};
    vector<int> p4_map = {2, 4, 3, 1};
    int box0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    int box1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

    vector<int> expansion = applyPermutation(rPart, ep_map);
    expansion = executeXor(expansion, subKey);
    vector<int> dLeft(expansion.begin(), expansion.begin() + 4);
    vector<int> dRight(expansion.begin() + 4, expansion.end());
    vector<int> oS0 = fetchSBox(dLeft, box0);
    vector<int> oS1 = fetchSBox(dRight, box1);
    vector<int> combinedS = {oS0[0], oS0[1], oS1[0], oS1[1]};
    combinedS = applyPermutation(combinedS, p4_map);
    vector<int> xorResult = executeXor(lPart, combinedS);

    vector<int> finalFk = {xorResult[0], xorResult[1], xorResult[2], xorResult[3],
                           rPart[0], rPart[1], rPart[2], rPart[3]};
    return finalFk;
}

int main() {
    vector<int> p10_rules = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> p8_rules = {6, 3, 7, 4, 8, 5, 10, 9};
    vector<int> init_p = {2, 6, 3, 1, 4, 8, 5, 7};
    vector<int> inv_p = {4, 1, 3, 5, 7, 2, 8, 6};

    vector<int> masterKey(10), rawData(8);
    cout<<"Enter Key (10bits) : ";
    for (int i = 0; i < 10; i++) cin >> masterKey[i];
    cout<<"Enter Plain Text(8bits) : ";
    for (int i = 0; i < 8; i++) cin >> rawData[i];

    masterKey = applyPermutation(masterKey, p10_rules);
    vector<int> sideA(masterKey.begin(), masterKey.begin() + 5);
    vector<int> sideB(masterKey.begin() + 5, masterKey.end());

    sideA = rotateBits(sideA, 1);
    sideB = rotateBits(sideB, 1);
    vector<int> joined1 = sideA;
    joined1.insert(joined1.end(), sideB.begin(), sideB.end());
    vector<int> keyGen1 = applyPermutation(joined1, p8_rules);
    display("K1", keyGen1);

    sideA = rotateBits(sideA, 2);
    sideB = rotateBits(sideB, 2);
    vector<int> joined2 = sideA;
    joined2.insert(joined2.end(), sideB.begin(), sideB.end());
    vector<int> keyGen2 = applyPermutation(joined2, p8_rules);
    display("K2", keyGen2);

    vector<int> processing = applyPermutation(rawData, init_p);
    display("IP", processing);

    vector<int> head1(processing.begin(), processing.begin() + 4);
    vector<int> tail1(processing.begin() + 4, processing.end());
    vector<int> stage1 = performFk(head1, tail1, keyGen1);
    display("Round 1", stage1);

    stage1 = switchSides(stage1);
    display("Swap", stage1);

    vector<int> head2(stage1.begin(), stage1.begin() + 4);
    vector<int> tail2(stage1.begin() + 4, stage1.end());
    vector<int> stage2 = performFk(head2, tail2, keyGen2);
    display("Round 2", stage2);

    vector<int> finalResult = applyPermutation(stage2, inv_p);
    display("Cipher", finalResult);

    return 0;
}
