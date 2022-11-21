#include <iostream>

/* TODO:
Find out how copy() works. See Appendix in the book.
Find out how initializer_list<T> works. See Appendix in the book.
NB: the list needs to be passed BY VALUE to my::vector::vector() due to implementation details.
*/

namespace my {
  class vector {
  public:
    vector(int s) : sz{s}, elem{new double[sz]} 
    {
      for (int i{}; i < sz; ++i) elem[i] = 0.0;
    }

    ~vector() { delete[] elem; }

    vector(std::initializer_list<double> lst) : sz{lst.size()}, elem{new double[sz]} 
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
    vector& operator=(const vector&);
  private:
    double* elem;
    int sz;
  };

  vector::vector(const vector& arg) : sz{arg.sz}, elem{new double[sz]} 
  {
    std::copy(arg.elem, arg.elem + sz, elem);
  }

  vector& vector::operator=(const vector& arg)
  {
    // copy source elements
    double* p = new double[arg.sz];
    std::copy(arg.elem, arg.elem + arg.sz, p);

    // clean up old ones
    // Rule of thumb: DO NOT DELETE OLD DATA BEFORE YOU HAVE A REPLACEMENT FOR IT.
    // delete[] elem -> copy(..., elem) would break "v = v"
    delete[] elem;

    // finish assignment
    sz = arg.sz;
    elem = p;

    return *this;
  }
} // my namespace