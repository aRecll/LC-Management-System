#include "supplier.h"

supplier::supplier(const std::string& name, double contract, double paid) : common(name), contract_amount(contract), paid_amount(paid) 
{
    if (contract < 0 || paid < 0) {
        throw std::invalid_argument("Суммы не могут быть отрицательными");
    }
}

void supplier::input()
{
    try {
        common::input();

        std::cout << "Введите сумму контракта: ";
        std::cin >> contract_amount;
        if (contract_amount < 0) {
            throw std::invalid_argument("Сумма контракта не может быть отрицательной");
        }

        std::cout << "Введите оплаченную сумму: ";
        std::cin >> paid_amount;
        if (paid_amount < 0) {
            throw std::invalid_argument("Оплаченная сумма не может быть отрицательной");
        }

        if (paid_amount > contract_amount) {
            throw std::invalid_argument("Оплаченная сумма не может превышать сумму контракта");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
        throw;
    }
}

void supplier::output() const
{
    common::output();
    std::cout << ", Контракт: " << contract_amount
        << ", Оплачено: " << paid_amount
        << ", Сальдо: " << get_balance() << "\n";
}

double supplier::get_balance() const
{
    return contract_amount - paid_amount;
}

supplier& supplier::operator=(const supplier& other)
{
    if (this != &other) {
        common::operator=(other);
        contract_amount = other.contract_amount;
        paid_amount = other.paid_amount;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, supplier& obj)
{
    
    std::ios_base::iostate original_state = is.rdstate();

    try {
        is.clear(); 

        is >> static_cast<common&>(obj);

        std::cout << "Введите сумму контракта: ";
        is >> obj.contract_amount;
        if (is.fail()) {
            throw std::invalid_argument("Некорректный формат суммы контракта");
        }
        if (obj.contract_amount < 0) {
            throw std::invalid_argument("Сумма контракта не может быть отрицательной");
        }

        std::cout << "Введите оплаченную сумму: ";
        is >> obj.paid_amount;
        if (is.fail()) {
            throw std::invalid_argument("Некорректный формат оплаченной суммы");
        }
        if (obj.paid_amount < 0) {
            throw std::invalid_argument("Оплаченная сумма не может быть отрицательной");
        }

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    catch (const std::exception& e) {
       
        is.clear(original_state);
        is.setstate(std::ios::failbit);
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        
        throw;
    }
    return is;
}
