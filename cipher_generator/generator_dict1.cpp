#include <algorithm>
#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

random_device rd;
mt19937_64 randomizer{rd()};

bool cmp(pair<char, int> a, pair<char, int> b) { return a.second > b.second; }

int get_pos(char c) {
  if (c == ' ')
    return 0;
  return c - 'a' + 1;
}

void createFreqMap(string x, map<char, int> &freqMap) {
  for (int i = 0; i < x.length(); i++) {
    if (freqMap.find(x[i]) != freqMap.end()) {
      freqMap[x[i]] += 1;
    } else {
      freqMap[x[i]] = 1;
    }
  }
}

void freqsort(string x, vector<pair<char, int>> &out) {
  map<char, int> freqMap;
  createFreqMap(x, freqMap);

  for (auto i : freqMap) {
    out.push_back(i);
  }

  sort(out.begin(), out.end(), cmp);
}

int main() {
  // setup
  ifstream infile("../dictionary_1.txt");
  string s;
  vector<string> candidates;
  while (getline(infile, s)) {
    if (s[0] <= 'z' && s[0] >= 'a') {
      candidates.push_back(s);
    }
  }

  vector<char> og_key;
  og_key.push_back(' ');
  for (char i = 'a'; i <= 'z'; i++) {
    og_key.push_back(i);
  }

  vector<char> key(og_key);

  shuffle(key.begin(), key.end(), randomizer);

  string out;

  // generation parameters
  int prob_of_random_ciphertext, string_to_use;
  cout << "Enter probability of random ciphertext float (0-99): " << endl;
  cout << "0 for no random" << endl;
  cin >> prob_of_random_ciphertext;
  cout << "String to use (0 - " << candidates.size() - 1 << "): " << endl;
  cin >> string_to_use;

  s = candidates[string_to_use];

  // generation
  int message_pointer = s.length() - 1;
  int num_of_randTexts = 0;
  while (message_pointer >= 0) {
    if (randomizer() % 100 < prob_of_random_ciphertext) {
      out.push_back(key[randomizer() % key.size()]);
      num_of_randTexts++;
      continue;
    }
    out.push_back(key[get_pos(s[message_pointer])]);
    message_pointer--;
  }

  cout << "Og text: " << s << endl;
  cout << "Sizes " << s.length() << " " << out.length() << endl;
  cout << "Number of random letters: " << num_of_randTexts << endl;
  cout << "Ciphertext: \"" << out << "\"" << endl;

  // analysis
  // vector<pair<char, int>> freqTableCipher;
  // freqsort(out, freqTableCipher);
  // vector<pair<char, int>> freqTableCandidate;
  // freqsort(s, freqTableCandidate);
  // for (int i = 0; i < freqTableCandidate.size(); i++) {
  //   cout << freqTableCandidate[i].first << " " <<
  //   freqTableCandidate[i].second
  //        << " ";
  // }
  // cout << endl;
  // for (int i = 0; i < freqTableCipher.size(); i++) {
  //   cout << freqTableCipher[i].first << " " << freqTableCipher[i].second << "
  //   ";
  // }
  return 0;
}