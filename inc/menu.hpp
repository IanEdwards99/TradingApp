#include <iostream>
#include <string>
#include "account.hpp"
#include "dataService.hpp"

class BaseMenu
{
public:
    BaseMenu();
    BaseMenu(dataService& data_service);
    virtual ~BaseMenu();
    virtual BaseMenu* getNextMenu(char iChoice, bool& iIsQuitOptionSelected) = 0;
    virtual void printText();


protected:
    std::string menuText; // This string will be shared by all children (i.e. derived) classes
    dataService& menuData; // Store reference to data service created in main.cpp
};


class homepage : public BaseMenu // FirstMenu is default menu (login and create account)
{
    public:
        homepage(dataService& data_service);
        int login();
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
        int createAccount();
};

class userHome : public BaseMenu
{
    public:
        userHome(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class stockMenu : public BaseMenu
{
    public:
        stockMenu(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class TransactionHistory : public BaseMenu
{
    public:
        TransactionHistory(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class accountDetailsMenu : public BaseMenu
{
    public:
        accountDetailsMenu(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class stockPage : public BaseMenu
{
    private:
        stock setStock;
    public:
        stockPage(dataService& data_service, stock selected_stock);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class topupMenu : public BaseMenu
{
    public:
        topupMenu(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};

class withdrawMenu : public BaseMenu
{
    public:
        withdrawMenu(dataService& data_service);
        BaseMenu* getNextMenu(char choice, bool& iIsQuitOptionSelected);
};






