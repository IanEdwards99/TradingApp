#include <iostream>
#include <string>
#include <stdexcept>
#include "menu.hpp"
#include <unistd.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & value){
    for (auto x : value){
        os << x << std::endl;
    }
    return os;
}

BaseMenu::BaseMenu(dataService& data_service) : menuData(data_service)
{ 
    menuText = "This shouldn't ever be shown!"; 
} 
BaseMenu::~BaseMenu() { }
void BaseMenu::printText()
{
    std::cout << menuText << std::endl;
}

homepage::homepage(dataService& data_service) : BaseMenu(data_service)
{
    menuText = std::string("==========================\n") + "Simple Trading Application\n" + 
            "==========================\n" +
            "q to exit application.\n" +
            "1: Login\n" +
            "2: Create account";
}

BaseMenu* homepage::getNextMenu(char choice, bool& iIsQuitOptionSelected) // This is us actually defining the pure virtual method above
{
    BaseMenu *aNewMenu = nullptr; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice) 
    {
        case '1': //login chosen
        {
            if (homepage::login())
            {
                aNewMenu = new userHome(menuData);
            }
            else menuText += "\nIncorrect login credentials provided. Please make another selection:";
            break;
        }
        case '2': //create Account chosen
        {
            int abortStatus = createAccount(); // consider adding pointer argument to receive new account instead.
            if (abortStatus == 1)
            {
                iIsQuitOptionSelected = true;
            }
            else if (abortStatus == 2){
                menuText += "\nAborted account creation.";
            }
            break;}
        case 'q': // Quit
        {
            iIsQuitOptionSelected = true; break;
        }
        default:
        { break;}
    }
    return aNewMenu; // Sending it back to the main function
}

int homepage::login(){
    std::string username;
    std::string password;
    
    std::cout << "Please enter your username:" << std::endl;
    std::cin >> username;
    password = getpass("Please enter your password:\n");
    return menuData.login(username, password);
}

int checkForExit(std::string input){
    if (input == "q")
    {
        return 1;
    }
    else if (input == "b")
    {
        return 2;
    }
    return 0;
}

int homepage::createAccount(){ // return unique_ptr instead
    
    std::string username;
    std::string password;
    std::string password_2;
    std::string fullname;
    
    std::cout << "Please enter your fullname:\n";
    std::cin.ignore();
    std::getline(std::cin, fullname);
    int exitCheck = checkForExit(fullname);
    
    std::cout << "Please enter a username:\n";
    std::cin >> username;
    exitCheck = checkForExit(username);
    if (exitCheck != 0)
        return exitCheck;
    password = getpass("Please enter a password:\n");
    exitCheck = checkForExit(password);
    if (exitCheck != 0)
        return exitCheck;
    password_2 = getpass("Please re-enter your password:\n");
    exitCheck = checkForExit(password_2);
    if (exitCheck != 0)
        return exitCheck;
    if (password != password_2){
        do
        {
            password_2 = getpass("Please re-enter your password:\n");
            int exitCheck = checkForExit(password_2);
            if (exitCheck != 0)
                return exitCheck;
        } while (password != password_2);
        
    }

    if (exitCheck != 0)
        return exitCheck;
    menuData.addAccount(account::account(username, password, fullname, time(0) % 1000));
    return 0;
}

userHome::userHome(dataService& data_service) : BaseMenu(data_service)
{ menuText = std::string(
    "=============================\n") +
    " Welcome " + menuData.getAccount()->getCustomerName() + "\n" + 
    "=============================\n" +
    "q to exit application.\n" +
    "1: View stocks\n" +
    "2: Transaction history\n" +
    "3: Account details\n" +
    "4: Logout";
}
BaseMenu *userHome::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case '1':
        { aNewMenu = new stockMenu(menuData); break;}
        case '2':
        { aNewMenu = new TransactionHistory(menuData); break;}
        case '3':
        { aNewMenu = new accountDetailsMenu(menuData); break;}
        case '4':
        { aNewMenu = new homepage(menuData); break;}
        case 'q':
        {
            iIsQuitOptionSelected = true; break;
        }
        default:
        { break; }
    }
    return aNewMenu; 
}

