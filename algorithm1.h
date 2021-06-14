#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll getWeight(map<string, Node> &transactionGraph, string txid, set<string> &visitedTransactions) {
    ll weight = transactionGraph[txid].weight;
    for(string parentTxid : transactionGraph[txid].parent_txids) {
        // if this parent is already done then don't consider it
        if(visitedTransactions.find(parentTxid) != visitedTransactions.end())
            continue;
        weight += getWeight(transactionGraph, parentTxid, visitedTransactions);
    }
    return weight;
}

ll getFees(map<string, Node> &transactionGraph, string txid, set<string> &visitedTransactions) {
    ll fees = transactionGraph[txid].fees;
    visitedTransactions.insert(txid);
    for(string parentTxid : transactionGraph[txid].parent_txids) {
        // if this parent is already done then don't consider it
        if(visitedTransactions.find(parentTxid) != visitedTransactions.end())
            continue;
        fees += getFees(transactionGraph, parentTxid, visitedTransactions);
    }

    // This will be directly stored in block.txt
    cout << txid << endl;
    return fees;
}

void algorithm1(map<string, Node> &transactionGraph, ll MAX_WEIGHT) {
    // pair<fees/weight, txid>. we want maximum fees/weight ratio
    priority_queue<pair<double, string>> maxHeap;

    for(auto transaction : transactionGraph) {
        double value = (double) transaction.second.fees / (double) transaction.second.weight;
        maxHeap.push({value, transaction.first});
    }

    // now, pick the best valued node and all of its parents
    ll currentBlockWeight = 0;
    ll currentBlockFees = 0;
    set<string> visitedTransactions;
    while (!maxHeap.empty()) {
        // total weight of this node and all of its unvisited parents
        pair<double, string> p = maxHeap.top();
        string txid = p.second;
        maxHeap.pop();

        // if this transaction is already done then continue
        if(visitedTransactions.find(txid) != visitedTransactions.end())
            continue;

        ll transactionWeight = getWeight(transactionGraph, txid, visitedTransactions);
        // if weight is too much then don't consider it
        if(transactionWeight+currentBlockWeight > MAX_WEIGHT)
            continue;

        // Take this and all of its parent transactions
        currentBlockFees += getFees(transactionGraph, txid, visitedTransactions);
        currentBlockWeight += transactionWeight;
    }
    // Fees from this Algorithm = 5713878
    // cout << currentBlockFees << endl;
    // cout << visitedTransactions.size() << endl;
}