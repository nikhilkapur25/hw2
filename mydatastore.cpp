#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include <algorithm>
#include "util.h"

using namespace std;

MyDataStore::MyDataStore() 
{
}

MyDataStore::~MyDataStore()
{
  for(Product* p : products_) {
    delete p;
  }
  for(User* u: users_) {
    delete u;
  }
}
 
void MyDataStore::addProduct(Product* p) {
  if (!p) {
    return;
  }
  products_.insert(p);
  std::set<std::string> keywords = p->keywords();
  
  for(const std::string& keyword : keywords) {
    // keyword = convToLower(keyword);
    keywordMap_[convToLower(keyword)].insert(p);
  }
}

void MyDataStore::addUser(User* u)  {
  if(!u) {
    return;
  }
  users_.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::vector<Product*> results;
  if(terms.empty()) {
    return results;
  }
  bool first = true;
  std::set<Product*> resultSet; 
  std::set<std::string> processedWords;

  for(const std::string& term : terms) {
    processedWords.insert(convToLower(term));
  }

  for(const std::string& term : terms) {
    std::set<std::string> parseWords = parseStringToWords(convToLower(term));
    processedWords.insert(parseWords.begin(), parseWords.end());
  }

 
  for(const std::string& term : processedWords) {
    if(keywordMap_.count(term) != 0) {
      std::set<Product*> productsForTerm = keywordMap_[term];
      if(first) {
        resultSet = productsForTerm;
        first = false;
      }
      else {
        if(type == 0) {
          resultSet = setIntersection(resultSet, productsForTerm);
        }
        else {
          resultSet = setUnion(resultSet, productsForTerm);
        }
      }
    }
    else if (type == 0 && !first) {
      resultSet.clear();
      break;
        // return results;
      }
    }
  
  for (Product* product : resultSet){
    results.push_back(product);
  }
  return results;
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n";
  for(Product* product : products_) {
    product->dump(ofile);
  }
  ofile << "</products>\n";

  ofile << "<users>\n";
  for(User* user : users_) {
    user->dump(ofile);
  }
  ofile << "</users>\n";
}

void MyDataStore::addToCart(const std::string& username, int hitResultIndex, const std::vector<Product*>& hits) {
  std::string lowerUsername = convToLower(username);
  User* target = nullptr;

  for(User* user : users_) {
    if(convToLower(user->getName()) == lowerUsername) {
      target = user; 
      break;
    }
  }

  if (!target) { 
    cout << "Invalid request" << endl;
    return;
  }

  if(hitResultIndex < 0 || hitResultIndex >= (int)hits.size()) {
    cout << "Invalid request" << endl;
    return;
  }
  userCarts_[lowerUsername].push_back(hits[hitResultIndex]);
}

void MyDataStore::viewCart(const std::string& username) {
  std::string lowerUsername = convToLower(username);
  User* target = nullptr;
  for(User* user : users_) {
    if(convToLower(user->getName()) == lowerUsername) {
      target = user;
      break;
    }
  }

  if(!target) {
    cout << "Invalid username" << endl;
    return;
  }
  
  if(userCarts_.find(lowerUsername) == userCarts_.end()) {
    userCarts_[lowerUsername] == std::vector<Product*>();
  }
  std::vector<Product*>& cart = userCarts_[lowerUsername];
  for(size_t i = 0; i < cart.size(); i++) {
    cout << "Item " << i + 1 << ":" << endl; // or i ?
    cout << cart[i]->displayString() << endl;
  }
}

void MyDataStore::buyCart(const std::string& username ) {
  std::string lowerUsername = convToLower(username);
  User* target = nullptr; 
  for(User* u : users_) {
    if(convToLower(u->getName()) == lowerUsername) {
      target = u;
      break;
    }
  }
  
  if(!target) {
    cout << "Invalid username" << endl;
    return;
  }

  if(userCarts_.find(lowerUsername) == userCarts_.end()) {
    userCarts_[lowerUsername] == std::vector<Product*>();
    return;
  }

  std::vector<Product*>& cart = userCarts_[username];
  std::vector<Product*> remainingItems;

  for(Product* p : cart) {
    if(p->getQty() > 0 && target->getBalance() >= p->getPrice()) {
      p->subtractQty(1);
      target->deductAmount(p->getPrice());
    }
    else {
      remainingItems.push_back(p);
    }
  }
  userCarts_[lowerUsername] = remainingItems;
}

