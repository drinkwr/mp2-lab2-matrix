// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be less than max_vector_size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) //noexcept
  {
  }
  ~TDynamicVector()
  {
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      
      delete[] this->pMem;
      this->sz = v.sz;
      this->pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) //noexcept
  {
      return *this;
  }

  size_t size() const //noexcept
    { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz)
      {
          throw "Incorrect index";
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz)
      {
          throw "Incorrect index";
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz)
      {
          throw "Incorrect index";
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
      {
          throw "Incorrect index";
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const //noexcept
  {
      if(sz != v.sz)
          return false;
      for(int i = 0; i < sz; i++)
          if(pMem[i] != v.pMem[i])
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const //noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + val;
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (v.sz != this->sz) throw "Incorrect vector size";

      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (v.sz != this->sz) throw "Incorrect vector size";

      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - v.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (v.sz != this->sz) throw "Incorrect vector size";

      T res = 0;
      for (int i = 0; i < sz; i++)
          res= res + pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) //noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T> >
{
  using TDynamicVector<TDynamicVector<T> >::pMem;
  using TDynamicVector<TDynamicVector<T> >::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
  {
      if (sz == 0)
        throw out_of_range("MAtrix size should be greater than zero");
      if (sz > MAX_MATRIX_SIZE)
        throw out_of_range("Matrix size should be less than max_vector_size");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

    size_t size() const //noexcept
      { return sz; }
  
  using TDynamicVector<TDynamicVector<T> >::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const //noexcept
  {
      if(sz != m.sz)
          return false;
      for(int i = 0; i < sz; i++)
          if(pMem[i] != m.pMem[i])
              return false;
      return true;
  }
    
    TDynamicMatrix& operator=(const TDynamicMatrix& m)
    {
        if (this == &m) return *this;
        
        delete[] this->pMem;
        this->sz = m.sz;
        //this->pMem = new(TDynamicVector<int>**) (sz);
        for (int i = 0; i < sz; i++)
            pMem[i] = m.pMem[i];
        return *this;
    }
    
  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz != this->sz) throw "Incorrect matrix size";

      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + pMem[i];
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz != this->sz) throw "Incorrect matrix size";

      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - pMem[i];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      
  }

  // ввод/вывод
  friend istream&  operator>>(istream& in, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          in >> v.pMem[i];
      return in;
  }
  friend ostream& operator<<(ostream& out, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          out << v.pMem[i] << " ";
      out << "\n";
      return out;
  }
};

#endif
