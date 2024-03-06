#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <ctime>
#include <chrono>
#include <vector>
#include "transaction.hpp"
#include "stock.hpp"
#include <iostream>

namespace account {
    class account
    {
    private:
        /* data */
        std::string account_name;
        std::string password;
        int account_nr;
        std::time_t dateCreated;
        std::time_t dateDeleted;
        std::vector<transaction> transactions;
        std::vector<stock> stocks;
    public:
        account(std::string account_name, std::string password, int account_nr);
        ~account();

        std::vector<transaction> getTransactions();
        std::vector<stock> getStocks();
        friend std::ostream& operator<<(std::ostream& os, const account & outputAccount);
        friend std::ostream& operator<<(std::ostream& os, const std::vector<transaction> & outputTransactions);
        friend std::ostream& operator<<(std::ostream& os, const std::vector<stock> & outputStocks);
        

        int buyShare(stock stock, int quantity);
        
    };
}
#endif
