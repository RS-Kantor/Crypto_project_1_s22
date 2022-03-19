#include "noise.h"

int calculateNoise(vector<pair<char, int>> freqMap1,
                   vector<pair<char, int>> freqMap2, float paddingLength) {
  int limit =
      (paddingLength < 0.12)
          ? freqMap1.size()
          : 3; // if random strings are more than 10% of the length of the
               // candidate, then we use the top 5 most frequent characters
  int noise = 0;
  for (int i = 0; i < limit; i++) {
    noise += abs(freqMap1[i].second - freqMap2[i].second);
  }
  return noise;
}

string analyzeNoise(string cipher, vector<string> &candidates) {
  vector<pair<char, int>> freqTableCipher;
  freqsort(cipher, freqTableCipher);

  string bestCandidate;
  int bestDist = INT_MAX;

  for (auto candidate : candidates) {
    vector<pair<char, int>> freqTableCandidate;
    freqsort(candidate, freqTableCandidate);

    int dist = calculateNoise(freqTableCipher, freqTableCandidate,
                              (float)(cipher.length() - candidate.length()) /
                                  candidate.length());
    if (dist < bestDist) {
      bestDist = dist;
      bestCandidate = candidate;
    }
  }

  return bestCandidate;
}