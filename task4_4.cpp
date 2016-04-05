#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::min;

void Input (string* Line) {
    cin >> (*Line);
}


void FindZFunction (const string &Line, vector <int>* ZFunction) {
    ZFunction->resize(Line.size(), 0);
    int LeftBound = 0;
    int RightBound = 0;
    int MaximalK_RepeatPrefix = 1;
    (*ZFunction)[0] = Line.size();
    for (int Index = 1; Index < ZFunction->size(); ++Index) {
        if (RightBound > Index) {
            (*ZFunction)[Index] = min((*ZFunction)[Index - LeftBound], RightBound - Index);
        }
        while ((Index + (*ZFunction)[Index] < Line.size()) && 
               (Line.at(Index + (*ZFunction)[Index]) == Line.at((*ZFunction)[Index]))) {
                   ++(*ZFunction)[Index];
        }
        if (Index + (*ZFunction)[Index] > RightBound) {
            RightBound = Index + (*ZFunction)[Index];
            LeftBound = Index;
        }
    }
}


int FindMaximalKRepeat(const string &Line) {
    int MaximalKRepeat = 1;
    for (size_t BeginIndex = 0; BeginIndex < Line.size(); ++BeginIndex) {
        vector<int> ZFunction;
        FindZFunction(Line.substr(BeginIndex, Line.size() - BeginIndex), &ZFunction);
        for (size_t ZFunctionIndex = 1; ZFunctionIndex < ZFunction.size(); ++ZFunctionIndex) {
            if (ZFunction[ZFunctionIndex] / ZFunctionIndex + 1 > MaximalKRepeat) {
                MaximalKRepeat = ZFunction[ZFunctionIndex] / ZFunctionIndex + 1;
            }
        }
    }
    return MaximalKRepeat;
}


void Output (const int MaximalKRepeat) {
    cout << MaximalKRepeat;
}


int main() {
    string Line;
    Input(&Line);
    Output(FindMaximalKRepeat(Line));
    return 0;
}
