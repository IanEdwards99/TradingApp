#include "account.hpp"
#include <string>

namespace account{
    account::account(    
        std::string name,
        std::string pass) : 
        account_name(name),
        password(pass)
        {
            dateCreated = time(0);
            account_nr = 1;
        }

    account::~account(){}
}

