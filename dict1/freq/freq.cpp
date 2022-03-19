#include "freq.h"

bool cmp(pair<char, int> a, pair<char, int> b) { return a.second > b.second; }
bool cmpStr(pair<string, int> a, pair<string, int> b) {
  return a.second > b.second;
}

map<char, int> singFreqMap;
map<string, int> diaFreqMap;

FreqMap::FreqMap(string text) {
  for (int i = 0; i < text.length(); i++) {
    if (singFreqMap.find(text[i]) == singFreqMap.end()) {
      singFreqMap[text[i]] = 1;
    } else {
      singFreqMap[text[i]] += 1;
    }
  }
  for (int i = 0; i < text.length() - 1; i++) {
    string s = text.substr(i, 2);
    if (diaFreqMap.find(s) == diaFreqMap.end()) {
      diaFreqMap[s] = 1;
    } else {
      diaFreqMap[s] += 1;
    }
  }
}

vector<pair<char, int>> FreqMap::getSingFreqSort() {
  vector<pair<char, int>> freqTable;
  for (auto i : singFreqMap) {
    freqTable.push_back(i);
  }
  sort(freqTable.begin(), freqTable.end(), cmp);
  return freqTable;
}

vector<pair<string, int>> FreqMap::getDiaFreqSort() {
  vector<pair<string, int>> freqTable;
  for (auto i : diaFreqMap) {
    freqTable.push_back(i);
  }
  sort(freqTable.begin(), freqTable.end(), cmpStr);
  return freqTable;
}