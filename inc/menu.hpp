#include <iostream>
#include <string>
#include "account.hpp"
#include "dataService.hpp"

class BaseMenu
{
public:
    BaseMenu();
    BaseMenu(dataService* data_service);
    virtual ~BaseMenu();
    virtual BaseMenu* getNextMenu(char iChoice, bool& iIsQuitOptionSelected) = 0;
    virtual void printText();
    dataService* menuData;

protected:
    std::string menuText; // This string will be shared by all children (i.e. derived) classes
};


class homepage : public BaseMenu // FirstMenu is default menu (login and create account)
{
    public:
        homepage(dataService* data_service);
        int login();
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
        account::account createAccount();
};

class userHome : public BaseMenu
{
    public:
        userHome(dataService* data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};






