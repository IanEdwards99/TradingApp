#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "stock.hpp"
#include <ctime>
#include <stdexcept>

namespace transactionSpace{
    class transaction
    {
    private:
        /* data */
        std::time_t transactionDate;
        stockSpace::stock transactedStock;
        double quantity;
        double cost;

    public:
        transaction(std::time_t date, stockSpace::stock stockName, double amount, double value) : 
            transactionDate(date), 
            transactedStock(stockName), 
            quantity(amount), 
            cost(value)
            {};

        ~transaction(){};
    };
}
#endif
