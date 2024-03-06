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

    std::vector<transaction> account::getTransactions(){
        return transactions;
    }

    std::vector<stock> account::getStocks(){
        return stocks;
    }

    std::ostream& operator<<(std::ostream& os, const account & outputAccount){
        os << "Account name: " << outputAccount.account_name << std::endl << "Account password: " << outputAccount.password << std::endl
                << "Account number: " << outputAccount.account_nr << std::endl << "Date created: " << outputAccount.dateCreated << std::endl;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const std::vector<transaction> & outputTransactions){
        for (transaction x : outputTransactions){
            os << x << std::endl;
        }

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const std::vector<stock> & outputStocks){
        for (auto i : outputStocks){
            os << i << std::endl;
        }
        return os;
    }

    int account::buyShare(stock stock, int quantity){
        transactions.push_back(transaction(time(0), stock, quantity, stock.getPrice()*quantity));
        return 0;
    }


}

