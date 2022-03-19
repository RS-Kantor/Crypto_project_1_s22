#include "noise.h"

int calculateNoise(FreqMap &freqMap1, FreqMap &freqMap2) {
  vector<pair<char, int>> freqTable1 = freqMap1.getSingFreqSort();
  vector<pair<char, int>> freqTable2 = freqMap2.getSingFreqSort();
  int noise = 0;
  for (int i = 0; i < freqTable1.size(); i++) {
    noise += abs(freqTable1[i].second - freqTable2[i].second);
  }
  return noise;
}

string analyzeNoise(string cipher, vector<string> &candidates) {
  FreqMap freqMap(cipher);

  string bestCandidate;
  int bestDist = INT_MAX;

  for (auto candidate : candidates) {
    FreqMap candidateMap(candidate);

    int dist = calculateNoise(freqMap, candidateMap);
    if (dist < bestDist) {
      bestDist = dist;
      bestCandidate = candidate;
    }
  }

  return bestCandidate;
}