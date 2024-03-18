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
    stock transactedStock;
    double quantity;
    double cost;

public:
    transaction(std::time_t date, stock stockName, double amount, double value);
    ~transaction();
    operator std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const transaction& outputTransaction);
    stock getStock();
};
#endif
