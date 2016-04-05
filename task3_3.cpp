#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cin;
using std::cout;

void Input (string* Line) {
     cin >> (*Line);
}


void FindPrefixFunction(const string& Line, vector<int>* PrefixFunction) {
     PrefixFunction->resize(Line.size(), 0);
     for (int SubLineEnd = 1; SubLineEnd < Line.size(); ++SubLineEnd) {
           int SubLinePrefixSuffix = PrefixFunction->at(SubLineEnd - 1);
           while ((Line.at(SubLinePrefixSuffix) != Line.at(SubLineEnd)) && 
                  (SubLinePrefixSuffix > 0)) {
                 SubLinePrefixSuffix = PrefixFunction->at(SubLinePrefixSuffix - 1);
           }
           if (SubLinePrefixSuffix > 0) {
                 PrefixFunction->at(SubLineEnd) = SubLinePrefixSuffix + 1;
           }
           else if (Line.at(0) == Line.at(SubLineEnd)) {
                 PrefixFunction->at(SubLineEnd) = 1;
           }
           else {
                 PrefixFunction->at(SubLineEnd) = 0;
           }
     }
}


void Output (const vector <int>& PrefixFunction) {
     for (int j = 0; j < PrefixFunction.size(); ++j) {
           cout << PrefixFunction.at(j) << " ";
     }
}

int main() {
     string Line;
     vector <int> PrefixFunction;
     Input(&Line);
     FindPrefixFunction(Line, &PrefixFunction);
     Output(PrefixFunction);
     return 0;
}
