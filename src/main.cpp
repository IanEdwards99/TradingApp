#include "account.hpp"
#include "menu.hpp"
#include <vector>

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
    dataService myData = dataService();
    myData.addAccount("iedwards", "1234", "Ian Edwards");

    // //User buys a MSFT share:
    int i = myData.getAccounts()[0].buyShare(myData.getStocks()[1], 2); // Give Floris 2 GOOG shares.
    int j = myData.getAccounts()[1].buyShare(myData.getStocks()[0], 3); // Give Ian 3 MSFT shares.
    // myData.displayAllAccounts();

    BaseMenu* currentMenu = new homepage(myData);
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

