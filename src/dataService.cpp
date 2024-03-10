#include "dataService.hpp"
#include "account.hpp"

dataService::dataService(){}
dataService::~dataService(){}

account::account dataService::getAccount(std::string username, std::string password){
    for (auto account : accounts){
        if (account.login(username, password)){
            return account;
        }
    }
    return account::account("Nothing found", "1234", "Nothing found at all.", 1234);
}

void dataService::displayAllAccounts(){
    for (auto account : accounts){
        std::cout << account << std::endl;
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
    for (auto account : accounts){
        if (account.login(username, password)){
            std::cout << "found" << std::endl;
            return account.getAccountNr();
        }
    }
    return 0;
}
