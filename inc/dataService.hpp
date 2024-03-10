#include <vector>
#include <string>
#include <iostream>
#include "account.hpp"

class dataService
{
private:
    std::vector<account::account> accounts; // move into separate class eventually.
    int account_amount = 0;
public:
    dataService();
    ~dataService();
    account::account getAccount(std::string username, std::string password);
    void displayAllAccounts();
    int addAccount(std::string username, std::string password, std::string customer_name);
    int addAccount(account::account userAccount);
    int login(std::string username, std::string password);
};



