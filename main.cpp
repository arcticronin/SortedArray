/**
@file main.cpp 
@brief test d'uso della classe SortedArray<int>
**/

#include <iostream>
#include <fstream>
#include "sortedarray.h" // SortedArray<int>
#include <cassert>   // assert

struct lessThen100 {
    bool operator()(const int& a) const {
        return a < 100;
    }
};

struct AscendingOrd {
    bool operator()(const int& a, const int& b) const {
        return a < b;
    }
};

struct DescendingOrd {
    bool operator()(const int& a, const int& b) const {
        return a > b;
    }
};

struct Equalz {
    bool operator()(const int& a, const int& b) const {
        return a == b;
    }
};


struct Person
{
  std::string name;
  int age;
  Person():name(""), age(0){};//needed for array initialization
  Person(const std::string &name, int age) : name(name), age(age) {};
};

struct AgeOrderPolicy
{
  bool operator()(const Person &p1, const Person &p2) const
  {
    return p1.age < p2.age;
  }
};

struct NameEqualPolicy
{
  bool operator()(const Person &p1, const Person &p2) const
  {
    return p1.name == p2.name;
  }
};

std::ostream& operator<<(std::ostream& os, const Person& person)
{
  os << "Name: " << person.name << ", Age: " << person.age;
  return os;
}

void test2(){
  // Create a SortedArray of Persons using custom policies
  SortedArray<Person, AgeOrderPolicy, NameEqualPolicy> arr;

  // Test insertion
  arr.insert(Person("John", 25));
  arr.insert(Person("Alice", 30));
  arr.insert(Person("Bob", 20));
  arr.insert(Person("Jane", 35));

  // Test copy constructor
  SortedArray<Person, AgeOrderPolicy, NameEqualPolicy> arr2(arr);

  // Test iterator constructor
  Person data[] = {Person("Tom", 40), Person("Mary", 22)};
  SortedArray<Person, AgeOrderPolicy, NameEqualPolicy> arr3(data, data + 2);
  assert(arr3.size()==2);

  // Test remove
  arr3.remove(Person("Tom", 40));

  assert(arr3.size()==1);

  // Test find
  assert(arr.find(Person("Alice", 30)));

  // Test filter
  
  SortedArray<Person, AgeOrderPolicy, NameEqualPolicy> f = arr.filter
                                  ([](const Person &p) { return p.age > 25; });

  // Print the elements of the filtered array
  for (int i = 0; i < f.size(); ++i){
    assert(f[i].age > 25);
  }
}


void test1(){

  // Create a SortedArray of integers
  SortedArray<int, std::less<int>, std::equal_to<int>> arr;

  // Test insertion
  arr.insert(5);
  arr.insert(3);
  arr.insert(7);
  arr.insert(1);
  arr.insert(9);

  // Test copy constructor
  SortedArray<int, std::less<int>, std::equal_to<int>> arr2(arr);
  for (int i = 0 ; i< arr2.size(); i++)
    assert(arr[i]==arr2[i]);

  // Test iterator constructor
  int data[] = {2, 4, 6, 8};
  SortedArray<int, std::less<int>, std::equal_to<int>> arr3(data, data + 4);

  // Test remove
  arr3.remove(2);

  // Test find
  bool found = arr.find(7);
  if (found)
    std::cout << "7 found in the array." << std::endl;
  else
    std::cout << "7 not found in the array." << std::endl;

  // Test filter
  SortedArray<int, std::less<int>, std::equal_to<int>> filtered = arr.filter([](int num) { return num % 2 == 0; });

  // Print the elements of the filtered array
  for (int i = 0; i < filtered.size(); ++i)
    std::cout << filtered[i] << " ";
  std::cout << std::endl;
}

