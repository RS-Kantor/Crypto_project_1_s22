#include "freq.h"

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