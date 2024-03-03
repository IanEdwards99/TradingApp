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
        std::vector<transactionSpace::transaction> transactions;
        std::vector<stockSpace::stock> stocks;
    public:
        account(std::string account_name, std::string password, int account_nr);
        ~account();

        void displayAccount(){
            std::cout << "Account name: " << account_name << std::endl << "Account password: " << password << std::endl
             << "Account number: " << account_nr << std::endl << "Date created: " << dateCreated << std::endl;
        };

        void displayTransactions();

    };
}
#endif
