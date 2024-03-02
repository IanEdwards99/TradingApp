#ifndef STOCK_HPP
#define STOCK_HPP

#include <string>

namespace stockSpace {
    class stock
    {
    private:
        /* data */
        std::string ID;
        std::string description;
        double price;
        
    public:
        stock(/* args */){};
        ~stock(){};

        std::string getID(){
            return ID;
        };

        std::string getDescription(){
            return description;
        };

        double getPrice(){
            return price;
        };
    };
}
#endif
