/**
@file main.cpp 
@brief test d'uso della classe SortedArray<int>
**/


// NOTA

#include <iostream>
#include <fstream>
#include "sortedarray.h" // SortedArray<int>
#include <cassert>   // assert

//template<typename T>
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

void test(){
  
  std::cout << "*** TEST METODI FONDAMENTALI ***" << std::endl;

  
  std::cout << "test ctor default" << std::endl;
  SortedArray<int, AscendingOrd, Equalz> db1;
  
  assert(db1.size() == 0); // verifichiamo lo stato dell'oggetto

  
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

  std::cout << "test operatore assegnamento =" << std::endl;

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
  std::cout<<"ci provo duro"<<std::endl;
  SortedArray<int, AscendingOrd, Equalz> db5(beg, end);
  std::cout<<db5;



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
SortedArray<double, DescendingOrd, Equalz> db7(db6);
std::cout <<"printing new initilized on original"<<std::endl;
std::cout << db7;
assert(db6.size() == db7.size());






// 7. Un metodo che, dato un funtore generico F che implementa una
// condizione booleana su un dato T, ritorna un nuovo SortedArray che
// contiene gli elementi T che soddisfano la condizione. Ad esempio, se il
// SortedArray contiene interi, F potrebbe essere un funtore che ritorna
// true se l’intero è pari e maggiore di 100;
// 8. Un metodo che ritorna true se nella struttura dati è presente almeno un
// elemento di valore T.
// Deve essere inoltre ridefinito l’operatore di stream per il SortedArray.
// Utilizzare dove è opportuno la gestione delle eccezioni. Gestite con una logica
// opportuna i casi limite/di errore";

// 4. Un metodo per rimuovere un dato elemento T. Se più elementi sono
// rimovibili, ne viene rimosso solo uno;
  int a = db1.size();
  std::cout<<db1;
  db1.remove(-1);
  db1.remove(5);
  db1.remove(3);
  std::cout<<db1;
  assert(db1.size() == a - 3);


  std::cout << "trying to use iteratorr;" <<std::endl ;
// 6. Iteratore standard di tipo random_access che ritorna gli elementi in
// ordine;
  for (auto it = db1.begin(); it != db1.end(); ++it){
    std::cout << *it << std::endl;
  }


  SortedArray<int, AscendingOrd, Equalz> 
  db3 = db1.filter(lessThen100());;
  for(auto it = db3.begin(); it!= db3.end(); ++it){
    assert(*it < 100);
  }  
  std::cout<<db3;
}

/**
  test dei metodi d'uso per un SortedArray<int> non const
*/
//   std::cout << "*** TEST METODI SortedArray<int> ***" << std::endl;

//   SortedArray<int> db(5,0);

//   std::cout << "test value" << std::endl;
//   db.value(1) = 100;
//   assert(db.value(1) == 100);

//   std::cout << "test set_value" << std::endl;
//   db.set_value(0,99);
//   assert(db.value(0) == 99);

//   std::cout << "test scrittura op[]" << std::endl;
//   db[3] = 5;
//   assert(db[3]==5);

//   // Se compilazione in modalita' debug da' errore 
//   //db[100] = 5;

//   std::cout << "test lettura op[]" << std::endl;
//   int a = db[3];
//   assert(a==5);

//   // Se compilazione in modalita' debug da' errore 
//   //int tmp = db[8];

//   std::cout << "test stampa con operator<<" << std::endl;
//   std::cout << db << std::endl;

//   return 0;
// }



// int test_fondamentali_int() {

//   std::cout << "*** TEST METODI FONDAMENTALI ***" << std::endl;

//   std::cout << "test ctor default" << std::endl;
//   SortedArray<int> db1;
//   assert(db1.size() == 0); // verifichiamo lo stato dell'oggetto

//   std::cout << "test ctor secondario 1" << std::endl;
//   SortedArray<int> db2(100);
//   assert(db2.size() == 100);

//   std::cout << "test ctor secondario 2" << std::endl;
//   SortedArray<int> db3(50,-1);
//   assert(db3.size() == 50);
//   for(unsigned int i =0; i < 50; i++)
//     assert(db3[i] == -1);

//   std::cout << "test copy constructor" << std::endl;
//   SortedArray<int> db4(db3); 
//   // ATTENZIONE: una sintassi del tipo
//   //             SortedArray<int> db4 = db3;
//   //             EQUIVALE ALLA CHIAMATA AL COPY CONSTRUCTOR!
//   assert(db4.size() == db3.size());
//   for(unsigned int i =0 ; 
//     i < db4.size(); i++)
//     assert(db3[i] == db4[i]);

//   std::cout << "test operatore assegnamento =" << std::endl;
//   db1 = db3;
//   assert(db1.size() == db3.size());
//   for(unsigned int i =0 ; 
//     i < db1.size(); i++)
//     assert(db3[i] == db1[i]);
// }

// /**
//   test dei metodi d'uso per un SortedArray<int> non const
// */
// void test_SortedArray_int() {
//   std::cout << "*** TEST METODI SortedArray<int> ***" << std::endl;

//   SortedArray<int> db(5,0);

//   std::cout << "test value" << std::endl;
//   db.value(1) = 100;
//   assert(db.value(1) == 100);

//   std::cout << "test set_value" << std::endl;
//   db.set_value(0,99);
//   assert(db.value(0) == 99);

//   std::cout << "test scrittura op[]" << std::endl;
//   db[3] = 5;
//   assert(db[3]==5);