stockMenu::stockMenu(dataService& data_service) : BaseMenu(data_service)
{ menuText = std::string(
    "===============================================\n") +
    "Currently available stocks on Janky Trades Ltd.\n" +
    "===============================================\n"
    "(Press \"b\" to go back)\n"                      ;
    for (auto i : menuData.getStocks()){
        menuText += i.getID() + " " + std::to_string(i.getPrice()) + "\n";
    }
    menuText += "-----------------------\nCurrently owned stocks:\n-----------------------\n";
    for (const auto i : menuData.getAccount()->getStocks()){
        menuText += i;
        menuText += "\n";
    }
    menuText += std::string(
    "\n-----------------------\nq to exit application.\n") +
    "1: Search/Purchase a specific stock\n" +
    "2: Sell a stock";
}
BaseMenu *stockMenu::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case '1':
        { 
            std::string stock_ID;
            std::cout << "Please enter the stock you would like to view:" << std::endl;
            std::cin >> stock_ID;
            bool found = false;
            stock selected_stock;
            for (auto i : menuData.getStocks()){
                if (i.getID() == stock_ID){
                    selected_stock = i;
                    found = true;
                    break;
                }
            }
            if (found)
                aNewMenu = new stockPage(menuData, selected_stock);
            else{ menuText += "\nNo stock found with given ID! Try again!"; }
            break;
        }
        case '2':
        { aNewMenu = new homepage(menuData); break;}
        case 'b':
        { aNewMenu = new userHome(menuData); break;}
        case 'q':
        {
            iIsQuitOptionSelected = true; break;
        }
        default:
        { break; }
    }
    return aNewMenu; 
}

TransactionHistory::TransactionHistory(dataService& data_service) : BaseMenu(data_service)
{ menuText = std::string(
    "===============================================\n") +
    " Transaction history for " + menuData.getAccount()->getCustomerName() + "\n"
    "===============================================\n"
    "(Press \"b\" to go back)\n"                      ;
    for (auto i : menuData.getAccount()->getTransactions()){
        menuText += i;
    }
    menuText += std::string(
    "\n-----------------------\nq to exit application.\n");
}
BaseMenu *TransactionHistory::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case 'b':
        { aNewMenu = new userHome(menuData); break;}
        case 'q':
        {
            iIsQuitOptionSelected = true; break;
        }
        default:
        { break; }
    }
    return aNewMenu; 
}

accountDetailsMenu::accountDetailsMenu(dataService& data_service) : BaseMenu(data_service)
{ menuText = std::string(
    "===============================================\n") +
    " Account details for " + menuData.getAccount()->getCustomerName() + "\n"
    "===============================================\n"
    "(Press \"b\" to go back)\n"                      ;
    menuText += *menuData.getAccount();
    menuText += "\n-----------------------\n1: Topup balance\n2: Withdraw money\nq to exit application.\n";
}
BaseMenu *accountDetailsMenu::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case 'b':
        { aNewMenu = new userHome(menuData); break;}
        case '1':
        {
            std::cout << std::string(
        "===============================================\n") +
        " Topup balance for " + menuData.getAccount()->getCustomerName() + "\n" +
        " Current balance: " + std::to_string(menuData.getAccount()->getBalance()) + 
    "\n===============================================\n"
        "(Press \"b\" to go back)"                      << std::endl;
        std::cout << std::string(
        "\n-----------------------\nq to exit application.\n") << std::endl;

        std::string input;
        try {
            std::cout <<  "Enter the amount you wish to top up your balance by:" << std::endl;
            std::cin >> input;
            account::account * currAccount = menuData.getAccount();
            currAccount->topUpBalance(std::stod(input));
            std::cout << std::to_string(std::stod(input)) + " successfully added to your account! Press any key to continue." << std::endl;
            std::cin >> input;
            aNewMenu = new accountDetailsMenu(menuData);
        }
        catch(const std::invalid_argument& e)
        {
            std::cout << "Incorrect input provided - please only enter numerical values when asked. Press any key to continue:" << std::endl;
            input = "";
            std::cin >> input;
        }        
        break; 
        }
        case '2':
        {
            std::cout << std::string(
             "===============================================\n") +
            " Withdraw money for " + menuData.getAccount()->getCustomerName() + "\n"
            " Current balance: " + std::to_string(menuData.getAccount()->getBalance()) + 
            "\n===============================================\n"
            "(Press \"b\" to go back)"                      << std::endl;
            std::cout << std::string(
            "\n-----------------------\nq to exit application.\n") << std::endl;

            std::string input;
            try {
                double withdrawal = 0;
                std::cout << "Enter the amount you wish to withdraw from your account:" << std::endl;
                std::cin >> withdrawal;
                menuData.getAccount()->topUpBalance(withdrawal*-1);
                std::cout << std::to_string(withdrawal) + " successfully withdrawn from your account!\nBalance remaining: $" + std::to_string(menuData.getAccount()->getBalance()) + "\nPress any key to continue:" << std::endl;
                std::cin >> input;
                aNewMenu = new accountDetailsMenu(menuData);
            }
            catch(const std::invalid_argument& e)
            {
                std::cout << "Incorrect input provided - please only enter numerical values when asked. Press any key to continue:" << std::endl;
                input = "";
                std::cin >> input;
            }        
            break; }
        case 'q':
        { iIsQuitOptionSelected = true; break; }
        default:
        { break; }
    }
    return aNewMenu; 
}

