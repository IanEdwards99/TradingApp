#include "account.hpp"
#include "menu.hpp"
#include <vector>

void displayStockList(std::vector<stock> stockList){
    std::cout << "===============================================" << std::endl
              << "Currently available stocks on Janky Trades Ltd." << std::endl
              << "===============================================" << std::endl;
    for (auto i : stockList){
        std::cout << i << std::endl;
    }
}

void clearConsole() {
    // CSI[2J clears the screen, CSI[H moves the cursor to the top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

std::ostream& operator<<(std::ostream& os, const std::vector<account::account> & accountsList){
        for (auto i : accountsList){
            os << i << std::endl;
        }
        return os;
    }

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & value){
    for (auto x : value){
        os << x << std::endl;
    }
    return os;
}

int main(){
    int account_amount = 0;
    std::vector<stock> stocks = {stock("MSFT", "Microsoft corporation limited", 750.00), stock("GOOG", "Google enterprises", 800.00)
    , stock("TSLA", "Tesla electric vehicles", 400.00)};
    dataService myData = dataService();
    account_amount += 1;
    myData.addAccount("iedwards", "1234", "Ian Edwards");
    myData.displayAllAccounts();
    std::cout << stocks << std::endl;

    // //User buys a MSFT share:
    // int status = Accounts[0].buyShare(stocks[0], 3);
    // std::cout << Accounts[0].getTransactions() << std::endl;

    BaseMenu* currentMenu = new homepage(&myData);
    bool quitSelected = false;
    while (!quitSelected)
    {
        // clearConsole();
        currentMenu->printText();
        char choice = 0;
        std::cin >> choice;

        BaseMenu* newMenuPtr = currentMenu->getNextMenu(choice, quitSelected);
        if (newMenuPtr != nullptr) { //if pointer is 0 like default, no new menu is created.
            delete currentMenu;
            currentMenu = newMenuPtr; // currentMenu is kept the same.
        }
    }

    return 0;
}

