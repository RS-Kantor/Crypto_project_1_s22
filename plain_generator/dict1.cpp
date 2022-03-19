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

char get_char(int i) {
  if (i == 0)
    return ' ';
  return 'a' + i - 1;
}

int main() {
  int l, u;
  cout << "Enter the value of L: " << endl;
  cin >> l;
  cout << "Enter the no. of examples: " << endl;
  cin >> u;
  ofstream outfile("dict1.txt");
  for (int i = 0; i < u; i++) {
    for (int j = 0; j < l; j++) {
      int r = randomizer() % 27;
      outfile << get_char(r);
    }
    outfile << endl;
  }
  return 0;
}