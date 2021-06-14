#include <bits/stdc++.h>
#include "./csv_handler.h"

#define ll long long int
using namespace std;

int main() {
    // Take input of CSV File through stdin
    freopen("./temp/mempool.csv", "r", stdin);
    // Put output of stdout to block.txt
    // freopen("./block.txt", "w", stdout);
    map<string, Node> transactionGraph = CSV_Handler::parseCSVFromStdIn();
    
    return 0;
}