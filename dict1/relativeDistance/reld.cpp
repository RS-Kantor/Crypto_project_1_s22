#include "reld.h"

vector<int> cal_reld_single(string text, FreqMap &freqMapObj, int freqIdx) {
  vector<int> reld_dists;
  vector<pair<char, int>> freqTable = freqMapObj.getSingFreqSort();

  string t;
  int lastIdx = -1;
  for (int i = 0; i < text.length(); i++) {
    if (text[i] == freqTable[freqIdx].first) {
      reld_dists.push_back(i - lastIdx);
      lastIdx = i;
      t += '!';
    } else {
      t += text[i];
    }
  }

  return reld_dists;
}

vector<int> cal_reld_double(string text, FreqMap &freqMapObj, int freqIdx) {
  vector<int> reld_dists;
  vector<pair<string, int>> freqTable = freqMapObj.getDiaFreqSort();

  string t;
  int lastIdx = -1;
  for (int i = 0; i < text.length() - 1; i++) {
    string s = text.substr(i, 2);
    if (s == freqTable[freqIdx].first) {
      reld_dists.push_back(i - lastIdx);
      lastIdx = i;
      t += '!';
    } else {
      t += s;
    }
  }

  return reld_dists;
}

int get_reld_diff(vector<int> reldDistCipher, vector<int> reldDistCandidate) {
  int i = reldDistCipher.size(), j = reldDistCandidate.size();
  int diff = 0;
  for (int k = 0; k < min(i, j); k++) {
    diff += reldDistCipher[k] - reldDistCandidate[k];
  }
  if (i < j) {
    for (int k = i; k < j; k++) {
      diff += reldDistCandidate[k];
    }
  } else {
    for (int k = j; k < i; k++) {
      diff += reldDistCipher[k];
    }
  }
  return abs(diff);
}

string analyzeReld(string cipher, vector<string> &candidates) {

  FreqMap cipherMap(cipher);

  int best_reld = INT_MAX;
  string best_candidate;
  for (int i = 0; i < candidates.size(); i++) {
    FreqMap candidateMap(candidates[i]);

    int reld_diff_avg = 0;
    for (int j = 0; j < 3; j++) {
      vector<int> reld_dists = cal_reld_single(cipher, cipherMap, j);
      vector<int> reld_dists_candidate =
          cal_reld_single(candidates[i], candidateMap, j);
      reld_diff_avg += get_reld_diff(reld_dists, reld_dists_candidate);
    }
    for (int j = 0; j < 2; j++) {
      vector<int> reld_dists = cal_reld_double(cipher, cipherMap, j);
      vector<int> reld_dists_candidate =
          cal_reld_double(candidates[i], candidateMap, j);
      reld_diff_avg += get_reld_diff(reld_dists, reld_dists_candidate);
    }

    cout << "reld_diff_avg: " << reld_diff_avg << endl;

    if (reld_diff_avg < best_reld) {
      best_reld = reld_diff_avg;
      best_candidate = candidates[i];
    }
  }

  return best_candidate;
}