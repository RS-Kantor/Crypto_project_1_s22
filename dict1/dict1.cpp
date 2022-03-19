#include "dict1.h"
#include <algorithm>
#include <climits>
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

int calculateNoise(vector<pair<char, int>> freqMap1,
                   vector<pair<char, int>> freqMap2) {
  int noise = 0;
  for (int i = 0; i < freqMap1.size(); i++) {
    noise += abs(freqMap1[i].second - freqMap2[i].second);
  }
  return noise;
}

string analyze(string cipher, vector<string> &candidates) {
  vector<pair<char, int>> freqTableCipher;
  freqsort(cipher, freqTableCipher);

  string bestCandidate;
  int bestDist = INT_MAX;

  for (auto candidate : candidates) {
    vector<pair<char, int>> freqTableCandidate;
    freqsort(candidate, freqTableCandidate);

    int dist = calculateNoise(freqTableCipher, freqTableCandidate);
    if (dist < bestDist) {
      bestDist = dist;
      bestCandidate = candidate;
    }
  }

  return bestCandidate;
}

string tryDict1(string cipher, vector<string> candidates) {
  return analyze(cipher, candidates);
}