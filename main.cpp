#include "dict1/dict1.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << "Enter the ciphertext: \n";
  string cipher;
  getline(cin, cipher);
  ifstream infile("dictionary_1.txt");

  vector<string> candidates;
  string c;
  while (getline(infile, c)) {
    if (c[0] <= 'z' && c[0] >= 'a') {
      candidates.push_back(c);
    }
  }
  cout << "The plaintext is: " << tryDict1(cipher, candidates) << endl;
}