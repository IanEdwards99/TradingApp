#include "account.hpp"
#include <vector>

void displayStockList(std::vector<stockSpace::stock> stockList){
    std::cout << "===============================================" << std::endl
              << "Currently available stocks on Janky Trades Ltd." << std::endl
              << "===============================================" << std::endl;
    for (auto i : stockList){
        std::cout << i << std::endl;
    }
}

int main(){
    int account_amount = 0;
    std::vector<stockSpace::stock> stocks = {stockSpace::stock("MSFT", "Microsoft corporation limited", 750.00), stockSpace::stock("GOOG", "Google enterprises", 800.00)
    , stockSpace::stock("TSLA", "Tesla electric vehicles", 400.00)};
    std::vector<account::account*> Accounts;
    Accounts.push_back(new account::account("Ian Edwards", "1234", account_amount));
    account_amount += 1;
    Accounts[0]->displayAccount();
    displayStockList(stocks);
}

