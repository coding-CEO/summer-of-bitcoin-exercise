#include<bits/stdc++.h>
#define ll long long int
using namespace std;

// Store information about fees, weight and parent transaction ids of a transaction (node)
struct Node {
    ll fees, weight;
    vector<string> parent_txids;
};