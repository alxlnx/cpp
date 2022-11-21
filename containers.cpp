#include <iostream>

/* TODO:
Find out how copy() works. See Appendix in the book.
Find out how initializer_list<T> works. See Appendix in the book.
NB: the list needs to be passed BY VALUE to my::vector::vector() due to implementation details.
*/

namespace my {
  template <typename T>
  class vector {
  // How about we add some iterators and using value_type = T, using iter_type = T* alongside them?
  // How about no? I'm done implementing this monster.
  public:
    // Single-arg constructor defines conversion from vector to int.
    // Now, is "vector v1 = 10" okay? No, idk what this would mean. Therefore, we need to disallow such implicitness.
    // Rule of thumb: ALWAYS DECLARE SINGLE-ARG CONSTRUCTOS AS EXPLICIT, ALLOW IMPLICIT CONVERSIONS ONLY IF YOU HAVE A GOOD REASON TO DO THAT.
    explicit vector(int s) : sz{s}, elem{new T[sz]}, space{s}
    {
      for (int i{}; i < sz; ++i) elem[i] = T{};
    }

    ~vector() { delete[] elem; }

    vector(std::initializer_list<T> lst) : sz{lst.size()}, elem{new T[sz]}, space{lst.size()}
    {
      std::copy(lst.begin(), lst.end(), elem);
    }

    // Vector should have value semantics.
    // Ptrs should have pointer semantics.
    // Do I need a deep copy? If yes, then define copy assignment and consruction.

    // Default behaviour for copy constructors is to copy all elements. For ptr that means shallow copy, and we want deep.
    // That is not correct for vector since "vector v1 = v2" === "v1 and v2 SHARE elem".
    vector(const vector&);

    // Default behaviour for copy assignment is the same as of copy constructors.
    // Note that this time "v1 = v2" === "v1 and v2 SHARE elem AND v1 loses access to its old elements (i.e. memory leak)".
    vector<T>& operator=(const vector&);

    // Steal reosurces, consider "vector v = fill_vector(std::cin)"
    vector(vector&&);

    vector<T>& operator=(vector&&);

    T& operator[](int n) { return elem[n]; }
    T operator[](int n) const { return elem[n]; }
    // how tf do I use exceptions???
    T& at(int n) { if (n < 0 or n >= sz) { throw out_of_range{}; } return elem[n]; }
    T at(int n) const { if (n < 0 or n >= sz) { throw out_of_range{}; } return elem[n]; }
    
    vector() : sz{0}, elem{nullptr}, space{0} {}

    int capacity() const { return space; }
    int size() const { return sz; }

    void reserve(int);
    void resize(int, T def = T{});

    void push_back(const T& d);
  private:
    T* elem;
    int sz;
    int space;
    static constexpr int initial_space { 10 };
    class out_of_range{};
  };

  template <typename T> 
  vector<T>::vector(const vector& arg) : sz{arg.sz}, elem{new double[sz]}, space{arg.sz} 
  {
    std::copy(arg.elem, arg.elem + sz, elem);
  }

  template <typename T>
  vector<T>& vector<T>::operator=(const vector& arg)
  {
    if (&arg == this) return;

    if (space >= arg.sz) {
      for(int i{}; i < arg.sz; ++i) elem[i] = arg.elem[i];
      sz = arg.sz;
      return *this;
    }

    // NB: the ifs above are purely for optimzation.

    // copy source elements
    T* p = new T[arg.sz];
    std::copy(arg.elem, arg.elem + arg.sz, p);

    // clean up old ones
    // Rule of thumb: DO NOT DELETE OLD DATA BEFORE YOU HAVE A REPLACEMENT FOR IT.
    // delete[] elem -> copy(..., elem) would break "v = v"
    delete[] elem;

    // finish assignment
    sz = arg.sz;
    elem = p;
    space = sz;

    return *this;
  }

  template <typename T>
  vector<T>::vector(vector&& arg) : sz{arg.sz}, elem{arg.elem}, space{arg.space}
  {
    arg.sz = 0;
    arg.elem = nullptr;
  }

  template <typename T>
  vector<T>& vector<T>::operator=(vector&& arg) 
  {
    delete[] elem;
    sz = arg.sz;
    elem = arg.elem;
    space = arg.space;
    arg.sz = 0;
    arg.elem = nullptr;
    return *this;
  }

  template <typename T>
  void vector<T>::reserve(int newalloc)
  {
    if (newalloc <= space) return;
    T* p = new T[newalloc];
    std::copy(elem, elem + sz, p);  // that is diff. form the book
    delete[] elem;
    elem = p;
    space = newalloc;
  }

  template <typename T>
  void vector<T>::resize(int newsize, T def)
  {
     reserve(newsize);
     for (int i{sz}; i < newsize; ++i) elem[i] = def;
     sz = newsize;
  }

  template <typename T>
  void vector<T>::push_back(const T& d)
  {
    if (space == 0) reserve(initial_space);
    else if (sz == space) reserve(space * 2);
    elem[sz] = d;
    sz++;
  }
} // my namespace

int main() {
  my::vector<double> v{};
  v.push_back(2.2);
  std::cout << v.at(0);
  return 0;
}
