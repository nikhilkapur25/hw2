#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "datastore.h"

class MyDataStore : public DataStore {
public:
  MyDataStore(); 
  ~MyDataStore();

  void addProduct(Product* p) override;
  void addUser(User* u) override; 
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;
  void addToCart(const std::string& username, int hitResultIndex, const std::vector<Product*>& hits);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);
  
private:
  std::set<Product*> products_;
  std::set<User*> users_;
  std::map<std::string, std::set<Product*>> keywordMap_;
  std::map<std::string, std::vector<Product*>> userCarts_;
};
#endif