stockPage::stockPage(dataService& data_service, stock selected_stock) : BaseMenu(data_service), setStock(selected_stock)
{ 
    menuText = std::string(
    "===============================================\n") +
    " Stock details for " + setStock.getID() + "\n"
    "===============================================\n"
    "(Press \"b\" to go back)\nDescription: " + setStock.getDescription() + "\nCurrent Price: " + std::to_string(setStock.getPrice()) + "\n1: Buy " + setStock.getID();
    "\nq to exit application.\n";
}
BaseMenu *stockPage::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case '1':
        {   std::string input;
            double total_cost;
            std::string confirmation_choice;
            std::cout << "Number of shares to purchase: " << std::endl;
            try{
                std::cin >> input;
                int quantity = std::stoi(input);
                std::cout << "Total amount due: " + std::to_string(quantity*(setStock.getPrice())) << std::endl;
                //Catch if entered amount is more than balance.
                if (quantity*(setStock.getPrice()) > menuData.getAccount()->getBalance()){
                    std::cout << "Insufficient funds! Please try adding funds. Press any key to continue:" << std::endl;
                    std::cin >> input; // Accept input to allow pause and message to be read.
                    break;
                }
                std::cout << "Please confirm the transaction (Y/N): " << std::endl;
                std::cin >> confirmation_choice;
                if (confirmation_choice == "Y" || confirmation_choice == "y" || confirmation_choice == "yes" || confirmation_choice == "YES")
                {
                    int status = menuData.getAccount()->buyShare(setStock, quantity);
                    if (status)
                    {
                        std::cout << std::to_string(quantity) + " " + setStock.getID() + " shares successfully purchased to " + menuData.getAccount()->getCustomerName() << std::endl;
                        std::cout << menuData.getAccount()->getTransactions().back() << std::endl;
                        std::cout << "Confirm to go back (any character):" << std::endl;
                        std::cin >> choice;
                    }
                    else throw std::invalid_argument("Impossible situation - higher cost than funds available. Exiting...");
                }
                else
                {
                    std::cout << "Purchase cancelled. Confirm to return to stock overview." << std::endl;
                    std::cin >> choice;
                }
            }
            catch(const std::invalid_argument& e)
            {
                std::cout << "Incorrect input provided - please only enter numerical values when asked. Press any key to continue:" << std::endl;
                input = "";
                std::cin >> input;
            }
            //No new menu assigned so it stays as previously set.
            break;
        }
        case 'b':
        { aNewMenu = new userHome(menuData); break;}
        case 'q':
        {
            iIsQuitOptionSelected = true; break;
        }
        default:
        { break; }
    }
    return aNewMenu; 
}