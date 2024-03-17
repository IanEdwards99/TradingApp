#include <iostream>
#include <string>
#include "menu.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & value){
    for (auto x : value){
        os << x << std::endl;
    }
    return os;
}

BaseMenu::BaseMenu(){}

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
    switch (choice) // Notice - I have only done "options". You would obviously need to do this for all of your menus
    {
        case '1': //login chosen
        {
            if (homepage::login())
            {
                aNewMenu = new userHome(menuData); // should accept an account object to create menu with correct data... so change dataService::login to return an account.
            }
            else std::cout << "Incorrect login credentials provided, please try again!" << std::endl; // line getting cleaned up, find a better way.
            break;
        }
        case '2': //create Account chosen
        {
            menuData.addAccount(createAccount());
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
    std::cout << "Please enter your username:" << std::endl;
    std::string username;
    std::string password;
    std::cin >> username;
    std::cout << "Please enter your password:" << std::endl;
    std::cin >> password;

    return menuData.login(username, password);
}

account::account homepage::createAccount(){ // return unique_ptr instead
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
    return account::account(username, password, fullname, time(0) % 1000);
}

userHome::userHome(dataService& data_service) : BaseMenu(data_service)
{ menuText = std::string(
    "=============================\n") +
    " Welcome " + data_service.getAccount().getCustomerName() + "\n" + 
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
    for (auto i : data_service.getStocks()){
        menuText += i.getID() + " " + std::to_string(i.getPrice()) + "\n";
    }
    menuText += "-----------------------\nCurrently owned stocks:\n-----------------------\n";
    for (auto i : data_service.getAccount().getStocks()){
        menuText += i;
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
    " Transaction history for " + data_service.getAccount().getCustomerName() + "\n"
    "===============================================\n"
    "(Press \"b\" to go back)\n"                      ;
    for (auto i : data_service.getAccount().getTransactions()){
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
    " Account details for " + data_service.getAccount().getCustomerName() + "\n"
    "===============================================\n"
    "(Press \"b\" to go back)\n"                      ;
    menuText += data_service.getAccount();
    menuText += "\n-----------------------\nq to exit application.\n";
}
BaseMenu *accountDetailsMenu::getNextMenu(char choice, bool& iIsQuitOptionSelected)
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
        {   int quantity;
            double total_cost;
            char choice;
            std::cout << "Number of shares to purchase: " << std::endl;
            std::cin >> quantity;
            std::cout << "Total amount due: " + std::to_string(quantity*(setStock.getPrice())) << std::endl;
            std::cout << "Please confirm the transaction (Y/N): " << std::endl;
            std::cin >> choice;
            if (choice == 'Y')
            {
                std::cout << std::to_string(quantity) + setStock.getID() + " shares successfully purchased to " + menuData.getAccount().getCustomerName() + " account." << std::endl;
                int status = menuData.getAccount().buyShare(setStock, quantity);
                std::cout << menuData.getAccount().getTransactions() << std::endl;
                std::cout << "Confirm to go back (any character):" << std::endl;
                std::cin >> choice;
            }
            else {
                std::cout << "Purchase cancelled. Confirm to return to stock overview." << std::endl;
                std::cin >> choice;
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
