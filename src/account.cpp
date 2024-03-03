#include "account.hpp"
#include <string>

namespace account{
    account::account(    
        std::string name,
        std::string pass,
        int acc) : 
        account_name(name),
        password(pass),
        account_nr(acc)
        {
            dateCreated = time(0);
        }

    account::~account(){}

    void account::displayTransactions(){
        std::cout << transactions << std::endl;
    }

}

