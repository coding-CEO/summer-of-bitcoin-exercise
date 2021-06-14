#include<bits/stdc++.h>
#define ll long long int
using namespace std;

class CSV_Handler {
private:
    static string splitter(string &line, char delimiter, vector<string> &information) {
        string info = "";
        for(char c : line) {
            if(c == delimiter) {
                information.push_back(info);
                info = "";
                continue;
            }
            info += c;
        }
        return info;
    }
    static void extractInformationFromLine(string &line, map<string, Node> &graph) {
        vector<string> transactionInformation;
        // Here parentString contains data about parents of this transaction
        string parentString = splitter(line, ',', transactionInformation);
        vector<string> parentList;

        if(parentString.size() > 0) {
            string lastParent = splitter(parentString, ';', parentList);
            parentList.push_back(lastParent);
        }

        // transactionInformation vector contains data about txid, fees, weight
        // parentList contains txid of all parents
        Node node;
        node.fees = atoll(transactionInformation[1].c_str()); // convert string to int
        node.weight = atoll(transactionInformation[2].c_str()); // convert string to int
        node.parent_txids = parentList;

        graph[transactionInformation[0]] = node;
    }
public:
    static map<string, Node> parseCSVFromStdIn() {
        string line;
        cin >> line; // ignore the titles in csv
        
        map<string, Node> graph;
        while(cin >> line) {
            extractInformationFromLine(line, graph);
        }
        return graph;
    }
};