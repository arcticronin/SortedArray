#ifndef SortedArray_H
#define SortedArray_H

#include <ostream> // std::ostream
#include <cassert>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

/**
  @file SortedArray.h
  @brief Dichiarazione della classe SortedArray
*/

/**
  @brief Classe SortedArray

  Classe che vuole rappresentare un array dinamico ordinato.
  Classe Template, con 3 parametri Template
  
  Supporta iteratore random access

  Lista parametri template:
  @param T Tipo dei dati da inserire nel container
  @param P Policy per il confronto e ordinamento degli elementi
  @param Q Policy di uguaglianza


*/
template <typename T, typename P, typename Q>
class SortedArray
{
public:
  typedef T value_type;           /// Tipo del dato dell'array
  typedef unsigned int size_type; /// Tipo del dato size
  typedef P order_policy;
  typedef Q equal_policy;

  /**
    @brief Costruttore di default

    Il cosruttore di default serve a inizializzare i dati membro
    per rappresentare un SortedArray vuoto

    @post _array = nullptr
    @post _size = 0
  */

  SortedArray() : _array(nullptr), _size(0)
  {
#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray()" << std::endl;
#endif
  }

  /**
    @brief Distruttore

    Distruttore della classe. Il distruttore deve rimuovere tutte
    le risorse usate dalla classe. In questo caso l'array allocato
    sullo heap deve essere deallocato.
    Si rimanda a @ref makeEmpty()
  */
  ~SortedArray()
  {
    this->makeEmpty();
#ifndef NDEBUG
    std::cout << "SortedArray::~SortedArray()" << std::endl;
#endif
  }
  // Other member functions

  /**
    @brief Copy Constructor

    Costruttore di copia. Serve a creare un oggetto come copia di un
    altro oggetto. I due oggetti devono essere indipendenti.

    @param other SortedArray sorgente da copiare

    @post _array != nullptr
    @post _size = other._size
  */
  SortedArray(const SortedArray<value_type,
                                order_policy,
                                equal_policy> &other)
      : _array(nullptr), _size(0)
  {

    _array = new value_type[other._size];

    _size = other._size;

    try
    {
      for (size_type i = 0; i < _size; ++i)
        _array[i] = other._array[i];
    }
    catch (...)
    {
      makeEmpty();
      throw;
    }
#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray(const SortedArray&)" << std::endl;
#endif
  }

/**
    @brief Costruttore da iteratori

    Serve a creare un oggetto a partire da una coppia di iteratori.
    Gli iteratori sono di tipo sconosciuto, uso solamente l'operazione ++
    comune a tutti.

    @param begin Iter di inizio seq
    @param end iteratore di fine seq

    @post _array != nullptr
    @post _size = diff(end, begin)
  */
  template <typename Iter>
  SortedArray(Iter begin, Iter end) : _array(nullptr), _size(0)
  {
    while (begin != end)
    {
      try
      {
        this->insert(static_cast<value_type>(*begin));
      }
      catch (...)
      {
        makeEmpty();
        throw;
      }
      ++begin;
    }
#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray(Iter begin, Iter end)" << std::endl;
#endif
  }
/**
    @brief Costruttore da altro generico Sorted Array.

    Serve a creare un oggetto a partire da una altro generico SortedArray.


    @param begin Iter di inizio seq
    @param end iteratore di fine seq

    @post _array != nullptr
    @post _size = other.size
    
    @ref insert()
  */

  template <typename U, typename R, typename S>
  SortedArray(const SortedArray<U, R, S> &other) : _array(nullptr), _size(0)
  {
    try
    {
      for (size_type i = 0; i < other.size(); ++i){
        this->insert(static_cast<value_type>(other[i]));
        }
    }
    catch (...)
    {
      makeEmpty();
      throw;
    }
#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray(const SortedArray<U, R, S> &other)"
              << std::endl;
#endif
  }

  /**
    @brief Operatore di assegnamento

    OPERATORE ASSEGNAMENTO
    L'operatore di assegnamento serve a copiare il contenuto di un oggetto
    in un altro oggetto dello stesso tipo. I due oggetti devono essere
    indipendenti.

    @param other SortedArray sorgente da copiare

    @return reference all'oggetto corrente

    @post _SortedArray != nullptr
    @post _size = other._size
  */
  SortedArray &operator=(const SortedArray<value_type,
                                           order_policy,
                                           equal_policy> &other)
  {
    if (this != &other)
    {
      SortedArray tmp(other);
      this->swap(tmp);
    }
#ifndef NDEBUG
    std::cout << "SortedArray::operator=(const SortedArray &)" << std::endl;
#endif
    return *this;
  }

