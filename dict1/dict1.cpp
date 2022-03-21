#include "dict1.h"

using namespace std;

string tryDict1(string cipher, vector<string> candidates) {
  if ((float)(cipher.length() - candidates[0].length()) /
          candidates[0].length() <
      0.15) {
    return analyzeNoise(cipher, candidates);
  }
  return analyzeReld(cipher, candidates);
}