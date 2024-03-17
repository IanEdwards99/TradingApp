#ifndef STOCK_HPP
#define STOCK_HPP
#include <iostream>
#include <string>

class stock
{
private:
    /* data */
    std::string ID;
    std::string description;
    double price;
    
public:
    stock();
    
    stock(std::string ID, std::string description, double price);
    
    ~stock();

    std::string getID();

    std::string getDescription();

    double getPrice();

    friend std::ostream& operator<<(std::ostream& os, const stock& outputStock);

    operator std::string() const;
};
#endif
