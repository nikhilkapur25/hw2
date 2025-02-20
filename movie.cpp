#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(
    const std::string& category, 
    const std::string& name, 
    double price, 
    int qty,
    const std::string& genre,
    const std::string& rating) :
  Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

Movie::~Movie() 
{

}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> result = parseStringToWords(name_);
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left. ";
  return ss.str();  
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os);
  os << genre_ << "\n" << rating_ << endl;
}





