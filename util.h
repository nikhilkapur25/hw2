#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  // size_t max;
  std::set<T> result;

  const std::set<T>* smaller;
  const std::set<T>* larger;

  if(s1.size() > s2.size()) {
    smaller = &s1;
    larger = &s2;
  } 
  else{ 
    smaller = &s2;
    larger = &s1;
  }
  for(T item : *smaller) {
    if(larger->find(item) != larger->end()) {
       result.insert(item);
     }
  }


  // for(const T& i : smaller) {
  //   if(larger.find(i) != larger.end()) {
  //     result.insert(i);
  //   }
  // }
  return result;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> result = s1;
  result.insert(s2.begin(), s2.end());
  // size_t max;
  // std::set<T> result;
  // const std::set<T>& smaller = s1;
  // const std::set<T>& larger = s2;
  
  // if (s1.empty()) {
  //   return s2;
  // }
  
  // if(s2.empty()) {
  //   return s1;
  // }

  // if(s1.size() > s2.size()) {
  //   smaller = s1;
  //   larger = s2;
  // } 
  // else{ 
  //   smaller = s2;
  //   larger = s1;
  // }

  // result = larger; 
  // for(const T& t : smaller) {
  //   result.insert(t);
  // }

  // for(const T& i : larger) 
  // {
  //   if (smaller.find(i) = smaller.end()) {
  //     if (result.find(i) = result.end()) {
  //       result.insert(i);
  //     }
  //   }
  // }
  return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
