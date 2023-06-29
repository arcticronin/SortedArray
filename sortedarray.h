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

  Classe che vuole rappresentare un array dinamico di interi.
*/
template <typename T, typename P, typename Q>
class SortedArray
{
public:
  typedef T value_type;           ///< Tipo del dato dell'array
  typedef unsigned int size_type; ///< Tipo del dato size
  typedef P order_policy;
  typedef Q equal_policy;

  /**
    @brief Costruttore di default

    1° MEtodo FONDAMENTALE: COSTRUTTORE DI DEFAULT
    Il cosruttore di default serve a inizializzare i dati membro
    per rappresentare un SortedArray vuoto

    @post _array = nullptr
    @post _size = 0
  */
  SortedArray() : _array(nullptr), _size(0)
  { // Initialization list
    // I costruttori messi nella initialization list servono per
    // inizializzare (creare + impostare un valore) i dati membro.
    // Sono eseguiti prima di qualunque operazione interna al
    // costruttore.

#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray()" << std::endl;
#endif
  }

  //   1. Un costruttore secondario che costruisce un SortedArray a partire dai
  // dati rappresentati da due iteratori generici di inizio e fine sequenza;
  // Constructor with iterators

  template <typename Iterator>
  SortedArray(Iterator begin, Iterator end) : _array(nullptr), _size(0)
  {
    while( begin != end){
      this->insert(*begin);
      ++begin;
    }
  }

  /**
    @brief Distruttore

    2° MEtodo FONDAMENTALE: DISTRUTTORE
    Distruttore della classe. Il distruttore deve rimuovere tutte
    le risorse usate dalla classe. In questo caso l'array allocato
    sullo heap deve essere deallocato.
  */
  ~SortedArray()
  {
    this->makeEmpty();
#ifndef NDEBUG
    std::cout << "SortedArray::~SortedArray()" << std::endl;
#endif
  }

// TODO review
   // Secondary constructor taking another SortedArray
  template <typename U, typename R, typename S>
  SortedArray(const SortedArray<U, R, S> &other) : _array(nullptr), _size(0)
  {
    _size = other.getSize();
    _array = new value_type[_size];
    try
    {
      for (size_type i = 0; i < _size; ++i)
        _array[i] = static_cast<value_type>(other[i]);
    }
    catch (...)
    {
      delete[] _array;
      _array = nullptr;
      _size = 0;
      throw;
    }
    // Implementation
  }
  ///// TODO review

  // Other member functions

  /**
    @brief Copy Constructor

    3° MEtodo FONDAMENTALE: COPY CONSTRUCTOR
    Costruttore di copia. Serve a creare un oggetto come copia di un
    altro oggetto. I due oggetti devono essere indipendenti.

    @param other SortedArray sorgente da copiare

    @post _array != nullptr
    @post _size = other._size
  */
  SortedArray(const SortedArray &other) : _array(nullptr), _size(0)
  {
    _array = new value_type[other._size];
    _size = other._size;
    try
    { // TODO riportare questo in TUTTE LE FUNZIONI
      for (size_type i = 0; i < _size; ++i)
        _array[i] = other._array[i];
    }
    catch (...)
    {
      delete[] _array;
      _array = nullptr;
      _size = 0;
      throw;
    }
#ifndef NDEBUG
    std::cout << "SortedArray::SortedArray(const SortedArray&)" << std::endl;
#endif
  }

  /**
    @brief Operatore di assegnamento

    4° Metodo FONDAMENTALE: OPERATORE ASSEGNAMENTO
    L'operatore di assegnamento serve a copiare il contenuto di un oggetto
    in un altro oggetto dello stesso tipo. I due oggetti devono essere
    indipendenti.

    @param other SortedArray sorgenete da copiare

    @return un reference all'oggetto corrente

    @post _SortedArray != nullptr
    @post _size = other._size
  */
  SortedArray &operator=(const SortedArray &other)
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

  void insert(const value_type &item)
  {

    value_type *new_array = nullptr;
    try
    {
      new_array = new value_type[_size + 1];
    }
    catch (...)
    {
      throw;
      // return;
    }

    int index = searchsorted(item);
    // get_insert_index

    // TODO check se può fallire
    if (_array == nullptr)
    {
      new_array[0] = item;
      std::swap(_array, new_array);
      _size = 1;
      return;
    }

    // copy first part
    for (int i = 0; i < index; ++i)
    {
      new_array[i] = _array[i];
    }

    // insert
    new_array[index] = item;

    // copy second part
    for (int i = index; i < _size; i++)
    {
      new_array[i + 1] = _array[i];
    }
    std::swap(new_array, _array);
    delete[] new_array;
    _size += 1;
  }

