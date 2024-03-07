#include "account.hpp"
#include <string>

namespace account{
    account::account(  
        std::string username,  
        std::string pass,
        std::string customer_name,
        int acc) : 
        username(username),
        password(pass),
        customer_name(customer_name),
        account_nr(acc)
        {
            dateCreated = time(0);
        }

    account::~account(){}

    std::ostream& operator<<(std::ostream& os, const account & outputAccount){
        os << "Username: " << outputAccount.username << std::endl << "Account password: " << outputAccount.password << std::endl 
        << "Fullname: " << outputAccount.customer_name << std::endl
        << "Account number: " << outputAccount.account_nr << std::endl << "Date created: " << outputAccount.dateCreated << std::endl;
        return os;
    }

    int account::getAccountNr(){
        return account_nr;
    }

    std::vector<transaction> account::getTransactions(){
        return transactions;
    }

    std::vector<stock> account::getStocks(){
        return stocks;
    }

    int account::buyShare(stock stock, int quantity){
        transactions.push_back(transaction(time(0), stock, quantity, stock.getPrice()*quantity));
        return 0;
    }

    int account::login(std::string username, std::string password){
        if (username == this->username && password == this->password){
            return true;
        }
        else return false;
    }
}

