#include <variant>
#include <string>
#include <vector>
#include <iostream>

enum class ExceptionCode {
    invalid_value,
    insufficient_funds
};

struct ReturnedValue {
    double value;
    ExceptionCode exception_code;
    bool has_exception = false;
};


class Wallet {
public:
    Wallet(std::string bank_, double balance_) : bank(bank_), balance(balance_) {  }

    std::variant<ExceptionCode, double> withdraw_money(double amount) {
        if (amount <= 0)
            return ExceptionCode::invalid_value;
        else if (balance < amount) 
            return ExceptionCode::insufficient_funds;
        
        balance -= amount;
        return balance;
    }

    ReturnedValue deposit_money(double amount) {
        ReturnedValue response;
        if (amount <= 0)
            response.has_exception = true;
            response.exception_code = ExceptionCode::invalid_value;

        balance += amount;
        response.value = balance;

        return response;
    }

private:
    double balance;
    std::string bank;
};

int main(int argc, char const *argv[]) {

    // new Tinkoff wallet
    Wallet wallet("Tinkoff", 1000);

    // new withdraw action
    double to_withdraw = 10000;
    std::variant<ExceptionCode, double> balance_after_withdraw = wallet.withdraw_money(to_withdraw);

    if (std::holds_alternative<ExceptionCode>(balance_after_withdraw))
        std::cout << "Error code: " << static_cast<int>(std::get<ExceptionCode>(balance_after_withdraw)) << std::endl;
    else
        std::cout << "New balance: " << std::get<double>(balance_after_withdraw) << std::endl;

    // new deposit action
    double to_deposit = 1000;
    ReturnedValue balance_after_deposit = wallet.deposit_money(to_deposit);

    if (balance_after_deposit.has_exception)
        std::cout << "Error code: " << static_cast<int>(balance_after_deposit.exception_code) << std::endl;
    else
        std::cout << "New balance: " << balance_after_deposit.value << std::endl;

    return 0;
}
