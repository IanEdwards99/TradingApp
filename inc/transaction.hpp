#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "stock.hpp"
#include <ctime>
#include <stdexcept>

class transaction
{
private:
    /* data */
    std::time_t transactionDate;
    stock transactedStock; // stock being bought.
    double quantity; // quantity of stock.
    double cost; // current cost of stock at that moment.

public:
    transaction(std::time_t date, stock stockName, double amount);
    ~transaction();
    operator std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const transaction& outputTransaction);
    stock getStock();
};
#endif
