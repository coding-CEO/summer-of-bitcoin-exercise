#include <bits/stdc++.h>
#include "./transaction_node.h"
#include "./csv_handler.h"
#include "./algorithm1.h"

#define ll long long int
using namespace std;

int main() {
    // Take input of CSV File through stdin
    freopen("./temp/mempool.csv", "r", stdin);
    // Put output of stdout to block.txt
    freopen("./block.txt", "w", stdout);

    map<string, Node> transactionGraph = CSV_Handler::parseCSVFromStdIn();
    
    algorithm1(transactionGraph, 4000000);

    return 0;
}