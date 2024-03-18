#include <vector>
#include <string>
#include <iostream>
#include "account.hpp"

class dataService
{
private:
    std::vector<account::account> accounts = {account::account("fliere", "1", "Floris Van Liere", 1)}; // Temporarily populate
    int account_amount = 0;
    account::account* activeAccount;
    std::vector<stock> stocks = {stock("MSFT", "Microsoft corporation limited", 750.00), stock("GOOG", "Google enterprises", 800.00)
    , stock("TSLA", "Tesla electric vehicles", 400.00)}; // Fill from database eventually.
public:
    dataService();
    ~dataService();
    account::account* getAccount();
    void displayAllAccounts();
    int addAccount(std::string username, std::string password, std::string customer_name);
    int addAccount(account::account userAccount);
    int login(std::string username, std::string password);
    std::vector<stock>& getStocks();

    std::vector<account::account>& getAccounts(); // Temp function to return all accounts. Not safe.
};