 /**
    @brief Inserimento di un elemento
    
    Inserimento di un elemento nel SortedArray in posizione ordinata

    @param item reference di elemento di tipo del SortedArray 

    @post _size++  
  */

  void insert(const value_type &item)
  {
    value_type *new_array = new value_type[_size + 1];

    int index = searchsorted(item);
    // get_insert_index

    if (_array == nullptr)
    {
      try
      {
        new_array[0] = item;
      }
      catch (...)
      {
        delete[] new_array;
        throw;
      }
      std::swap(_array, new_array);
      _size = 1;
      return;
    }

    // copy first part
    for (int i = 0; i < index; ++i)
    {
      try
      {
       new_array[i] = _array[i];
      }
      catch (...)
      {
        delete[] new_array;
        throw;
      }
    }

    // insert
    try
    {
      new_array[index] = item;
    }
    catch (...)
    {
      delete[] new_array;
      throw;
    }

    // copy second part
    for (int i = index; i < _size; i++)
    {
      try
      {
        new_array[i + 1] = _array[i];
      }
      catch (...)
      {
        delete[] new_array;
        throw;
      }
    }
    
    std::swap(new_array, _array);
    delete[] new_array;
    _size += 1;
    return;
  }

 /**
    @brief Rimozione di un elemento
    
    Rimozione di un elemento nel SortedArray in posizione ordinata

    @param item reference di elemento di tipo del SortedArray 
    @return 0 if manages to remove 
    @return -1 if it fails 
    @post _size--  
  */
  int remove(const value_type &item)
  {
    // get_insert_index
    int index = get_index_of(item);

    if(index == -1){
      // i vhose -1 as error code
      return -1;
      }

    value_type *new_array = nullptr;

    if (_size == 1)
    {
      assert(index == 0);
      makeEmpty();
      return 0;
    }

    new_array = new value_type[_size - 1];

    // copy first part
    for (int i = 0; i < index; ++i)
    {
      try
      {
        new_array[i] = _array[i];
      }
      catch (...)
      {
        delete[] new_array;
        throw;
      }
    }

    // copy second part skipping index
    for (int i = index; i < _size - 1; i++)
    {
      try
      {
        new_array[i] = _array[i + 1];
      }
      catch (...)
      {
        delete[] new_array;
        throw;
      }
    }

    std::swap(new_array, _array);
    delete[] new_array;
    _size -= 1;
    return 0;
  }

 /**
    @brief Searchsorted, ritorna indice al quale inserire per mantenere ordine
    
    @param item reference di elemento di tipo del SortedArray 

    @return indice al quale si deve inserire 
  */
  int searchsorted(const value_type &item) const
  {
    order_policy ord;
    if (_size == 0)
    {
      return 0;
    }
    for (int i = 0; i < _size; ++i)
    {
      if (ord(item, _array[i]))
      {
        return i;
      }
    }
    return _size;
  }

 /**
    @brief makeEmpty - svuota
    
    Funzione che svuota array e inizializza a zero la struttura dati occupandosi della memoria


    @post _size = 0
    @post _array = nullptr  
  */
  void makeEmpty()
  {
    delete[] _array;
    _array = nullptr;
    _size = 0;
    return;
  }

 /**
    @brief find - ricerca un elemento se presente
    
    Inserimento di un elemento nel SortedArray in posizione ordinata

    @param item reference di elemento di tipo del SortedArray 

    @return 1, trovato, 
    @return 0, non trovato  
  */
  bool find(const value_type &target)
  {
    return (get_index_of(target) != -1);
  }

/**
    @brief Filter - filtra l'array e restituisce un altro SortedArray
    

    @param filt Policy che vogliamo usare per filtrare l'array, una sua istanza confrontando un elemento di tipo value_type con l'operatore (), deve restituire un boolean

    @return SortedArray - con soli gli elementi che soddisfano il filtro 
    @ref insert
  */


  template <typename Policy>
  SortedArray filter(Policy filt)
  {
    // init things
    SortedArray<value_type, order_policy, equal_policy> result;

    // reverse to have better insert time
    for (int i = _size - 1; i >= 0; --i)
    {
      if (filt(_array[i]))
      {
        try
        {
          result.insert(_array[i]);
        }
        catch (...)
        {
          result.makeEmpty();
          throw;
        }
      }
    }
    return result;
  }

  /**
    @brief Accesso alla dimensione dell'array

    Metodo per ottenere la dimensione dell'array

    @return dimensione dell'array dinamico
  */
  size_type size(void) const
  {
    return _size;
  }


