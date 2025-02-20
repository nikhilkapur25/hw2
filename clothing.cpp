#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(
    const std::string& category, 
    const std::string& name, 
    double price, 
    int qty,
    const std::string& size,
    const std::string& brand) :
  Product(category, name, price, qty), size_(size), brand_(brand)
{

}

Clothing::~Clothing() 
{

}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> result = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);
  result.insert(brandWords.begin(), brandWords.end());
  return result;
}

std::string Clothing::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left. ";
  return ss.str();  
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
  os << size_ << "\n" << brand_ << endl;
}