  void remove(const value_type &item)
  {

    int index = get_index_of(item);
    assert(index != -1);

    value_type *new_array = nullptr;

    if (_size == 1)
    {
      assert(index == 0);
      std::swap(_array, new_array);
      delete[] new_array;
      _size = 0;
      return;
    }

    try
    {
      new_array = new value_type[_size - 1];
    }
    catch (...)
    {
      throw;
      // return;
    }
    // get_insert_index

    // TODO check se può fallire
    // copy first part
    for (int i = 0; i < index; ++i)
    {
      new_array[i] = _array[i];
    }

    // copy second part skipping index
    for (int i = index; i < _size - 1; i++)
    {
      new_array[i] = _array[i + 1];
    }
    std::swap(new_array, _array);
    delete[] new_array;
    _size -= 1;
  }

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

  void makeEmpty()
  {
    delete[] _array;
    _array = nullptr;
    _size = 0;
  }

  bool find(const value_type &target)
  {
    return (get_index_of(target) != -1);
  }

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

  template <typename Filter>
  SortedArray filter(Filter filter)
  {
    // init things
    SortedArray<value_type, order_policy, equal_policy> result;

    // reverse to have better insert time
    for (int i = _size - 1; i >= 0; --i)
    {
      if (filter(_array[i]))
        result.insert(_array[i]);
    }
    return result;
  }

  /**
    @brief Accesso alla dimensione dell'array (stile C++)

    Metodo per ottenere la dimensione dell'array dinamico

    @return dimensione dell'array dinamico
  */
  size_type size(void) const
  {
    return _size;
  }

  /**
    @brief Accesso ai dati in lettura (stile Java)

    Metodo getter per leggere il valore index-esimo dell'array

    @param index indice della cella dell'array da leggere

    @return valore della cella index-esima

    @pre index < size()
  */
  value_type get_value(size_type index) const
  {
    assert(index < _size);

    return _array[index];
  }

  /**
    @brief Accesso ai dati in scrittura (stile Java)

    Metodo setter per scrivere un valore nella cella index-esima dell'array

    @param index indice della cella dell'array da scrivere
    @param value valore da scrivere nella cella

    @pre index < size()
  */
  void set_value(unsigned int index, const value_type &value)
  {
    assert(index < _size);

    _array[index] = value;
  }

  /**
    @brief Getter/Setter della cella index-esima (stile C++)

    Metodo che permette di leggere e/o scrivere la cella
    index-esima dell'array

    @param index della cella da leggere/scrivere

    @return reference alla cella index-esima

    @pre index < size()
  */
  value_type &value(size_type index)
  {
    assert(index < _size);

    return _array[index];
  }

  /**
    @brief Getter della cella index-esima (stile C++)

    Metodo che permette di leggere la cella
    index-esima dell'array. Il metodo si può usare
    solo su istanze costanti della classe.

    @param index della cella da leggere

    @return reference alla cella index-esima

    @pre index < size()
  */
  const value_type &value(size_type index) const
  {
    assert(index < _size);

    return _array[index];
  }

  /**
    @brief Getter/Setter della cella index-esima (stile op[])

    Metodo che permette di leggere e/o scrivere la cella
    index-esima dell'array

    @param index della cella da leggere/scrivere

    @return reference alla cella index-esima

    @pre index < size()
  */
  value_type &operator[](size_type index)
  {
    assert(index < _size);

    return _array[index];
  }

  /**
    @brief Getter della cella index-esima (stile op[])

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
    @brief ridefinizione operatore di stream

    Ridefinizione dell'operatore di stream per scrivere un
    SortedArray su uno stream di output

    @param os stream di output (operando di sinistra)
    @param db SortedArray da scrivere (operando di destra)

    @return reference allo stream di output
  */
  // Diamo accesso alla funzione globale, esterna alla classe, alle
  // parti private della classe
  friend std::ostream &operator<<(std::ostream &os, const SortedArray<T, P, Q> &db)
  {
    os << "size: " << db._size << " | ";
    for (typename SortedArray<T, P, Q>::size_type i = 0; i < db.size(); i++)
      os << db[i] << ' ';
    os << std::endl;
    return os;
  }

  // Implementazione completa di ietartori di tipo random.
  // Come si vedrà, i metodi sono solo dei wrapper a delle
  // operazioni tra puntatori.

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

    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class SortedArray;

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    iterator(T *p)
    {
      ptr = p;
    }

    // !!! Eventuali altri metodi privati

  }; // classe iterator

  // Ritorna l'iteratore all'inizio della sequenza dati
  iterator begin()
  {
    return iterator(_array);
  }

  // Ritorna l'iteratore alla fine della sequenza dati
  iterator end()
  {
    return iterator(_array + _size);
  }

private:
  value_type *_array;
  size_type _size;
};

#endif