  /**
    @brief Getter della cella index-esima

    Metodo che permette di leggere la cella
    index-esima dell'array. Il metodo si può usare
    solo su istanze costanti della classe.

    @param index della cella da leggere

    @return reference alla cella index-esima

    @pre index < size()
  */
  const value_type &operator[](size_type index) const
  {
    assert(index < _size);
    
    return _array[index];
  }

  /**
    @brief Metodo swap per la classe SortedArray

    Funzione che scambia il contenuto di due SortedArray

    @param other il SortedArray con cui scambiare il contenuto
  */
  void swap(SortedArray &other)
  {
    std::swap(_array, other._array);
    std::swap(_size, other._size);
  }

/**
    @brief Classe che rappresenta un iteratore di tipo random_access_iterator

    sfrutta la struttura della classe SortedArray per implementare un puntatore random access
    
    @ref SortedArray::begin()
    @ref SortedArray::end()
  */
    class iterator
  {
    //
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;

    iterator()
    {
      ptr = nullptr;
    }

    iterator(const iterator &other)
    {
      ptr = other.ptr;
    }

    iterator &operator=(const iterator &other)
    {
      ptr = other.ptr;
      return *this;
    }

    ~iterator() {}

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const
    {
      return *ptr;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const
    {
      return ptr;
    }

    // Operatore di accesso random
    reference operator[](int index)
    {
      return ptr + index;
    }

    // Operatore di iterazione post-incremento
    iterator operator++(int)
    {
      iterator old(*this);
      ++ptr;
      return old;
    }

    // Operatore di iterazione pre-incremento
    iterator &operator++()
    {
      ++ptr;
      return *this;
    }

    // Operatore di iterazione post-decremento
    iterator operator--(int)
    {
      iterator old(*this);
      --ptr;
      return old;
    }

    // Operatore di iterazione pre-decremento
    iterator &operator--()
    {
      --ptr;
      return *this;
    }

    // Spostamentio in avanti della posizione
    iterator operator+(int offset)
    {
      return iterator(ptr + offset);
    }

    // Spostamentio all'indietro della posizione
    iterator operator-(int offset)
    {
      return iterator(ptr - offset);
    }

    // Spostamentio in avanti della posizione
    iterator &operator+=(int offset)
    {
      ptr += offset;
      return *this;
    }

    // Spostamentio all'indietro della posizione
    iterator &operator-=(int offset)
    {
      ptr -= offset;
      return *this;
    }

    // Numero di elementi tra due iteratori
    difference_type operator-(const iterator &other)
    {
      return ptr - other.ptr;
    }

    // Uguaglianza
    bool operator==(const iterator &other) const
    {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const iterator &other) const
    {
      return ptr != other.ptr;
    }

    // Confronto
    bool operator>(const iterator &other) const
    {
      return ptr > other.ptr;
    }

    bool operator>=(const iterator &other) const
    {
      return ptr >= other.ptr;
    }

    // Confronto
    bool operator<(const iterator &other) const
    {
      return ptr < other.ptr;
    }

    // Confronto
    bool operator<=(const iterator &other) const
    {
      return ptr <= other.ptr;
    }

  private:

    T *ptr;
    friend class SortedArray;
    
    iterator(T *p)
    {
      ptr = p;
    }

  }; // classe iterator
/**
    @brief Iteratore inizio sequenza
    
    @return iteratore 
    @ref iterator
  */
  iterator begin()
  {
    return iterator(_array);
  }

/**
    @brief Iteratore fine sequenza
    
    nota: non dereferenzializzarlo : non punta a nessun valore appartenente all'array
    
    @return iteratore 
    @ref iterator
  */
  iterator end()
  {
    return iterator(_array + _size);
  }

private:

  int get_index_of(const value_type &target)
  {
    equal_policy eq;
    order_policy ord;

    for (int i = 0; i < _size; ++i)
    {
      if (eq(target, _array[i]))
      {
        return i;
      }
      else if (ord(target, _array[i]))
      {
        std::cout << "cutting prematurely" << std::endl;
        return -1;
      }
    }
    return -1;
  }

private:
  value_type *_array;
  size_type _size;
};

/**
    @brief Ridefinizione operatore di stream su SortedArray
    
    @ref SortedArray::size
  */
template <typename T, typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const SortedArray<T, P, Q> array)
{
  os << "array of dim:" << array.size() << '\t' << "| ";
  for (int i = 0; i < array.size(); i++)
  {
    os << array[i] << ' ';
  }
  os << std::endl;
  return os;
}

#endif