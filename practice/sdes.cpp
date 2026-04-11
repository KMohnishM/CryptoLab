#include<iostream>
#include<vector>
using namespace std;

vector<int>permutation(vector<int>src,vector<int>map){
    vector<int>res;
    for(int i=0;i<map.size();i++){
        res.push_back(src[map[i]-1]);
    }
    return res;
} 

vector<int> executexor(vector<int>a,vector<int>b){
    vector<int>res;
    for(int i=0;i<a.size();i++){
        res.push_back((a[i]^b[i]));
    }
    return res;
}
vector<int> fetchsbox(vector<int> arr,int grid[4][4]){
int r=arr[0]*2+arr[3];
int c=arr[1]*2+arr[2];
return {grid[r][c]/2,grid[r][c]%2};
}
vector<int> swap(vector<int> a){
    return {a[4],a[5],a[6],a[7],a[0],a[1],a[2],a[3]};
}

vector<int>performfk(vector<int>left,vector<int>right,vector<int>k1){
    vector<int> exp={};
    vector<int> p4={};
    int s0[4][4]={};
    int s1[4][4]={};
    

}

