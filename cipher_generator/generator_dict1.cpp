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

int get_pos(char c) {
  if (c == ' ')
    return 0;
  return c - 'a' + 1;
}

int main() {
  // setup
  ifstream infile("../dictionary_1.txt");
  string s;
  getline(infile, s);

  vector<char> key;
  key.push_back(' ');
  for (char i = 'a'; i <= 'z'; i++) {
    key.push_back(i);
  }

  shuffle(key.begin(), key.end(), randomizer);

  string out;

  // generation parameters
  int prob_of_random_ciphertext;
  cout << "Enter probability of random ciphertext float (0-100): " << endl;
  cout << "0 for no random" << endl;
  cin >> prob_of_random_ciphertext;

  // generation
  int message_pointer = s.length() - 1;
  int num_of_randTexts = 0;
  while (message_pointer >= 0) {
    if (randomizer() % 101 <= prob_of_random_ciphertext) {
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
  cout << "Ciphertext: " << out << endl;

  return 0;
}