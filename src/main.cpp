#include "account.hpp"
#include <vector>

void displayStockList(std::vector<stock> stockList){
    std::cout << "===============================================" << std::endl
              << "Currently available stocks on Janky Trades Ltd." << std::endl
              << "===============================================" << std::endl;
    for (auto i : stockList){
        std::cout << i << std::endl;
    }
}

int main(){
    int account_amount = 0;
    std::vector<stock> stocks = {stock("MSFT", "Microsoft corporation limited", 750.00), stock("GOOG", "Google enterprises", 800.00)
    , stock("TSLA", "Tesla electric vehicles", 400.00)};

    std::vector<account::account*> Accounts;
    Accounts.push_back(new account::account("Ian Edwards", "1234", account_amount));
    account_amount += 1;
    
    std::cout << *Accounts[0] << std::endl;
    displayStockList(stocks);


    //User buys a MSFT share:
    int status = Accounts[0]->buyShare(stocks[0], 3);
    std::vector<transaction> transactions = Accounts[0]->getTransactions();
    for (auto i : transactions){
        std::cout << i << std::endl;
    }
}

