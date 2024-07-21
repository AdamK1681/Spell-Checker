/*
Name: Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
This file contains the Implementation for the HashTableLinear class. It is virtually identical to HashTable class, which can be
found in the "quadratic_probing.h" file. The primary difference is the helper functions that deal w/ prime number have to be their
own function as due to an error occuring if the ones from the aforementioned file are used.
*/

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace {
// Internal method to test if a positive number is prime.
bool IsPrimeLinear(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}

// Internal method to return a prime number at least as large as n.
int NextPrimeLinear(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeLinear(n)) n += 2;  
  return n;
}

}  // namespace


// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrimeLinear(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    collisions = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

//Helpers

 //number of the elements inside the hash table (N)
int getNumElements() 
{
  return current_size_;
}

//size of the hash table (T)
int getTableSize() 
{
  return array_.size();
}
    
//number of collisions (C)
int getNumCollisions() 
{
  return collisions;
}
    
// collisions are cleared
void clearCol() 
{
  collisions = 0;
}	

private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable int collisions = 0; //Variable which keeps track of the number of collisions, not in original/provided code
  
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      current_pos ++;// Compute ith probe. offset not needed
      collisions++; 
      if (current_pos >= array_.size()) current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeLinear(2 * old_array.size()));
    for (auto & entry : array_) entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
    {
      if (entry.info_ == ACTIVE) Insert(std::move(entry.element_));
    }
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
};

#endif  // LINEAR_PROBING_H
