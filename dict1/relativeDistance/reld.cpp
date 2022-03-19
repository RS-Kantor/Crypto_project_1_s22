#include "reld.h"

vector<int> calculate_reld_distance(string text,
                                    vector<pair<char, int>> &freqMap,
                                    int freqIdx) {
  vector<int> reld_dists;
  string t;
  int lastIdx = -1;
  for (int i = 0; i < text.length(); i++) {
    if (text[i] == freqMap[freqIdx].first) {
      reld_dists.push_back(i - lastIdx);
      lastIdx = i;
      t += '!';
    } else {
      t += text[i];
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

  vector<pair<char, int>> cipher_freq;
  freqsort(cipher, cipher_freq);

  int best_reld = INT_MAX;
  string best_candidate;
  for (int i = 0; i < candidates.size(); i++) {
    vector<pair<char, int>> candidate_freq;
    freqsort(candidates[i], candidate_freq);

    int reld_diff_avg = 0;
    for (int j = 0; j < 8; j++) {
      vector<int> reld_dists = calculate_reld_distance(cipher, cipher_freq, j);
      vector<int> reld_dists_candidate =
          calculate_reld_distance(candidates[i], candidate_freq, j);
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