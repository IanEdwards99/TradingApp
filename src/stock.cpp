#include "stock.hpp"

namespace stockSpace{
    stock::stock(std::string ID, std::string description, double price) : ID(ID), description(description), price(price){};
    stock::~stock(){};

    std::string stock::getID(){
        return ID;
    };

    std::string stock::getDescription(){
        return description;
    };

    double stock::getPrice(){
        return price;
    };

    std::ostream& operator<<(std::ostream& os, const stock& outputStock){
        os << "Stock ID: " << outputStock.ID << "\nStock description: " << outputStock.description << "\nStock price: " << outputStock.price << std::endl;
        return os;
    };

}