#include "transaction.hpp"
transaction::transaction(std::time_t date, stock stockName, double amount, double value) : 
    transactionDate(date), 
    transactedStock(stockName), 
    quantity(amount), 
    cost(value)
    {}

transaction::~transaction(){}

transaction::operator std::string() const{
    stock val = transactedStock;
    return "Transaction for stock: " + val.getID() + "\nTransaction date: " + std::to_string(transactionDate) + "\nShare quantity: " + std::to_string(quantity) + "\nTotal transaction Cost: " + std::to_string(cost) + "\n";
}

std::ostream& operator<<(std::ostream& os, const transaction& outputTransaction) {
    stock val = outputTransaction.transactedStock;
    os << "Transaction for stock: " << val.getID() << std::endl <<
    "Transaction date: " << outputTransaction.transactionDate << std::endl <<
    "Share quantity: " << outputTransaction.quantity << std::endl << 
    "Total transaction Cost: " << outputTransaction.cost << std::endl;

    return os;
}

stock transaction::getStock(){
    return transactedStock;
}


