#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
class MyContainer
{
public:
  typedef int size_type;

  class iterator
  {
  public:
    typedef iterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    iterator(pointer ptr) : ptr_(ptr) {}
    self_type operator++()                { self_type i = *this; ptr_++; return i; }
    self_type operator++(int junk)        { ptr_++; return *this; }
    reference operator*()                 { return *ptr_; }
    pointer operator->()                  { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
  private:
      pointer ptr_;
  };

  class const_iterator
  {
  public:
    typedef const_iterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    const_iterator(pointer ptr) : ptr_(ptr) {}

    self_type operator++()                { self_type i = *this; ptr_++; return i; }
    self_type operator++(int junk)        { ptr_++; return *this; }
    reference operator*()                 { return *ptr_; }
    pointer operator->()                  { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
  private:
      pointer ptr_;
  };
  
  MyContainer(size_type size) : size_(size) {
    data_ = new T[size_];
  }
  size_type size() const { return size_; }

  T& operator[](size_type index) { return data_[index]; }
  const T& operator[](size_type index) const { return data_[index]; }

  iterator begin()             { return iterator(data_);         }
  iterator end()               { return iterator(data_ + size_); }
  const_iterator begin() const { return iterator(data_);         }
  const_iterator end()   const { return iterator(data_ + size_); }
private:
  T* data_;
  size_type size_; 
};

using namespace std;

int main(int argc, char **argv)
{
  MyContainer<int> mc(10);
  mc[0] = 101;
  mc[1] = 102;
  mc[2] = 103;
  for(auto item = mc.begin(); item != mc.end(); item++)
    cout << *item << endl;

  return -1;
}
