
// Author:           Syed Tamal
// Created:          03 Aug 2023  21:44:49 

#include <bits/stdc++.h>
using namespace std;
#define int long long

template<class K, class V>
struct node{
  K key;
  V value;
  node<K, V> *next, *prev;
};

template<class K, class V>
class List{
  node<K, V> *head, *tail;
  int sz;
public:
  List(){
    head = NULL;
    tail = NULL;
    sz = 0;
  }
  void emplace_back(K key, V value){
    node<K, V>* newitem = new node<K, V>;
    newitem->key = key;
    newitem->value = value;
    newitem->next = NULL;
    newitem->prev = NULL;
    if(head == NULL) {
      head = newitem, tail = newitem;
    }
    else{
      tail->next = newitem;
      newitem->prev = tail;
      tail = newitem;
    }
    sz++;
  }
  node<K, V>* erase(node<K, V>* tar){
    if(!sz){
      cout<<"The size of list is empty\n";
      return NULL;
    }
    if(tar == head) {
      node<K, V>* ptr = head;
      head = head->next;
      delete ptr;
      return head;
    }
    else if(tar == tail){
      node<K, V>* ptr = tail;
      tail = tail->prev;
      delete ptr;
      return NULL;
    }
    else{
      node<K, V> *pre = tar->prev;
      node<K, V> *nex = tar->next;
      if(pre != NULL) pre->next = nex;
      if(nex != NULL) nex->prev = pre;
      delete tar;
      sz--;
      return nex;
    }
  }
  int size() const { return sz; }
  node<K, V>* find(K key){
    node<K, V>* temp = head;
    while(temp != NULL){
      if(temp->key == key) return temp;
      temp = temp->next;
    }
    return temp;
  }
  void display(){
    node<K, V> *temp = head;
    while(temp != NULL){
      debug(temp->key, temp->value);
      temp = temp->next;
    }
  }
  node<K, V>* begin(){
    return head;
  }
  node<K, V>* end(){
    return tail->next;
  }
};

template<class K, class V>
class HashTable{
private:
  static const int hashGroup = 10;
  List<K, V> table[hashGroup];
public:
  bool isEmpty() const;
  int hashFunction(int key);
  int hashFunction(string key);
  void insert(K key, V value);
  void erase(K key);
  V searchTable(K key);
  void printTable();
  V& operator[](K key){
    int hashValue = hashFunction(key);
    node<K, V>* it = table[hashValue].find(key);
    if(it != NULL) return it->value;
    table[hashValue].emplace_back(key, V());
    it = table[hashValue].find(key);
    return it->value;
  }
};

template<class K, class V>
bool HashTable<K, V>::isEmpty() const{
  int size = 0;
  for(int i=0;i<hashGroup;i++){
    size += table[i].size();
  }
  if(!size) return true;
  return false;
}

template<class K, class V>
int HashTable<K, V>::hashFunction(int key){
  return key % hashGroup;
}

template<class K, class V>
int HashTable<K, V>::hashFunction(string key){
      int res = 0;
      const int m = 1e9 + 7, p = 31;
      int power = 1;
      for(char c:key){
        res = (res + (int)c * power) % m;
        power = (power * p) % m;
      }
      return res % hashGroup;
}

template<class K, class V>
void HashTable<K, V>::insert(K key, V value){
  int hashValue = hashFunction(key);
  auto it = table[hashValue].find(key);
  if(it != NULL){
    it->value = value;
    cout<<"[Warning] key exist. Value replaced\n";
  }
  else table[hashValue].emplace_back(key, value);
}

template<class K, class V>
void HashTable<K, V>::erase(K key){
  int hashValue = hashFunction(key);
  auto it = table[hashValue].find(key);
  if(it != NULL){
    it = table[hashValue].erase(it);
    cout<<"[Info] key exist. Value deleted\n";
  }
  else cout<<"[Warning] key not found. Pair not found.\n";
}

template<class K, class V>
V HashTable<K, V>::searchTable(K key){
  int hashValue = hashFunction(key);
  auto it = table[hashValue].find(key);
  if(it != NULL) return it->value;
  return 0;
}

template<class K, class V>
void HashTable<K, V>::printTable(){
  for(int i=0;i<hashGroup;i++){
    if(table[i].size() == 0) continue;
    for(auto it = table[i].begin(); it != table[i].end(); it = it->next){
      cout<<"key: "<<it->key<<" value: "<<it->value<<"\n";
    }
  }
}
