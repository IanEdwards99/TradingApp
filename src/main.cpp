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

void clearConsole() {
    // CSI[2J clears the screen, CSI[H moves the cursor to the top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void displayStart(){
    std::cout <<"==========================\n" <<
                "Simple Trading Application\n" << 
                "==========================\n" <<
                "q to exit application.\n" <<
                "1: Login\n" <<
                "2: Create account" << std::endl;
}

void displayMenu(){
    std::cout <<"==========================\n" <<
                "Simple Trading Application\n" << 
                "==========================\n" <<
                "q to exit application.\n" <<
                "1: View stocks\n" <<
                "2: Transaction history\n" << 
                "3: Account details" << std::endl;

}

int login(std::vector<account::account*> accounts){
    std::cout << "Please enter your username:" << std::endl;
    std::string username;
    std::string password;
    std::cin >> username;
    std::cout << "Please enter your password:" << std::endl;
    std::cin >> password;

    for (auto account : accounts){
        if (account->login(username, password)){
            return account->getAccountNr();
        }
    }
    return -1;
}

account::account* createAccount(){
    std::cout << "Please enter a username:" << std::endl;
    std::string username;
    std::string password;
    std::string password_2;
    std::string fullname;
    std::cin >> username;
    std::cout << "Please enter a password:" << std::endl;
    std::cin >> password;
    std::cout << "Please re-enter your password:" << std::endl;
    std::cin >> password_2;
    if (password != password_2){
        do
        {
            std::cout << "Please re-enter your password:" << std::endl;
            std::cin >> password_2;
        } while (password != password_2);
        
    }
    std::cout << "Please enter your fullname:" << std::endl;
    std::cin >> fullname;
    return new account::account(username, password, fullname, time(0) % 1000);
}

std::ostream& operator<<(std::ostream& os, const std::vector<account::account*> & accountsList){
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

    std::vector<account::account*> Accounts;
    Accounts.push_back(new account::account("iedwards", "1234", "Ian Edwards", account_amount));
    account_amount += 1;

    std::cout << Accounts << std::endl;
    std::cout << *Accounts[0] << std::endl;

    std::cout << stocks << std::endl;


    //User buys a MSFT share:
    int status = Accounts[0]->buyShare(stocks[0], 3);
    std::cout << Accounts[0]->getTransactions() << std::endl;

    char choice;
    int mynr;
    do
    {
        clearConsole();
        displayStart();
        std::cin >> choice; 
        switch(choice){
            case '1':
                mynr = login(Accounts);
                if (mynr != -1){
                    char choose;
                    while (choose != 'q'){
                        clearConsole();
                        displayMenu();
                        std::cin >> choose;
                    } 
                }
                else std::cout << "Incorrect login details provided. c to continue to main menu:" << std::endl;
                char val;
                std::cin >> val;
                break;
            case '2':
                Accounts.push_back(createAccount());
                break;
        }
    } while (choice != 'q');
}

