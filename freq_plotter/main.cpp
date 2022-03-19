#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void createFreqMap(string x, map<char, int> &freqMap) {
  for (int i = 0; i < x.length(); i++) {
    if (freqMap.find(x[i]) != freqMap.end()) {
      freqMap[x[i]] += 1;
    } else {
      freqMap[x[i]] = 1;
    }
  }
}

bool cmp(pair<char, int> a, pair<char, int> b) { return a.second > b.second; }

void freqsort(string x, vector<pair<char, int>> &out) {
  map<char, int> freqMap;
  createFreqMap(x, freqMap);

  for (auto i : freqMap) {
    out.push_back(i);
  }

  sort(out.begin(), out.end(), cmp);
}

int main() {
  ifstream infile("../dictionary_2.txt");
  string fin;
  string c;
  while (getline(infile, c)) {
    if (c[0] <= 'z' && c[0] >= 'a') {
      fin += c;
    }
  }

  vector<pair<char, int>> freqTableAll;
  freqsort(fin, freqTableAll);

  for (int i = 0; i < freqTableAll.size(); i++) {
    cout << freqTableAll[i].first << " " << freqTableAll[i].second << endl;
  }
  return 0;
}