#include <bits/stdc++.h>
#define ll long long int
using namespace std;

/* 
* Fees from this Algorithm = 5713878
*
* Algorithm:
*
* 1) Sort nodes accoding to their (fees/weight) ratio in decreasing order
* 2) If top node is already visited then remove this node
* 3) Else Calculate totalWeight of unvisited nodes in its subtree
* 4) If this weight is out of limits remove this node
* 5) Else get sum of fees and weight of all unvisited nodes in its subtree and mark them as visited
* 6) After all nodes are done we stop.
*/

// This Returns total weight in the subtree of transactionId = txid
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

// This Returns total fees in the subtree of transactionId = txid and pushes the output to block.txt
ll getFees(map<string, Node> &transactionGraph, string txid, set<string> &visitedTransactions) {
    ll fees = transactionGraph[txid].fees;
    visitedTransactions.insert(txid);
    for(string parentTxid : transactionGraph[txid].parent_txids) {
        // if this parent is already done then don't consider it
        if(visitedTransactions.find(parentTxid) != visitedTransactions.end())
            continue;
        fees += getFees(transactionGraph, parentTxid, visitedTransactions);
    }

    // This transactionId will be directly pushed to block.txt
    cout << txid << endl;

    return fees;
}

void algorithm1(map<string, Node> &transactionGraph, ll MAX_WEIGHT) {
    // pair<fees/weight, txid>. we want maximum fees/weight ratio
    priority_queue<pair<double, string>> maxHeap;

    // sort transactions in decreasing order of (fees/weight) ratio using maxheap
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

        // if this transaction is already visited then continue
        if(visitedTransactions.find(txid) != visitedTransactions.end())
            continue;

        ll transactionWeight = getWeight(transactionGraph, txid, visitedTransactions);
        // if weight is too much then don't consider it
        if(transactionWeight+currentBlockWeight > MAX_WEIGHT)
            continue;

        // Take fees, weight and mark all parent transactions as visited
        currentBlockFees += getFees(transactionGraph, txid, visitedTransactions);
        currentBlockWeight += transactionWeight;
    }
}