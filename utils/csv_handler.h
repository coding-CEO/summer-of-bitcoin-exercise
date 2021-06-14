#include<bits/stdc++.h>
#define ll long long int
using namespace std;

class CSV_Handler {
private:
    static string splitter(string &line, char delimiter, vector<string> &information) {
        string info = "";
        for(char c : line) {
            if(c == delimiter) {
                information.push_back(info); // store information
                info = ""; // reset information
                continue;
            }
            info += c; // push characters in line to info
        }
        return info; // return information after last delimiter
    }

    static void extractInformationFromLine(string &line, map<string, Node> &graph) {
        vector<string> transactionInformation;
        // Here parentString contains data about parents of this transaction
        string parentString = splitter(line, ',', transactionInformation); // split line at ','
        
        vector<string> parentList; // store txid of all its parents
        if(parentString.size() > 0) {
            string lastParent = splitter(parentString, ';', parentList); // split line at ';'
            parentList.push_back(lastParent);
        }

        // Here,
        // transactionInformation vector contains data about txid, fees, weight
        // parentList contains txid of all parents
        Node node;
        node.fees = atoll(transactionInformation[1].c_str()); // convert string to int
        node.weight = atoll(transactionInformation[2].c_str()); // convert string to int
        node.parent_txids = parentList;

        // for the given transaction id store information in node
        graph[transactionInformation[0]] = node;
    }

public:
    static map<string, Node> parseCSVFromStdIn() {
        string line; // store every line of csv
        cin >> line; // ignore the titles in csv
        
        map<string, Node> graph; // Convert whole transaction system to a graph
        while(cin >> line) {
            extractInformationFromLine(line, graph);
        }
        return graph;
    }
};