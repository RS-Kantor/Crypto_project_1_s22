#include <algorithm>
#include <climits>
#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class FreqMap {
private:
  map<char, int> singFreqMap;
  map<string, int> diaFreqMap;

public:
  FreqMap(string text);

  vector<pair<char, int>> getSingFreqSort();

  vector<pair<string, int>> getDiaFreqSort();
};