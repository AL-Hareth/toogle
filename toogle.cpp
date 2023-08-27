#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> getSignatures(string filename) {
    vector<string> signatures;

    // initialize readers
    ifstream stream(filename);
    string line;

    while (getline(stream, line)) {
        // skip lines that does not contain the word function
        if(line.substr(0, 8) != "function") {
            continue;
        }

        // push the function signature to the vector
        signatures.push_back(line.substr(9));
    }
    // close readers
    stream.close();
    return signatures;
}

vector<string> getSearchResults(vector<string> signatures, string search) {

    vector<string> matched;

    for(int i = 0; i < signatures.size(); i++) {
        if(signatures[i].find(search) == string::npos) {
            continue;
        }

        matched.push_back(signatures[i]);
    }

    return matched;
}

vector<string> getSearchParametersTypes(string searchQuery) {
    int leftParenthesis = searchQuery.find(")");
    string type;
    vector<string> paramsTypes;

    for(int i = 1; i < searchQuery.size(); i++) {
        if(i == leftParenthesis) {
            paramsTypes.push_back(type);
            break;
        }

        if(searchQuery[i] == ',') {
            paramsTypes.push_back(type);
            type = "";
            continue;
        }

        type = type + searchQuery[i];
    }

    return paramsTypes;
}

regex generateRegexFromSearch(string searchQuery) {
    vector<string> paramsTypes = getSearchParametersTypes(searchQuery); // {number, number}

    string returnType = searchQuery.substr(searchQuery.find_last_of(":")+2);
    string regexString = "[\\w]+\\(";
    for(int i = 0; i < paramsTypes.size(); i++) {
        if(i != paramsTypes.size() - 1) {
            regexString = regexString + "[\\w]+: " + paramsTypes[i] + ", ";
        } else {
            regexString = regexString + "[\\w]+: " + paramsTypes[i];
        }
    }
    regexString = regexString + "\\): " + returnType + " \\{";

    return regex(regexString);
}

int main(int argc, char *argv[]) {

    cout << "Insert a search with this format: (type1,type2,type3): return_type" << endl;
    string search;
    getline(cin, search);

    // Generate a regex for the search query
    regex searchRegex = generateRegexFromSearch(search);

    vector<string> signatures = getSignatures(argv[1]);

    cout << endl << "==========These Functions Matched Your Search==========" << endl;
    for(int i = 0; i < signatures.size(); i++) {
        if(regex_match(signatures[i], searchRegex)) {
            cout << signatures[i] << endl;
        }
    }


    return 0;
}
