#include <iostream>
#include <string>
#include "menu.hpp"

BaseMenu::BaseMenu(){}

BaseMenu::BaseMenu(dataService* data_service) 
{ 
    menuText = "This shouldn't ever be shown!"; 
} 
BaseMenu::~BaseMenu() { }
void BaseMenu::printText()
{
    std::cout << menuText << std::endl;
}

homepage::homepage(dataService* data_service)
{
    menuText = std::string("==========================\n") + "Simple Trading Application\n" + 
            "==========================\n" +
            "q to exit application.\n" +
            "1: Login\n" +
            "2: Create account";
    menuData = data_service;
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
                std::cout << "here" << std::endl;
            }
            else std::cout << "Incorrect login credentials provided, please try again!" << std::endl; // line getting cleaned up, find a better way.
            break;
        }
        case '2': //create Account chosen
        {
            menuData->addAccount(createAccount());
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

    return menuData->login(username, password);
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

userHome::userHome(dataService* data_service)
{ menuText = std::string(
    "==========================\n") +
    "Simple Trading Application\n" + 
    "==========================\n" +
    "q to exit application.\n" +
    "1: View stocks\n" +
    "2: Transaction history\n" +
    "3: Account details";
    menuData = data_service;
}
BaseMenu *userHome::getNextMenu(char choice, bool& iIsQuitOptionSelected)
{
    BaseMenu *aNewMenu = 0; // We're setting up the pointer here, but makin sure it's null (0)
    switch (choice)
    {
        case '1':
        { aNewMenu = new homepage(menuData); break;}
        case '2':
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

