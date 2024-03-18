#include "account.hpp"
#include <string>

namespace account{
    account::account(){}

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

    std::string account::getCustomerName(){
        return customer_name;
    }

    std::vector<transaction>& account::getTransactions(){
        return account::transactions;
    }

    std::vector<stock> account::getStocks() const{
        std::vector<stock> stocks;
        for (auto i : transactions){
            stocks.push_back(i.getStock());
        }
        return stocks;
    }

    int account::buyShare(stock stock, int quantity){
        this->transactions.push_back(transaction(time(0), stock, quantity, stock.getPrice()*quantity));
        return 0;
    }

    int account::login(std::string username, std::string password){
        if (username == this->username && password == this->password){
            return true;
        }
        else return false;
    }

    account::operator std::string() const{
        std::string output = "Username: " + username + "\nCustomer Name: " + customer_name + "\nAccount number: " + std::to_string(account_nr) + "\n-----------------------\nList of owned shares:\n-----------------------\n";
        for (auto i : getStocks()){
            output += i;
            output += "\n";
        }
        return output;
    }
}

