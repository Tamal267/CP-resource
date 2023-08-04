// Author:           Syed Tamal
// Created:          03 Aug 2023  21:44:49 

#include <bits/stdc++.h>
#include "HashMap.h"
using namespace std;
#define int long long

int32_t main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  HashTable<string, int> mp;
  mp.insert("10", 20);
  mp.insert("30", 40);
  mp.insert("50", 1);

  mp["60"] = 10;

  mp.printTable();
  mp.erase("10");
  mp.printTable();
  mp["50"]++;
  cout<<mp["50"]<<"\n";
}
