#include <bits/stdc++.h>
#include "./utils/transaction_node.h"
#include "./utils/csv_handler.h"
#include "./algorithms/algorithm1.h"

#define ll long long int
using namespace std;

int main() {
    // Take input of CSV File through stdin
    freopen("./mempool.csv", "r", stdin);

    // Put output of stdout to block.txt
    freopen("./block.txt", "w", stdout);

    // Generate a Transaction Graph
    map<string, Node> transactionGraph = CSV_Handler::parseCSVFromStdIn();

    algorithm1(transactionGraph, 4000000);

    return 0;
}