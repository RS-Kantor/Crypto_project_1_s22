#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<char, float> freqs(string cipher) {

  map<char, float> vals;

  for (int i = 0; i < cipher.length(); i++) {
    if (vals.find(cipher[i]) != vals.end()) {
      vals[cipher[i]] += 1;
    } else {
      vals[cipher[i]] = 1;
    }
  }

  for (auto i : vals) {
    i.second = i.second / cipher.size();
  }

  return vals;
}

bool cmp(pair<char, float> a, pair<char, float> b) {
  return a.second > b.second;
}

vector<pair<char, float>> freqsort(string cipher) {

  vector<pair<char, float>> out;
  map<char, float> vals = freqs(cipher);

  for (auto i : vals) {
    out.push_back(i);
  }

  sort(out.begin(), out.end(), cmp);

  return out;
}

map<char, char> keygen(string cipher, string candidate) {

  map<char, char> out;

  auto freqtable = freqsort(candidate);
  auto sorted = freqsort(cipher);

  for (int i = 0; i < sorted.size(); i++) {
    out[sorted[i].first] = freqtable[i].first;
  }

  return out;
}

string decrypt(string cipher, map<char, char> key) {

  string output;
  for (int i = 0; i < cipher.size(); i++) {
    output = output + to_string(key[cipher[i]]);
  }

  return output;
}

int noiseamount(string cipher, string candidate, map<char, char> key) {

  string d_cipher = decrypt(cipher, key);

  int i_cipher = 0;
  int i_candidate = 0;
  int noise = 0;

  while (i_cipher < d_cipher.size()) {
    if (d_cipher[i_cipher] == candidate[i_candidate]) {
      i_cipher++;
      i_candidate++;
    } else {
      i_cipher++;
      noise++;
    }
  }

  return noise;
}

string analyze(string cipher) {

  string guess;

  ifstream infile("dictionary_1.txt");

  int bestnoise = INT_MAX;
  int c_noise;

  string candidate;

  while (getline(infile, candidate)) {
    if (candidate[0] <= 'z' && candidate[0] >= 'a') {
      auto keyout = keygen(cipher, candidate);
      c_noise = noiseamount(cipher, candidate, keyout);
      if (c_noise < bestnoise) {
        bestnoise = c_noise;
        guess = candidate;
      }
    }
  }

  return guess;
}

int main() {

  cout << "Enter the ciphertext: \n";
  string cipher;
  getline(cin, cipher);

  string plain = analyze(cipher);

  cout << "\nMy plaintext guess is: " + plain + "\n";
}
