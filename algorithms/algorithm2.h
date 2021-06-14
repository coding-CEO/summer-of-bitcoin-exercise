#include <bits/stdc++.h>
#define ll long long int
using namespace std;

/*
* Fees from this Algorithm = 5846859
*
* Algorithm:
*
* 1) Take all nodes in the graph with indegree = 0
* 2) these nodes will be roots of their respective trees
* 3) Apply a DFS and for each node in their trees - find the totalWeight and totalFees in its subtree
* 4) Sort root nodes accoding to (totalFees/totalWeight) ratio in decreasing order
* 5) if the totalWeight of top node is within limits then take its whole subtree and add its topological ordering in block.txt
* 6) else remove this node and add its parent nodes and sort again
* 7) After all root nodes are done we stop.
*/

// Store information of complete subtree of node
struct NodeSubtree {
    ll totalFees = 0, totalWeight = 0;
};

// find totalWeight and totalFees in the subtree of transactionId = txid and store it.
void populateTransactionSubtreeInformation(map<string, Node> &transactionGraph, string txid, ll &subtreeFees, ll &subtreeWeight, map<string, NodeSubtree> &transactionSubtree) {
    for(string parentTxid : transactionGraph[txid].parent_txids) {
        ll subFees = 0, subWeight = 0;
        populateTransactionSubtreeInformation(transactionGraph, parentTxid, subFees, subWeight, transactionSubtree);
        subtreeFees += subFees;
        subtreeWeight += subWeight;
    }
    subtreeFees += transactionGraph[txid].fees;
    subtreeWeight += transactionGraph[txid].weight;

    transactionSubtree[txid].totalFees = subtreeFees;
    transactionSubtree[txid].totalWeight = subtreeWeight;
}

// Add topological sorting of the graph in block.txt
void printTopologicalSort(map<string, Node> &transactionGraph, string txid) {
    for(string parentTxid : transactionGraph[txid].parent_txids) {
        printTopologicalSort(transactionGraph, parentTxid);
    }

    // This transaction id will direct get added to block.txt file
    cout << txid << endl;
}

void algorithm2(map<string, Node> &transactionGraph, ll MAX_WEIGHT) {
    // store indegree of every node in graph
    map<string, ll> transactionIndegree;
    for(auto transaction : transactionGraph) {
        // initializa indegree to 0
        transactionIndegree[transaction.first] = 0LL;
    }

    for(auto transaction : transactionGraph) {
        for(string parentTxid : transaction.second.parent_txids)
            transactionIndegree[parentTxid]++; // increament indegree
    }

    // root transaction are the transactions with indegree == 0;
    vector<string> rootTransactions;
    for(auto transactionInfo : transactionIndegree) {
        if(transactionInfo.second != 0) continue;
        rootTransactions.push_back(transactionInfo.first); // store all root transactions
    }
    
    map<string, NodeSubtree> transactionSubtree; // store information about subtree of every node
    priority_queue<pair<double, string>> maxHeap; // pair<(totalFees/totalWeight), txid> in decreasing order
    for(string rootTransaction : rootTransactions) {
        ll subtreeFees = 0, subtreeWeight = 0;
        populateTransactionSubtreeInformation(transactionGraph, rootTransaction, subtreeFees, subtreeWeight, transactionSubtree);
        double value = (double)transactionSubtree[rootTransaction].totalFees/(double)transactionSubtree[rootTransaction].totalWeight;
        maxHeap.push({value, rootTransaction});
    }

    // now take subtrees from transactionGraph instead of indivisual transaction
    ll currentBlockWeight = 0;
    ll currentBlockFees = 0;
    while(!maxHeap.empty()) {
        pair<double, string> p = maxHeap.top();
        string txid = p.second;
        maxHeap.pop();

        // If weight of this subtree is too much
        if(transactionSubtree[txid].totalWeight + currentBlockWeight > MAX_WEIGHT) {
            // push its parent transactions in the maxHeap
            for(string parentTxid : transactionGraph[txid].parent_txids) {
                double value = (double)transactionSubtree[parentTxid].totalFees/(double)transactionSubtree[parentTxid].totalWeight;
                maxHeap.push({value, parentTxid});
            }
            continue;
        }

        // weight was in the limits so, get whole subtree of this node
        currentBlockWeight += transactionSubtree[txid].totalWeight;
        currentBlockFees += transactionSubtree[txid].totalFees;
        
        // add this subtree in block.txt
        printTopologicalSort(transactionGraph, txid);
    }
}