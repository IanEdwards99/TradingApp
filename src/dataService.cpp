#include "dataService.hpp"
#include "account.hpp"

dataService::dataService(){}
dataService::~dataService(){}

account::account* dataService::getAccount(){
    if (dataService::activeAccount == nullptr){
        throw std::runtime_error("No active account set, unexpected situation encountered. Exiting...");
        exit(1);
    }
    return this->activeAccount;
}

void dataService::displayAllAccounts(){
    for (auto account : accounts){
        std::cout << account << std::endl << "Transactions: \n";
        for (auto i : account.getTransactions())
            std::cout << i << std::endl;
    }
}

int dataService::addAccount(std::string username, std::string password, std::string customer_name){
    account_amount += 1;
    accounts.push_back(account::account(username, password, customer_name, time(0) % 1000));
    return account_amount;
}

int dataService::addAccount(account::account userAccount){
    account_amount += 1;
    accounts.push_back(userAccount);
    return account_amount;
}

int dataService::login(std::string username, std::string password){
    for (auto& account : accounts){
        if (account.login(username, password)){
            this->activeAccount = &account;
            return account.getAccountNr();
        }
    }
    return 0;
}

std::vector<stock>& dataService::getStocks(){
    return stocks;
}

std::vector<account::account>& dataService::getAccounts(){
    return accounts;
}