//   // Se compilazione in modalita' debug da' errore 
//   //db[100] = 5;

//   std::cout << "test lettura op[]" << std::endl;
//   int a = db[3];
//   assert(a==5);

//   // Se compilazione in modalita' debug da' errore 
//   //int tmp = db[8];

//   std::cout << "test stampa con operator<<" << std::endl;
//   std::cout << db << std::endl;

// }

// /**
//   funzione helper per i test dei metodi d'uso per un SortedArray<int> const
// */
// void test_SortedArray_const_helper_int(const SortedArray<int> &db) {

//   // Tutti i metodi di scrittura devono dare errore
//   // db[1] = 10; // errore
//   // db.value(1) = 10; // errore
//   // db.set_value(1,10); // errore

//   // I metodi di lettura devono funzionare
//   int tmp1 = db[3];
//   int tmp2 = db.value(3);
//   int tmp3 = db.get_value(3);

//   std::cout << "test stampa con operator<<" << std::endl;
//   std::cout << db << std::endl;


//   //SortedArray<int> db2;
//   //db2.swap(db); // errore
// } 

// /**
//   test dei metodi d'uso per un SortedArray<int> const
// */void test_SortedArray_const_int() {
//   SortedArray<int> db(5,0);

//   test_SortedArray_const_helper_int(db);  
// }

// /**
//   Esempio di come si può serializzare un oggetto su file. 
// */
// void serializzazione_SortedArray_int() {
//   std::cout << std::endl << "*** PROVA DI SERIALIZZAZIONE ***" << std::endl;

//   // SortedArray<int> di test
//   SortedArray<int> src(5,9999);

//   // Usando operator<< possiamo scrivere su file il contenuto del SortedArray<int>.
//   // E' importante scrivere operator<< in modo tale da spedire SOLO i dati
//   // e niente altro. Nel caso specifico vengono spediti nell'ordine la size 
//   // e gli interi dell'array.  
//   std::ofstream ofs;
//   ofs.open("output.txt"); // il file è aperto come testo
//   if (!ofs.is_open()) {
//     std::cerr << "ERRORE NELLA'APERTURA DEL FILE" << std::endl;
//     return;
//   }
//   ofs << src << std::endl;
//   ofs.close();

//   // Riapriamo il file e creiamo un secondo SortedArray<int> con i valori salvati 
//   std::ifstream ifs;
//   ifs.open("output.txt");
//   if (!ifs.is_open()) {
//     std::cerr << "ERRORE NELLA'APERTURA DEL FILE" << std::endl;
//     return;
//   }
//   // Leggiamo la size
//   unsigned int size;
//   ifs >> size;

//   // Creiamo un SortedArray<int> con la dimensione letta 
//   SortedArray<int> dst(size);

//   // Leggiamo i size interi dal file direttamente nelle celle dell'array 
//   for(unsigned int i=0; i<size;++i)
//     ifs >> dst[i];
//   ifs.close();

//   std::cout <<"Contenuto del SortedArray<int> src:" << std::endl;
//   std::cout << src << std::endl;

//   std::cout <<"Contenuto del SortedArray<int> dst:" << std::endl;
//   std::cout << dst << std::endl;
// }

// void test_conversione_tipo_int() {
//   SortedArray<int> d1(10);

//   SortedArray<int> d2;
  
//   d2 = d1; // op assegnamento
  
//   d2 = SortedArray<int>(3); // conversione di tipo esplicita
  
//   std::swap(d1,d2);
  
//   SortedArray<int>::size_type s; // uso dei typedef
// } 

// void test_iteratori_int() {
//   SortedArray<int> d(10);

//   for (unsigned int j = 0; j < 10; ++j)
//     d[j] = j;

//   SortedArray<int>::iterator it; // iteratore di inizio lettura/scrittura
//   SortedArray<int>::iterator ite;// iteratore di fine lettura/scrittura

//   ite = d.end(); // chiediamo l'iteratore di fine

//   for (it = d.begin(); it!=ite; ++it)
//     std::cout << *it << std::endl;

//   it = d.begin();
//   *it = 100; // modifico il primo elemento della sequenza di dati

//   assert(d[0] == 100);


//   SortedArray<int>::const_iterator cit; // iteratore in lettura

//   cit = d.begin();

//   assert(*cit == 100); 

//   // *cit = 0; // errore

//   // NOTA1: gli iteratori sono come i puntatori. Possono 
//   //        "puntare" a delle posizioni non valide se 
//   //        iteriamo troppo.
//   // 
//   // NOTA2: non dereferenziare MAI l'iteratore di fine: 
//   //        Non punta a dei dati utili.
// }

// struct utente {
//   std::string nome;
//   std::string cognome;

//   utente(const std::string &n, const std::string &c) : 
//     nome(n), cognome(c) {}
// };

// int main(int argc, char *argv[]) {
  
//   // Test con SortedArray su interi: SortedArray<int> 
//   test_fondamentali_int();
  
//   test_SortedArray_int();
  
//   test_SortedArray_const_int();
  
//   serializzazione_SortedArray_int();

//   test_conversione_tipo_int();
  
//   test_iteratori_int();

//   // Test con SortedArray su tipi custom: es. SortedArray<utente>

//   // Rifare tutti i test come sopra
//   //
//   // test_SortedArray_utente();
//   // ...
//   return 0;
// }
int main(int argc, char const *argv[]){
  test();
}