void test0(){
  
  std::cout << "*** TEST METODI FONDAMENTALI ***" << std::endl;

  SortedArray<int, AscendingOrd, Equalz> db1;
  
  assert(db1.size() == 0);
  
  db1.insert(1);
  db1.insert(2);
  db1.insert(100);
  db1.insert(0);
  
  SortedArray<int, AscendingOrd, Equalz> db4(db1); 
  
  std::cout << "test copy constructor" << std::endl;
  // ATTENZIONE: una sintassi del tipo
  //             SortedArray<int> db4 = db3;
  //             EQUIVALE ALLA CHIAMATA AL COPY CONSTRUCTOR!

  assert(db1.size() == db4.size());
  // for(unsigned int i =0 ;
  //   i < db4.size(); i++){
  //   assert(db1[i] == db4[i]);
  //   }

  std::cout << "test operatore assegnamento  =" << std::endl;

   SortedArray<int, AscendingOrd, Equalz> db2;
   db2 = db1 = db4;
  assert(db1.size() == db2.size());
  for(unsigned int i =0 ; i < db1.size(); i++){
    assert(db1[i] == db2[i]);
    assert(db4[i] == db2[i]);
  }

  std::cout << db2;

// 5. Un metodo per svuotare l’array;
// test makeempty

  std::cout << "test makeempty:" << std::endl;

  db1.makeEmpty();
  assert(db1.size()==0);

// 3. Un metodo per aggiungere un nuovo elemento T nell’array;

  db1.insert(1);
  db1.insert(2);
  db1.insert(3);
  db1.insert(4);
  db1.insert(5);
  db1.insert(0);
  db1.insert(102);
  db1.insert(130);
  db1.insert(106);
  db1.insert(100);
  db1.insert(-1);


// ". Un costruttore secondario che costruisce un SortedArray a partire dai
// dati rappresentati da due iteratori generici di inizio e fine sequenza;

  std::cout<<db1;
  //size: 11 | -1 0 1 2 3 4 5 100 102 106 130 
  auto beg = db1.begin()+2;
  auto end = db1.begin()+5;
  std::cout<<"pointrs from another SortedArray"<<std::endl;
  SortedArray<int, AscendingOrd, Equalz> db5(beg, end);
  std::cout<<db5;
  int ls[] = {-1, 2, 3, 10, 21, 32, -10 };
  SortedArray<int, AscendingOrd, Equalz> dbL(ls, ls + 7);

// 2. Un costruttore secondario che costruisce un SortedArray a partire da
// una altro SortedArray generico;

SortedArray<int, AscendingOrd, Equalz> db6;
db6.insert(1);
db6.insert(12);
db6.insert(6);
db6.insert(40);
db6.insert(2);
db6.insert(11);
db6.insert(12);
std::cout <<"printing original"<<std::endl;
std::cout << db6;
//other type, other policy
SortedArray<double, DescendingOrd, Equalz> db7(db6);
std::cout <<"printing new initilized on original"<<std::endl;
std::cout << db7;
assert(db6.size() == db7.size());

// 8. Un metodo che ritorna true se nella struttura dati è presente almeno un
// elemento di valore T.
assert(db6.find(2));




// 4. Un metodo per rimuovere un dato elemento T. Se più elementi sono
// rimovibili, ne viene rimosso solo uno;
  int a = db1.size();
  std::cout<<db1;
  db1.remove(-1);
  db1.remove(5);
  db1.remove(3);
  std::cout<<db1;
  assert(db1.size() == a - 3);


// 6. Iteratore standard di tipo random_access che ritorna gli elementi in
// ordine;
  std::cout << "trying to use iteratorr;" <<std::endl ;
  for (auto it = db1.begin(); it != db1.end(); ++it){
    std::cout << *it << std::endl;
  }// true se l’intero è pari e maggiore di 100;
  std::cout << "trying to use iter ops, 100 expected;" <<std::endl ;
  std::cout << *(db1.end() - 4) << std::endl;
  assert(*(db1.end() - 4)==100);

// 7. Un metodo che, dato un funtore generico F che implementa una
// condizione booleana su un dato T, ritorna un nuovo SortedArray che
// contiene gli elementi T che soddisfano la condizione. Ad esempio, se il
// SortedArray contiene interi, F potrebbe essere un funtore che ritorna
// true se l’intero è pari e maggiore di 100;

  SortedArray<int, AscendingOrd, Equalz> 
  db3 = db1.filter(lessThen100());;
  for(auto it = db3.begin(); it!= db3.end(); ++it){
    assert(*it < 100);
  }  
  std::cout<<db3;
}

int main(int argc, char const *argv[]){
  test2();
  test1();
  test0();
}

