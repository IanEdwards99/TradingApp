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
        std::string username;
        std::string password;
        std::string customer_name;
        int account_nr;
        std::time_t dateCreated;
        std::time_t dateDeleted;
        std::vector<transaction> transactions;
        double balance = 1000.0;
    public:
        account();
        account(std::string username, std::string password, std::string account_name, int account_nr);
        ~account();

        friend std::ostream& operator<<(std::ostream& os, const account & outputAccount);
        template<typename T>
        friend std::ostream& operator<<(std::ostream& os, const std::vector<T> & value);      
        int getAccountNr();
        std::string getCustomerName();
        std::vector<transaction>& getTransactions();
        std::vector<stock> getStocks() const;
        double getBalance() const;
        int topUpBalance(double Amount);
        int buyShare(stock stock, int quantity);
        int login(std::string username, std::string password);
        operator std::string() const;
    };
}
#endif
