#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(
    const std::string& category, 
    const std::string& name, 
    double price, 
    int qty,
    const std::string& isbn,
    const std::string& author) :
  Product(category, name, price, qty), isbn_(isbn), author_(author)
{
}

Book::~Book() 
{
}

std::set<std::string> Book::keywords() const {
  std::set<std::string> nameKey = parseStringToWords(name_);
  std::set<std::string> authorKey = parseStringToWords(author_);
  std::set<std::string> result = setUnion(nameKey, authorKey);
  result.insert(convToLower(isbn_));
  return result;
}

std::string Book::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left. ";
  return ss.str();  
}

void Book::dump(std::ostream& os) const {
  Product::dump(os);
  os << isbn_ << "\n" << author_ << endl;
}





