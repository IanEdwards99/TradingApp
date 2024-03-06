#include "transaction.hpp"
transaction::transaction(std::time_t date, stock stockName, double amount, double value) : 
    transactionDate(date), 
    transactedStock(stockName), 
    quantity(amount), 
    cost(value)
    {}

transaction::~transaction(){}

std::ostream& operator<<(std::ostream& os, const transaction& outputTransaction) {
    auto val = outputTransaction.transactedStock;
    os << "Transaction for stock: " << val.getID() << std::endl <<
    "Transaction date: " << outputTransaction.transactionDate << std::endl <<
    "Share quantity: " << outputTransaction.quantity << std::endl << 
    "Total transaction Cost: " << outputTransaction.cost << std::endl;

    return os;
}


